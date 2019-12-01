#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#include "cluster.h"
#include "comms.h"
#include "mains.h"


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
  		if(world_rank==5)
  		{
			int check=MPI_Send(&number_1,1,MPI_INT,0,0,MPI_COMM_WORLD);
  		}
		else if (world_rank == 0) 
		{	
			int i=1;
      			int check=MPI_Recv(&number_1, 1, MPI_INT,5,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
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
					//data_recv[i][number_1]=number_1;
					i++;
    				}	
 			}
		}	
		else if(world_rank>0 && world_rank<5)
		{
    			MPI_Recv(&number_1,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  		}
		number_1++;
	}

}


