#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
   int thread_count,n;
   thread_count = strtol(argv[1],NULL,10);

   cout<<"input n: ";
   cin>>n;

   # pragma omp parallel for num_threads(thread_count)
   for(int i = 0; i < n; i++)
   {
      if(i%thread_count == 0)
         cout<<"value : "<<i+1<<endl;
   }
   

   return 0;
}


