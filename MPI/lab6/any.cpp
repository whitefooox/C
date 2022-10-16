#include "mpi.h"
#include <iostream>
#include <locale>

using namespace std;

int main(int argc, char *argv[])
{ 
    setlocale(LC_ALL,"russian");
    int rank;
    int size;
    double starttime, endtime;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for(double e = 0.001; e >= 0.000000001; e *= 0.1){
        if (rank == 0){
            double buf = 0;
            double sum = 0;
            starttime = MPI_Wtime();
            for(int i = rank; 1.0/(1 + i) > e; i = i + size){
                sum += 1.0/(1 + i);
            }
            double result = sum;
            for(int i = 1; i < size; i++){
                MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
                MPI_Recv(&buf, 1, MPI_DOUBLE, stat.MPI_SOURCE, stat.MPI_TAG, MPI_COMM_WORLD, &stat);
                result = result + buf;
            }
            endtime = MPI_Wtime();
            cout << "Предел: " << e << " Сумма: " << result << " Время: " << endtime - starttime << endl;
        } else {
            double sum = 0;
            for(int i = rank; 1.0/(1 + i) > e; i = i + size){
                sum += 1.0/(1 + i);
            }
            MPI_Send(&sum, 1, MPI_DOUBLE, 0, 777, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}