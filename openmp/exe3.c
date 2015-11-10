#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n);

int main(int argc, char* argv[]) {
   double  integral;   /* Store result in integral      */
   double  a, b;       /* Left and right endpoints      */
   int     n;          /* Total number of trapezoids    */
   int     thread_count;
   double ini_t,end_t;
   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   
   integral = 0.0;
   double global_result = 0.0;
   ini_t = omp_get_wtime();
#  pragma omp parallel num_threads(thread_count)\
      reduction(+:global_result)
      global_result += Trap(a, b, n);
   #pragma omp barrier
   end_t = omp_get_wtime();
   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %.15e\n",
      a, b, integral);
   printf("tiempo: %f\n",end_t-ini_t);
   return 0;
}


void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  
double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}  
double Trap(double a, double b, int n) {
   double  h, x, my_integral;
   double  local_a, local_b;
   int  i, local_n;
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n;
   local_n = n/thread_count;
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   my_integral = (f(local_a) + f(local_b))/2.0;
   for (i = 1; i <= local_n-1; i++) {
     x = local_a + i*h;
     my_integral += f(x);
   }
   my_integral = my_integral*h;
   return my_integral;

} 