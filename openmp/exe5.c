#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


int main(int argc, char* argv[]) 
{

   float a[] = {4.0,3.0,3.0,1000.0};
   int i;
   float sumc = 0.0;
   for (i = 0; i < 4; i++)
      sumc += a[i];
   printf("sin pragma sum = %4.1f\n",sumc);

	float sum = 0.0;
   # pragma omp parallel for num_threads(2) reduction(+:sum)
   for (i = 0; i < 4; i++)
      sum += a[i];
   printf("con pragma sum = %4.1f\n",sum);

   return 0;
}


