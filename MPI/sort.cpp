#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 100

void mergeArrays(int *, int *, int *, int, int);
int computeNeighbor(int, int, int);
void Odd_even_sort(int a[], int n);
 
int main(int argc, char ** argv)
{
    int i, j, n, rank, size,v_[N];
    double t1=0,t2=0,t3=0,t4=0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand (time(NULL));
    if(rank == 0)
    {
      
      for(i = 0 ; i < N; i++)
        v_[i] = rand() % 100 ;
      t1 = MPI_Wtime();  // tiempo de incio
      Odd_even_sort(v_,N);
      t2 = MPI_Wtime();  // tiempo de fin
      printf("serie: %f\n", t2-t1);
      /*for(i = 0 ; i < N; i++)
        printf("%d\n",v_[i] );*/
      
    }
    int numElements = N/size;
    int * arr = (int *) malloc(sizeof(int)*numElements);
    int * temp = (int *) malloc(sizeof(int)*numElements*2);
    int * recvArr = (int *) malloc(sizeof(int)*numElements);
    int * fullArr = NULL;
    if(rank == 0)
      fullArr = (int *) malloc(sizeof(int)*N);  

    srand (time(NULL));
    for(i = 0 ; i < numElements; i++)
      arr[i] = rand() % 100 ;
    
    if (rank==0)
      t3 = MPI_Wtime();  // tiempo de incio  
    
    //ordenar el array con el algoritmo odd-even
  
    //ordenar valores locales
    Odd_even_sort(arr,numElements);

    //iniciando las interaciones
    for(n = 0; n < size; n++) 
    {
      MPI_Barrier(MPI_COMM_WORLD);
      int neighbor = computeNeighbor(n, rank, size);

      if(neighbor >= 0 && neighbor < size)
      {
        //enviar mis valores al vecino y recivir valores desde mis vecinos
        MPI_Sendrecv(arr,numElements,MPI_INT,neighbor,n,recvArr,numElements,MPI_INT,neighbor,n,MPI_COMM_WORLD, &status);
        //si mi rank es menor que el rank de los vecinos, mantener el valor menor
        if(rank < neighbor)
          mergeArrays(arr, recvArr, temp, numElements, 1);
        else   //caso contrario mantener el valor mayor 
          mergeArrays(arr, recvArr, temp, numElements, 0);
        
      }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(arr, numElements, MPI_INT, fullArr, numElements, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0)
    {
      t4 = MPI_Wtime();  //tiempo fin de paralelo
      printf("paralelos: %f\n", t4-t3);    
    }
    /*if(rank == 0)
    {
      printf("imprimiendo valores ordenados : ");
       for(i = 0; i < N; i++)
        printf("%d ", fullArr[i]);
      printf("\n");
    }*/
  MPI_Finalize();
  return 0;
}
void Odd_even_sort(int a[], int n) 
{
  int phase, i, temp;
  for (phase = 0; phase < n; phase++)
    if (phase % 2 == 0) //fase par
    { 
      for (i = 1; i < n; i += 2)
      if (a[i-1] > a[i]) 
      {
        temp = a[i];
        a[i] = a[i-1];
        a[i-1] = temp;
      }
   } else {  // fase impar
    for (i = 1; i < n-1; i += 2)
      if (a[i] > a[i+1]) {
        temp = a[i];
        a[i] = a[i+1];
        a[i+1] = temp;
      }
    }
 }


int computeNeighbor(int phase, int rank, int size)
{
  int neighbor;
  if(phase % 2 != 0)
  { 
    if(rank % 2 != 0)
      neighbor = rank + 1;
    else             
      neighbor = rank - 1;
  } 
  else 
  {  
    if(rank % 2 != 0) 
      neighbor = rank - 1; 
    else    
      neighbor = rank + 1;
  }

  if(neighbor < 0 || neighbor >= size)
    neighbor = -1;
  return neighbor;
}

void mergeArrays(int * arr, int * neighborArr, int * temp, int size, int low_or_high)
{
  int i, j, k;
  i = j = k = 0;

  //con los arrays ya ordenados
  for(i,j,k; i < size*2; i++)
  {
    if(j < size && k < size)
    {
      if(arr[j] < neighborArr[k])
      {
        temp[i] = arr[j];
        j++;
      } else {
        temp[i] = neighborArr[k];
        k++;
      }
    } else if(j < size) {
      temp[i] = arr[j];
      j++;
    } else {
      temp[i] = neighborArr[k];
      k++;
    }
  }

  if(low_or_high % 2 != 0)
    for(i = 0; i < size; i++)
      arr[i] = temp[i];
  else
    for(i = size, j=0; j < size; i++,j++)
      arr[j]= temp[i];
}