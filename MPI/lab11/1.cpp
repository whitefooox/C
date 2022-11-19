#include <stdio.h>
#include <iostream>
#include "mpi.h"
#include <unistd.h>

using namespace std;

int getRandomNumber(int min, int max, int rank){
    srand(time(NULL) + rank);
    int num = min + rand() % (max - min + 1);
    return num;
}

int main(int argc, char *argv[])
{
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int x = getRandomNumber(0, 100, rank);
    int max;
    
    MPI_Reduce(&x, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0){
        cout << "max = " << max << endl;
    }

    usleep(rank * rank * 1000);
    cout << "rank = " << rank << " x = "  << x << endl;

    MPI_Finalize();
    return 0;
}