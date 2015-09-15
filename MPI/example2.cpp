#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int procs, rank, size =5;
	int data[size];
	int tag = 10;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0)
	{
		for (int i = 0; i < size; ++i)
			data[i]=i;

		for (int i = 1; i < procs; ++i)
		{
			MPI_Send(&data,size,MPI_INT,i,tag,MPI_COMM_WORLD);	
		}
	}
	else
	{
		MPI_Recv(&data,size,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
		cout << "proceso: " << rank << " -> ";
    	for(int i=0;i<size;i++)
        	cout << data[i] << " ";
    	cout << endl;
    	
	}

	MPI_Finalize();


	return 0;
}
