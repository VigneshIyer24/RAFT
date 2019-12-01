#ifndef __COMMS_H__
#define __COMMS_H__

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void send_votes();
void send_logs(int data);
void recv_data_client();


#endif /*__COMMS_H__*/
