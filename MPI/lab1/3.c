#include "mpi.h"
#include <stdio.h>
#include <locale>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"russian");
    int rank, nprocs, len;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(name, &len);
    printf("Меня зовут %s\n", name);
    fflush(stdout);
    MPI_Finalize();
    return 0;
}
