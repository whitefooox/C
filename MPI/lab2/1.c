#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    int rank, size;
    int prev, next;
    float buf;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    next = rank + 1;
    prev = rank - 1;
    if(rank == 0){
        prev = size - 1;
    }
    if(rank == (size - 1)){
        next = 0;
    }
    if(rank == 0){
        buf = 1;
        MPI_Send(&buf, 1, MPI_FLOAT, next, 1, MPI_COMM_WORLD);
        MPI_Recv(&buf, 1, MPI_FLOAT, prev, 1, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(&buf, 1, MPI_FLOAT, prev, 1, MPI_COMM_WORLD, &status);
        buf++;
        MPI_Send(&buf, 1, MPI_FLOAT, next, 1, MPI_COMM_WORLD);
    }
    printf("Ранг: %d Число: %f\n", rank, buf);
    MPI_Finalize();
}