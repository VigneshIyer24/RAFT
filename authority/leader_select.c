#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <pthread.h>
#include <time.h>

#include "comms.h"
#include "leader_select.h"


#define LOW 150
#define HIGH 500

#define NSEC2MSEC 1000000
#define SEC2MSEC 0.001
#define SEC2NSEC 1000000000

struct timespec timeout[5];
pthread_mutex_t time_lock;
long double final_value[5];

void server_timeout(int no_servers)
{
	pthread_mutex_lock(&time_lock);
	double time_diff[5];	
	for(int i=0; i<no_servers;i++)
	{
		clock_gettime(CLOCK_MONOTONIC,&timeout[i]);
		time_diff[i]=timeout[i].tv_nsec;
		timeout[i].tv_nsec += ((rand() % (HIGH - LOW +5))+LOW)*1000000;
		final_value[i]=(timeout[i].tv_nsec - time_diff[i])/NSEC2MSEC;
		printf("Time %d = %Lf \n",i,final_value[i]);

	}
	pthread_mutex_unlock(&time_lock);
}

int leader_select(int no_servers)
{
	long double servers[5]; 
	int smallest,index;
	server_timeout(no_servers);
	for(int i=0;i<no_servers;i++)
	{
		servers[i]=final_value[i];
		printf("Timout for server %d = %Lf\n",i,servers[i]);
	}
	smallest=servers[0];
	for (int i = 0; i < no_servers; i++) 
	{
      		if (servers[i] < smallest)
		{	
			smallest = servers[i];
      			index=i;
		}
	}

	return index;

}
	
int main()
{
	int hello=leader_select(5);
	printf("%d is the leader",hello);
	return 0;
}
