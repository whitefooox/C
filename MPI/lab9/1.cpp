#include <iostream>
#include "mpi.h"
#include <unistd.h>

void printArray(int* a, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    int rank, size;
    int n = 3;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int* b = new int[n];
    for(int i = 0; i < n; i++){
        b[i] = rank;
    }
    int* a = new int[n * size];
    MPI_Gather(b, n, MPI_INT, a, n, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("rank = %d\n", rank);
        printArray(a, n * size);
    }
    MPI_Finalize();
    return 0;
}