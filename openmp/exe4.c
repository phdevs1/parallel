#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
   int thread_count;
   
   thread_count = strtol(argv[1], NULL, 10);

   int sum = 0,
       mu=1,
       and_double=1,
       or_double=0;
       and_single=~0;
       /*or_single=,
       powt=;*/

#  pragma omp parallel for num_threads(thread_count)\
   reduction(+:sum)
   for (int i = 1; i <= 10; ++i)
      sum += i;

   cout<<"sum: "<<sum<<endl;
   
#  pragma omp parallel for num_threads(thread_count)\
   reduction(*:mu)
   for (int i = 1; i <= 10; ++i)
      mu = mu*i;
      
   cout<<"multi:"<<mu<<endl;
   int v[] ={1,1,1,1,0,1,1,1,0,1};
#  pragma omp parallel for num_threads(thread_count)\
   reduction(&&:and_double)
   for (int i = 0; i < 10 ; ++i)
      and_double = and_double&&v[i];
   
   cout<<"&&: "<<and_double<<endl; // retorna cero si existe x lo menos un cero en el vector
   int v1[] ={0,0,0,0,0,1,0,0,0,1};
#  pragma omp parallel for num_threads(thread_count)\
   reduction(||:or_double)
   for (int i = 0; i < 10; ++i)
      or_double = or_double||v1[i];
   
   cout<<"||: "<<and_double<<endl;  // retorna uno si existe por lo menos algun 1

   int c1[] ={0,1,0,0,0,1,0,0,0,1};
   int d2[] ={0,0,0,0,0,1,0,0,0,1};
#  pragma omp parallel for num_threads(thread_count)\
   reduction(&|:and_single)
   for (int i = 0; i < 10; ++i)
      or_double = or_double||v1[i];
   int t = 11 & 6;
   cout<<"and :"<<t<<endl;
   return 0;
}

