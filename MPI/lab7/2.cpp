#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    double t1, t2;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n = 10;
    if (rank == 0){
        int* a = new int[n];
        int* b = new int[n];
        for(int i = 0; i < n; i++){
            a[i] = 0;
        }
        t1 = MPI_Wtime();
        MPI_Send(&a[0], n, MPI_INT, 1, 777, MPI_COMM_WORLD);
        MPI_Recv(&b[0], n, MPI_INT, 1, 777, MPI_COMM_WORLD, &stat);
        t2 = MPI_Wtime();
        cout << "process: " << rank << endl;
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        for(int i = 0; i < n; i++){
            cout << b[i] << " ";
        }
        cout << endl;
        cout << "time: " << t2 - t1 << endl;
    } else if (rank == 1) {
        int* b = new int[n];
        int* a = new int[n];
        for(int i = 0; i < n; i++){
            b[i] = 1;
        }
        t1 = MPI_Wtime();
        MPI_Recv(&a[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
        MPI_Send(&b[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD);
        t2 = MPI_Wtime();
        usleep(1000);
        cout << "process: " << rank << endl;
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        for(int i = 0; i < n; i++){
            cout << b[i] << " ";
        }
        cout << endl;
        cout << "time: " << t2 - t1 << endl;
    }
    MPI_Finalize();
}