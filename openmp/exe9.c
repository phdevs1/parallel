#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
double Local_trap(double a, double b, int n);
double f(double x)
{
        return 3*x;
}
int main(int argc, char const *argv[]) 
{
        double global_result = 0.0;
        double a, b;
        int n,thread_count;
        
        thread_count = strtol(argv[1], NULL, 10);
                        
        a=1;
        b=2;
        n=100;/**/
        /*printf("ingrese n: ");
        scanf("%d",&n);*/

        if(n%thread_count!=0)
        {
                printf("el numero %i no es multiplo de %d\n", thread_count,n);
                exit(0);
        }
#       pragma omp parallel num_threads(thread_count)\
                reduction(+:global_result)
        global_result += Local_trap(a, b, n);

        printf("%f\n", global_result);
        return 0;
}
double Local_trap(double a, double b, int n)
{

        double h, x, my_result,local_a, local_b;
        int i, local_n;
        int my_rank = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
 
        h = (b - a)/n;
        local_n = n/thread_count;
        local_a = a + my_rank*local_n*h;
        local_b = local_a + local_n*h;
        my_result = (f(local_a) + f(local_b))/2.0;
#       pragma omp parallel for num_threads(thread_count)\
                reduction(+:my_result) schedule(runtime)
        for (i = 1; i <= local_n - 1; i++) 
        {
                my_result += f(local_a + i*h);
        }
        my_result = my_result*h;
        return my_result;
}/**/