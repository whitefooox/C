#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    double t1, t2;
    int rank, size;
    int n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        cout << "n = "; cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int* a = new int[n];
    if(rank == 0){
        for(int i = 0; i < n; i++){
            a[i] = i;
        }
    }
    t1 = MPI_Wtime();
    MPI_Bcast(&a[0], n, MPI_INT, 0, MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    usleep(rank * rank * 10000);
    printf("rank= %d a: ",rank);
    for(int i = 0; i < n; i++){
        printf(" %d ",a[i]);
    }
    printf("\n");
    if(rank == 0){
        usleep(size * size * 10000);
        cout << "n = " << n << " time = " << t2 - t1 << endl;
    }
    MPI_Finalize();
    return 0;
}
