#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>

#include "cluster.h"
#include "comms.h"
#include "mains.h"
#include "leader_select.h"

void create_cluster();
const int data_send=1;
const int vote=1;
const int heartbeat=1;
int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);
  	// Find out rank, size
   	int world_rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  	int world_size;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    	create_cluster(world_size, world_rank);
        MPI_Finalize();
	return 0;
}

state serverStatechange(server Myserver, event_id ID)
{
        switch (ID):
        {

                case REPLICATION_COMMAND:
                /* starts corresponding  timeout timer for that particular server that is represented by the thread*/
			int counter=499;
			int check=MPI_Recv(&send_data, 1, MPI_INT,leader,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check == 0)
			{
				Myserver.data_recv[counter]=send_data;
				counter--;
				return FOLLOWER;
			}
			else
				return CANDIDATE;
                break;
                case VOTE_COMMAND:
                /* VOTE sent to a follower to a candidate*/
			MPI_Send(&vote,1,MPI_INT,Myserver.thread_id,0,MPI_COMM_WORLD);
			return CANDIDATE;
                break;
                case CLIENT_MESSAGE_COMMAND:
                /* Client sends data to the leader*/
			int counter = 0; 
			int check=MPI_Recv(&send_data, 1, MPI_INT,recv,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check==0)
			{
				Myserver.data_recv[counter]=send_data;
				counter++;
			}
			return LEADER;
                break;
                case VOTE_REQUEST_COMMAND:
                /* Requesting other servers for votes when an election is started*/
			
                break;
		case EVENT_TIMEOUT_COMMAND:
                /* Requesting and telling the other servers and leader to start an election*/
                break;
		case HEARTBEAT_COMMAND:
			int check=MPI_Recv(&send_data,1,MPI_INIT,client,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check!=0)
				MPI_Bcast(&heartbeat,1,MPI_INIT,0,MPI_COMM_WORLD);
        		return LEADER;
		break;

	}	

}

void create_cluster(int world_size,int world_rank)
{

  	int data_send;
	int data_recv[10];
	// We are assuming at least 2 processes for this task
  	if (world_size < 2) 
	{
    		perror( "World size must be greater than 1 for " );
    		MPI_Abort(MPI_COMM_WORLD, 1);
  	}
	
  	int number_1=0;
	int number;
	while(number_1<10)
	{
  		if(world_rank==world_size-1)
  		{
			int check=MPI_Send(&number_1,1,MPI_INT,0,0,MPI_COMM_WORLD);
  		}
		else if (world_rank == 0) 
		{	
			int i=1;
      			int check=MPI_Recv(&number_1, 1, MPI_INT,world_size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check==0)
			{
    				printf("Data Received %d\n",number_1);
				while(i>0 && i<world_size)
    				{
    					MPI_Send(&number_1,1,MPI_INT,i,0,MPI_COMM_WORLD);
    					if(i==1)
					{
						data_recv[number_1]=number_1;
					}
					i++;
    				}	
 			}
		}	
		else if(world_rank>0 && world_rank<world_size-1)
		{
    			MPI_Recv(&number_1,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  		}
		number_1++;
	}

}
