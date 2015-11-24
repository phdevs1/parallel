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
   for(int i = 1; i < n; i++)
   {  
  		//a[i]=a[i-1]+i;//
  		a[i]=i*(i+1)/2; 
   }
   
   for (int i = 1; i < n; ++i)
   {
      cout<<a[i]<<" ";
   }
   cout<<endl;
   return 0;
}


