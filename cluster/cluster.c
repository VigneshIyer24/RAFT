#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>

#include "cluster.h"
#include "comms.h"
//#include "mains.h"
#include "leader_select.h"

struct timespec timer_start,timer_end;
int send_data=1;
int vote=1;
int heartbeat=1;
double total_time;
void create_cluster();
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

state serverStatechange(server *Myserver, event_id ID)
{
        int counter,check;
	switch(ID)
        {

                case REPLICATION_COMMAND:
                /* starts corresponding  timeout timer for that particular server that is represented by the thread*/
			counter=499;
			check=MPI_Recv(&send_data, 1, MPI_INT,/*leader*/0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check==0 && counter == 499)
			{
				clock_gettime(CLOCK_MONOTONIC,&timer_end);
				total_time=timer_end.tv_sec+(timer_end.tv_nsec/1000000000);
				counter--;
			}
			check=MPI_Recv(&send_data, 1, MPI_INT,/*leader*/0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check==0 && counter<499)
			{
				clock_gettime(CLOCK_MONOTONIC,&timer_end);
				total_time=(timer_end.tv_sec+(timer_end.tv_nsec/1000000000));
				printf("%f",total_time);
				//total_time=total_time*100;
			}
			printf("%f",total_time);
			if(check == 0 && total_time < Myserver->timeout)
			{
				Myserver->data_recv[counter]=send_data;
				counter--;
				printf("Recived Data\n");
				return FOLLOWER;
			}
			else
			{
				printf("Failed");
				return CANDIDATE;
			}
                break;
                case VOTE_COMMAND:
                /* VOTE sent to a follower to a candidate*/
			MPI_Send(&vote,1,MPI_INT,Myserver->thread_id,0,MPI_COMM_WORLD);
			return CANDIDATE;
                break;
                case CLIENT_MESSAGE_COMMAND:
                /* Client sends data to the leader*/
			counter = 0; 
			check=MPI_Recv(&send_data, 1, MPI_INT,/*recv*/0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check==0)
			{
				Myserver->data_recv[counter]=send_data;
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
			printf("Hello\n");
		/*	check=MPI_Recv(&send_data,1,MPI_INT,client0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			if(check!=0)
			{
				MPI_Bcast(&heartbeat,1,MPI_INT,0,MPI_COMM_WORLD);
			}*/
		//	else
			
			MPI_Send(&heartbeat,1,MPI_INT,1,0,MPI_COMM_WORLD);
			
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
  	server *server_pool[world_size];
	for(int i=0;i<world_size;i++)
	{
		server_pool[i]=(server*)malloc(sizeof(server));
		server_pool[i]->thread_id=i;
	}
	server_pool[0]->timeout = 150;
	server_pool[1]->timeout = 190;
	server_pool[2]->timeout = 170;
	server_pool[3]->timeout = 200;
	server_pool[4]->timeout = 250;
	for(int i =0 ;i<3;i++)
	{
	if(world_rank==0)
	{
		server_pool[0]->__STATE__=LEADER;
		server_pool[0]->__STATE__=serverStatechange(server_pool[0],HEARTBEAT_COMMAND);
	}
	else
	{
		//server_pool[0]->__STATE__=LEADER;
		server_pool[1]->__STATE__=FOLLOWER;
		server_pool[2]->__STATE__=FOLLOWER;
		server_pool[3]->__STATE__=FOLLOWER;
		server_pool[4]->__STATE__=FOLLOWER;
//		server_pool[0]->__STATE__=serverStatechange(server_pool[0],HEARTBEAT_COMMAND);
		server_pool[1]->__STATE__=serverStatechange(server_pool[1],REPLICATION_COMMAND);
		server_pool[2]->__STATE__=serverStatechange(server_pool[2],REPLICATION_COMMAND);
		server_pool[3]->__STATE__=serverStatechange(server_pool[3],REPLICATION_COMMAND);
		server_pool[4]->__STATE__=serverStatechange(server_pool[4],REPLICATION_COMMAND);
		printf("Done\n");

	}
	}
}
