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
   int a[n];
   a[0] = 0;
   # pragma omp parallel for num_threads(thread_count)\
      reduction(+:tmp1) private(tmp0)
   for(int i = 1; i < n; i++)
   {  
      tmp0 = a[i-1];
      tmp1 = a[i];
      tmp1=tmp0+i;
   }
   
   for (int i = 1; i < n; ++i)
   {
      cout<<a[i]<<" ";
   }
   cout<<endl;
   return 0;
}


