#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mpi.h>


using namespace std;

int main(int argc, char *argv[]) 
{
	int procs, rank,len, count = 0;
   	char *ptr,text[1000];
   	char target[40] = {'\0'};
	int tag = 10;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  if(rank == 0)
  {
  	 text[1000] = {
      "Edelweiss, edelweiss, every morning you greet me.\n\
      Small and white, clean and bright, you look happy to meet me.\n\
      Blossom of snow may you bloom and grow, bloom and grow forever.\n\
      Edelweiss, edelweiss, bless my homeland forever.\n\
      Small and white, clean and bright, you look happy to meet me\n\
      Blossom of snow, may you bloom and grow, bloom and grow forever.\n\
      Edelweiss, edelweiss, bless my homeland forever."
   	};
   	cout<<text<<endl;
	cout<<"input the word: ";
  	fgets(target, sizeof(target), stdin);
   	len = strlen(target);
   	if(target[len-1] == '\n')  
      target[len-1] = '\0';

   	for (int i = 1; i < procs; ++i)
	{
		MPI_Send(&text,100,MPI_INT,i,tag,MPI_COMM_WORLD);	
		MPI_Send(&target,10,MPI_INT,i,tag,MPI_COMM_WORLD);	
	}
  }
  else
  {
  	
  	MPI_Recv(&text,100,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
  	MPI_Recv(&target,100,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
  	ptr = text;
	ptr = strstr(text, target);
   	while(ptr) {
      ptr = strstr(ptr,target);
      if(ptr)
       {
         ++count;
         ++ptr;
        
      }
   }
   printf("palabra: %s --> %d \n", target, count);

		
  }
   
   	MPI_Finalize();

   
	
   
   
   
   
   return 0;
}
