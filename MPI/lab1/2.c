#include "mpi.h"
#include <stdio.h>
#include <locale>

int main( int argc, char *argv[] )
{
    setlocale(LC_ALL,"russian");
    double tick;
    MPI_Init( 0, 0 );
    tick = MPI_Wtick();
    printf("Одиночный MPI тик равен %0.9f секунды\n", tick);
    fflush(stdout);
    MPI_Finalize( );
    return 0;
}