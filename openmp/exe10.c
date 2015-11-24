#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
   int thread_count,n,tmp0,tmp1;
   thread_count = strtol(argv[1],NULL,10);
   cout<<"ingrese n:";
   cin>>n;
   int i;
   double my_sum = 0.0;
  # pragma omp parallel num_threads(thread_count)
   {
      for (i = 0; i < n; i++)
  #   pragma omp atomic
      my_sum += sin(i);
   }

   

   

   return 0;
}

