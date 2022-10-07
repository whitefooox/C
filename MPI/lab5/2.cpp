#include <iostream>
#include "mpi.h"
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size;
    int n;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        cout << "n = "; cin >> n; cout << endl;
        for(int i = 1; i < size; i++){
            MPI_Send(&n, 1, MPI_INT, i, 111, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&n, 1, MPI_INT, 0, 111, MPI_COMM_WORLD, &stat);
    }
    if(rank == 0){
        int** a = new int*[size - 1];
        a[0] = new int[(size - 1) * n];
        for(int i = 1; i < size - 1; i++){
            a[i] = a[i - 1] + n;
        }
        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < n; j++){
                a[i][j] = 0;
            }
        }
        for(int i = 1; i < size; i++){
            MPI_Recv(a[i - 1], n, MPI_INT, i, 777, MPI_COMM_WORLD, &stat);
        }
        cout << "rank = " << rank << " array:\n";
        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < n; j++){
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        delete[] a[0];
        delete[] a;
    } else {
        int* b = new int[n];
        for(int i = 0; i < n; i++){
            b[i] = rank * 10 + i;
        }
        MPI_Send(&b[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD);
        delete[] b;
    }
    MPI_Finalize();
    return 0;
}