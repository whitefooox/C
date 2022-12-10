#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]){

    const int root = 0;
    int rank, size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int len;
    int** array;

    if(rank == root){
        cout << "n = "; cin >> len;
        array = new int*[len];
        array[0] = new int[len * len];
        for(int i = 1; i < len; i++){
            array[i] = array[i - 1] + len;
        }
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                array[i][j] = (i + 1) * 10 + (j + 1);
            }
        }

        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    MPI_Bcast(&len, 1, MPI_INT, root, MPI_COMM_WORLD);

    MPI_Datatype mt, mt1;
    MPI_Type_vector(len, 1, len, MPI_INT, &mt);
    MPI_Type_commit(&mt);
    int count = len % 2 != 0 ? len / 2 + 1 : len / 2;
    MPI_Type_hvector(count, 1, 8, mt, &mt1);
    MPI_Type_commit(&mt1);

    if(rank == root){
        MPI_Send(array[0], 1, mt1, 1, 777, MPI_COMM_WORLD);
    } else {
        int** buffer = new int*[len];
        buffer[0] = new int[len * len];
        for(int i = 1; i < len; i++){
            buffer[i] = buffer[i - 1] + len;
        }
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                buffer[i][j] = 0;
            }
        }
        MPI_Recv(&buffer[0][0], 1, mt1, root, 777, MPI_COMM_WORLD, &stat);
        
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                cout << buffer[i][j] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
    return 0;
}