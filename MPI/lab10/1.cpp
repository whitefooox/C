#include <stdio.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char *argv[]){

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = size * 2;
    int* a = new int[n];
    if(rank == 0){
        for(int i = 0; i < n; i++){
            a[i] = i;
        }
    }

    int* b = new int[2];

    MPI_Scatter(a, 2, MPI_INT, b, 2, MPI_INT, 0, MPI_COMM_WORLD);

    usleep(rank * rank * 1000);
    printf("rank = %d a:\n", rank);
    for(int i = 0; i < 2; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
    
    MPI_Finalize();
    return 0;
}