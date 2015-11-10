#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>



int main(int argc, char* argv[]) {
   int     n;          /* Total number of trapezoids    */
   int     thread_count;
   double ini_t,end_t;
   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   int sum = 0;
#  pragma omp parallel for num_threads(thread_count)\
      for (int i = 0; i < 5; ++i)
      {
         sum += i;
      }
      
      
 
   return 0;
}

