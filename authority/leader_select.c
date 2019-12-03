#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <pthread.h>
#include <time.h>

#include "comms.h"
#include "leader_select.h"

void server_timeout(int server_no)
{
	pthread_mutex_lock(&time_lock);
	double time_diff;	
	clock_gettime(CLOCK_MONOTONIC,&timeout[i]);
	time_diff=timeout.tv_nsec;
	timeout.tv_nsec += ((rand() % (HIGH - LOW +5))+LOW)*1000000;
	final_value=(timeout.tv_nsec - time_diff)/NSEC2MSEC;
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
