#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
   double sum = 0.0,factor,pi;
   int k,n,thread_count;
   n=1000;
   thread_count = strtol(argv[1], NULL, 10);

#  pragma omp parallel for num_threads(thread_count)\
      default(none) reduction(+:sum) private(k,factor)\
      shared(n)
   for (k = 0; k < n; k++)
   {
      if (k%2 == 0)
         factor = 1.0;
      else
         factor = -1.0;
      sum += factor/(2*k+1);
   }
   pi = 4.0*sum;
   printf("%f\n",pi);
   return 0;
}

// es incorrecto porque habia loop-carried dependence en la variable factor y tambien 
// existica un race condition en la variable sum