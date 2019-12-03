#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <stdio.h>
#include <stdlib.h>


typedef enum state_t
{

	LEADER,				/* This state represents the state of a server when it is a leader */
	CANDIDATE,			/* This state represents the state of a server when it is a candidate */
	FOLLOWER 			/* This state represents the state of a server when it is a follower */

}state;


typedef struct server_t
{

	int thread_id; 			/* Stores the thread id  of the server 		*/
	int data_recv[500];		/* Stores the data recived from client/leader 	*/
	state __STATE__; 		/* Stores the state of each server  		*/

}server;

typedef enum event_id_t
{

        REPLICATION_COMMAND,		/* Command sent by the leader to the other followers 						*/
	VOTE_COMMAND,			/* vote sent by the followers to a particular candidate						*/
	CLIENT_MESSAGE_COMMAND,		/* Message sent by the client to the leader							*/
	VOTE_REQUEST_COMMAND,		/* Command requesting the other followers to start an election 					*/
	EVENT_TIMEOUT_COMMAND,		/* Command telling the server that a timeout has occurred and you need to start an election 	*/
	HEARTBEAT_COMMAND		/* Command to see if the leader is still alive 							*/

}event_id;
void create_cluster(int a, int b);

state serverStatechange(server Myserver, event_id ID)/*
{
	switch (ID):
	{

		case REPLICATION_COMMAND:
		/* starts corresponding  timeout timer for that particular server that is represented by the thread
		break;
		case VOTE_COMMAND:
                /* VOTE sent to a follower to a canddate 
                break;
		case CLIENT_MESSAGE_COMMAND:
                /* Client sends data to the leader
                break;
		case VOTE_REQUEST_COMMAND:
                /* Requesting other servers for votes when an election is started
                break;
		case EVENT_TIMEOUT_COMMAND:
                /* Requesting and telling the other servers and leader to start an e;ection
                break;

	}

}*/
#endif /*__CLUSTER_H__*/

