#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#include "cluster.h"
#include "comms.h"

void create_cluster();
int main(int argc, char** argv)
{
	MPI_Init(NULL, NULL);
  	// Find out rank, size
   	int world_rank;
  	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  	int world_size;
  	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int process_number;
	sscanf(argv[2],"%d",&process_number);
        create_cluster(world_size, world_rank,process_number);
        MPI_Finalize();
	return 0;
}

void create_cluster(int world_size,int world_rank,int process_number)
{

  	// We are assuming at least 2 processes for this task
  	if (world_size < 2) 
	{
    		perror( "World size must be greater than 1 for " );
    		MPI_Abort(MPI_COMM_WORLD, 1);
  	}

  	int number_1=7;
	int number;
  /*	if(world_rank==5)
  	{
		int check=MPI_Send(
      	* data         = */// &number_1,   
      	/* count        = */ //1,
      	/* datatype     = */ //MPI_INT,
      	/* destination  = */ //0,
      	/* tag          = */ //0,
      	/* communicator =  MPI_COMM_WORLD;
  	}
*/
	 if (world_rank == 0) 
	{
	 	int i=1;
    	  	// If we are rank 0, set the number to -1 and send it to process 1
    
    	/*	int check=MPI_Recv(
      	* data         = */ //&number_1,
      	/* count        = */ //1,
      	/* datatype     = */// MPI_INT,
      	/* source       = */// 5,
      	/* tag          = */// 0,
      	/* communicator = */// MPI_COMM_WORLD,
      	/* status       = / MPI_STATUS_IGNORE);
		if(check==0)
		{
    			printf("Data Received %d\n",number_1);
			number=-1;*/
			while(i>0 && i<process_number)
    			{
    				MPI_Send(
      			/* data         = */ &number, 
      			/* count        = */ 1, 
      			/* datatype     = */ MPI_INT, 
      			/* destination  = */ i, 
      			/* tag          = */ 0, 
      			/* communicator = */ MPI_COMM_WORLD);
    				i++;
    			}	
 		//}
	}	
	else 
	{
    		MPI_Recv(
      	/* data         = */ &number, 
      	/* count        = */ 1, 
      	/* datatype     = */ MPI_INT, 
      	/* source       = */ 0, 
      	/* tag          = */ 0, 
      	/* communicator = */ MPI_COMM_WORLD, 
      	/* status       = */ MPI_STATUS_IGNORE);
    		printf("Process %d received number %d from process 0\n",world_rank, number);
  	}
}


