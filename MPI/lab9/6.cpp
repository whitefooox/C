#include <stdio.h>
#include "mpi.h"
#include <unistd.h>
int main(int argc, char *argv[]){
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* b = new int[size - rank];
    for(int i = 0; i < size - rank; i++){
        b[i] = rank;
    }
    int** a = new int*[size];
    a[0] = new int[size * size];
    for(int i = 1; i < size; i++){
        a[i] = a[i - 1] + size;
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            a[i][j] = 0;
        }
    }
    int* RC = new int[size];
    int* ds = new int[size];
    for (int i = 0; i < size;i++)
    {
        RC[i] = size - i;
        ds[i] = i * size + i;
    }
    MPI_Gatherv(b, size - rank, MPI_INT, *a, RC, ds, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("rank= %d a: \n",rank);
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
                printf(" %d ",a[i][j]);
            printf("\n ");
        }
    }
    MPI_Finalize();
    return 0;
}