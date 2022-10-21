#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
   int rank, size, prev, next;
   int buf[2];
   MPI_Status status1;
   MPI_Status status2;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   prev = (rank - 2 + size) % size;
   next = (rank + 2) % size;
   MPI_Sendrecv(&rank, 1, MPI_INT, prev, 777, &buf[1], 1, MPI_INT, next, 777, MPI_COMM_WORLD, &status2);
   MPI_Sendrecv(&rank, 1, MPI_INT, next, 999, &buf[0], 1, MPI_INT, prev, 999, MPI_COMM_WORLD, &status1);
   usleep(rank * 100000);
   printf( "process %d prev=%d next=%d\n", rank, buf[0], buf[1]);
   MPI_Finalize();
}