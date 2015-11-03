# include <iostream>
# include <cstdio>
# include <pthread.h>
# include <cstdlib>


using namespace std;

long thread_count, n = 10000000;
double sum = 0.0;
long flag = 0;
/*double func_pi(int n)
{
	double factor = 1.0, sum = 0.0, pi;
	for (int i = 0; i < n; i++, factor = -factor)
	{
		sum += factor/(2*i+1);
	}
	pi = 4.0*sum;
	return pi;
}*/
void *thread_sum(void* rank)
{
	//int my_rank = *((int*)rank);
	long my_rank = (long)rank;
	double factor,my_sum=0.0;
	long long my_n = n/thread_count;
	long long my_first_i = my_n*my_rank;
	long long my_last_i = my_first_i + my_n;

	if (my_first_i%2 == 0)
		factor = 1.0;
	else 
		factor = -1.0;

	for (long long i = my_first_i; i<my_last_i; i++,factor = -factor) 
	{
		my_sum += factor/(2*i+1);
	}
	while(flag != my_rank);
	sum += my_sum;
	flag = (flag+1)%thread_count;
	//cout<<"hola"<<endl;
	return NULL;


}/**/
int main(int argc, char *argv[])
{
	/*long thread; 
	pthread_t *thread_handles;
	int thread_count = strtol(argv[1], NULL, 10);
	thread_handles = new pthread_t [thread_count];*/

	pthread_t *thread_h;
	thread_count = strtol(argv[1], NULL, 10);
	thread_h = new pthread_t [thread_count];
	for (long i = 0; i < thread_count; ++i)
	{
		pthread_create(&thread_h[i], NULL, thread_sum, (void*)(i));
	}
	//printf("Hello from the main thread\n");
	for (long i = 0; i < thread_count; ++i)
		pthread_join(thread_h[i], NULL);/**/
	cout<<4*sum<<endl;
	/*int n = 1000;
	cout<<func_pi(n)<<endl;*/
	return 0;
}