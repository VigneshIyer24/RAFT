#include <stdio.h>
#include <stdlib.h>
#include <stdin.h>
#include <mpi.h>

#include "cluster.h"
#include "comms.h"

void create_cluster(int no_servers)
{
	MPI_Init(NULL, NULL);
