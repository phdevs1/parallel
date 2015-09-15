#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int procs, rank, data,data1;
	int tag = 10;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0)
	{
		data = 2;

	}
	else
		MPI_Recv(&data,1,MPI_INT,rank-1,tag,MPI_COMM_WORLD,&status);
	if (procs-1>rank)
	{
		MPI_Send(&data,1,MPI_INT,rank+1,tag,MPI_COMM_WORLD);
	}
	cout<<"from procs: "<<rank<<" -> "<<data<<endl;		
	MPI_Finalize();


	return 0;
}
