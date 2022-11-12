#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank;
    int size;

    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = size * (size + 1);
    int* a = new int[n];
    if(rank == 0){
        for(int i = 0; i < n; i++){
            a[i] = i;
        }
    }

    int nn = 2 * (rank + 1);
    int* b = new int[nn];
    int* RC = new int[size];
    int* ds = new int[size];
    for(int i = 0; i < size; i++){
        RC[i] = 2 * (i + 1);
        ds[i] = (i + 1) * i;
    }

    MPI_Scatterv(a, RC, ds, MPI_INT, b, nn, MPI_INT, 0, MPI_COMM_WORLD);

    usleep(rank * rank * 1000);
    printf("rank = %d b:\n", rank);
    for(int i = 0; i < nn; i++){
        printf("%d ",b[i]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}