#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int size;
    int n, count;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0)
    {
        n=size;
        int **a=new int *[n];
        a[0]=new int [n * n];
        for(int i = 1; i < n; i++){
            a[i] = a[i - 1] + n;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = 0;
            }
        }
        for (int i = 1; i < size; i++)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD, &stat);
            MPI_Get_count(&stat, MPI_INT, &count);
            MPI_Recv(a[stat.MPI_SOURCE], count, MPI_INT, stat.MPI_SOURCE, 777, MPI_COMM_WORLD, &stat);
        }
        printf("result:\n");
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            printf("%d ",a[i][j]);
            printf("\n");
        }
    }
    else
    {
        srand(rank);
        n = rand() % size + 1;
        int* a = new int[n];
        for(int i = 0; i < n; i++)
            a[i] = rank;
        usleep(rank * 1000);
        printf("rank = %d\n", rank);
        for(int i = 0; i < n; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n\n");
        MPI_Send(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}