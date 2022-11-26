#include <iostream>
#include <math.h>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]){

    double startTime, endTime;
    int rank, size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int n = pow(10, 3); n <  pow(10, 9); n *= 10){
        int* a = new int[n];
        if(rank == 0){
            for(int i = 0; i < n; i++){
                a[i] = i;
            }
            startTime = MPI_Wtime();
            MPI_Send(a, n, MPI_INT, 1, 777, MPI_COMM_WORLD);
            endTime = MPI_Wtime();
        } else {
            MPI_Recv(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
        }
        if (rank == 0){
            cout << "n = " << n << " time = " << endTime - startTime << endl;
        }
        delete[] a;
    }
    MPI_Finalize();
    return 0;
}