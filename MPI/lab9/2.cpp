#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

void printArray(int* a, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    int rank;
    int size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int *b = new int[size - rank];
    for(int i = 0; i < size - rank; i++){
        b[i] = rank;
    }
    int* a = new int[(size * (size + 1)) / 2];
    int* RC = new int[size];
    int* ds = new int[size];
    int ds_temp = 0;
    for (int i = 0; i < size; i++)
    {
        RC[i] = size - i;
        ds[i] = ds_temp;
        ds_temp += RC[i];
    }
    MPI_Gatherv(b, size - rank, MPI_INT, a, RC, ds, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("rank = %d\n", rank);
        printArray(a, (size * (size + 1)) / 2);
    }
    MPI_Finalize();
    return 0;
}