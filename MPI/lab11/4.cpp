#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double startTime, endTime;
    for(int n = 1000; n <= pow(10, 9); n *= 10){
        double res = 0;
        double result;
        startTime = MPI_Wtime();
        for(int i = rank; i < n; i += size){
            res += (1. / (1. + i)) * (i / (1. + i));
        }
        MPI_Reduce(&res, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        endTime = MPI_Wtime();
        if(rank == 0){
            cout << "n = " << n << " time = " << endTime - startTime << " result: " << result << endl;
        }
    }
    MPI_Finalize();
    return 0;
}