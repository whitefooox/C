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

    int n;
    if(rank == 0) scanf("%d", &n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int** a = new int*[size * 2];
    a[0] = new int [size * 2 * n];
    for(int i = 1; i < size * 2; i++){
        a[i] = a[i - 1] + n;
    }
    if(rank == 0){
        for(int i = 0; i < size * 2; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = i;
            }
        }
    }

    int** b = new int*[2];
    b[0] = new int[2 * n];
    for(int i = 1; i < 2; i++){
        b[i] = b[i - 1] + n;
    }

    MPI_Scatter(*a, 2 * n, MPI_INT, *b, 2 * n, MPI_INT, 0, MPI_COMM_WORLD);

    usleep(rank * rank * 1000);
    printf("rank= %d b:\n", rank);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}