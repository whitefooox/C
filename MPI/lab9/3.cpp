#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int rank;
    int size;
    int n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        scanf("%d",&n);
    }
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    int** b = new int*[2];
    b[0] = new int [n * 2];
    for(int i = 1; i < 2; i++){
        b[i] = b[i - 1] + n;
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            b[i][j] = rank;
        }
    }
    int** a = new int*[size * 2];
    a[0] = new int [n * size * 2];
    for(int i = 1; i < size * 2; i++){
        a[i] = a[i - 1] + n;
    }
    MPI_Gather(*b, n * 2,MPI_INT, *a,n * 2,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        printf("rank= %d a: \n",rank);
        for(int i=0; i<size * 2; i++)
        {
            for(int j=0; j<n; j++)
            printf(" %d ",a[i][j]);
            printf("\n ");
        }
    }
    MPI_Finalize();
    return 0;
}