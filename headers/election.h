#ifndef __ELECTION_H__
#define __ELECTION_H__

#include <stdio.h>
#include <stdlib.h>

#include "cluster.h"
typedef enum voting_t
{
	VOTE_RECIVED,		/* This will indicate that the server recieved the vote 	*/
	VOTE_REJECTED		/* This will indicate that the server did not recieve the vote 	*/
}voter_id

voter_id vote_progress(server *Myserver,event_id ID);
/*case(EVENT_TIMEOUT_COMMAND): Server will change status to canditate		*/
/*case(VOTE_REQUEST_COMMAND) : Server will ask to start election		*/
/*case(VOTING_COMMAND):								*/
	/* case(1) : if the server asking for vote has higher term  			*/
	/* case(2) : if the server asking for vote has lower term 			*/
	/* case(3) : if the server asking for vote has same term but higher timeout 	*/
	/* case(4) : if the server asking for vote has the same term but lower timeout	*/
