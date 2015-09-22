#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
 
using namespace std;
int tam = 6;
int main(int argc, char * argv[]) 
{
 
    int size,rank;
    int **A, *x, *y,*miFila;
                        
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    A = new int *[tam]; 
    x = new int [tam]; 
     
    if (rank == 0) 
    {
        //reservando memoria
        A[0] = new int [tam * tam];
        for (int i = 1; i < tam; i++) {
            A[i] = A[i - 1] + tam;
        }
        y = new int [tam];
 
        //generando matriz y vector
        srand(time(0));
        cout << "La matriz y el vector generados son " << endl;
        for (int i = 0; i < tam; i++) 
        {
            for (int j = 0; j < tam; j++)
                A[i][j] = rand() % 10;
            x[i] = rand() % 10;
        }
        cout<<"matriz:"<<endl;
        for (int i = 0; i < tam; i++) 
        {
            for (int j = 0; j < tam; j++)
            {
                
                cout << A[i][j];
                cout << "  ";
            }
            cout<<endl;
        }
        cout<<"vector: "<<endl;
        for (int i = 0; i < tam; i++) 
            cout << x[i] << endl;
        cout<<endl;
    }
 
    miFila = new int [tam];
 
    MPI_Scatter(A[0],tam,MPI_INT, miFila,tam, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(x,tam,MPI_INT,0,MPI_COMM_WORLD); 
    MPI_Barrier(MPI_COMM_WORLD);
  
 
 
    int subFinal = 0;
    for (int i = 0; i < tam; i++) {
        subFinal += miFila[i] * x[i];

    }
//    cout<<subFinal<<endl;
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&subFinal,1, MPI_INT,y,1, MPI_INT, 0, MPI_COMM_WORLD); 
    MPI_Finalize();

    if (rank == 0) 
    {
        cout << "El resultado " << endl;
        for (int i = 0; i < size; i++) {
            cout << y[i] <<  endl;
        }
     }
}