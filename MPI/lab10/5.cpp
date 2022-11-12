#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    if(rank == 0)
    scanf("%d", &n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int** a = new int*[n];
    a[0] = new int[n * n];
    for(int i = 1; i < n; i++){
        a[i] = a[i - 1] + n;
    }
    if(rank == 0){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = i;
            }
        }
    }

    int* t = new int[size];
    int c = n / size;
    int o = n % size;
    for(int i = 0; i < o; i++){
        t[i] = c + 1;
    }
    for(int i = 0; i < size - o ; i++){
        t[i + o] = c;
    }

    int** b = new int*[t[rank]];
    b[0] = new int[t[rank] * n];
    for(int j = 1; j < t[rank]; j++){
        b[j] = b[j - 1] + n;
    }
    int* RC = new int[size];
    int* ds = new int[size];
    for (int j = 0; j < size; j++){
        RC[j] = n * t[j];
    }
    ds[0]= 0;
    for (int j=1;j<size;j++){
        ds[j] = n * t[j - 1] + ds[j - 1];
    }

    MPI_Scatterv(*a, RC, ds, MPI_INT, *b, t[rank] * n,MPI_INT,0,MPI_COMM_WORLD);
    printf("rank= %d b: \n",rank);
    for(int i = 0; i < t[rank]; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}