#include <stdio.h>
#include "mpi.h"
#include <locale.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "russian");
    int rank, size;
    MPI_Init(&argc, &argv);

    int sum = 0;
    int data[10];
    for(int i = 0; i < 10; i++){
        data[i] = i;
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < rank + 1; i++)
    {
        sum += data[i];
    }

    printf("Номер: %d Сумма: %d\n", rank, sum);
    MPI_Finalize();
    return 0;
}
