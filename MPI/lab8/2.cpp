#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include <unistd.h>
#include <math.h>

using namespace std;

int Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm){
    int rank, size;
    int mask, src, dst;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(root >= size){
        return MPI_ERR_BUFFER;
    }
    int relative_rank = (rank >= root) ? rank - root : rank - root + size;
    mask = 0x1;
    while (mask < size){
        if (relative_rank & mask){
            src = rank - mask;
            if (src < 0) src += size;
            MPI_Recv(buffer, count, datatype, src, MPI_ANY_TAG, comm, MPI_STATUS_IGNORE);
            break;
        }
        mask <<= 1;
    }
    mask >>= 1;
    while(mask > 0){
        if(relative_rank + mask < size){
            dst = rank + mask;
            if(dst >= size){
                dst -= size;
            }
            MPI_Send(buffer, count, datatype, dst, 111, comm);
        }
        mask >>= 1;
    }
    return MPI_SUCCESS;
}

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
    Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int* a = new int[n];
    if(rank == 0){
        for(int i = 0; i < n; i++){
            a[i] = i;
        }
    }
    t1 = MPI_Wtime();
    Bcast(&a[0], n, MPI_INT, 0, MPI_COMM_WORLD);
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