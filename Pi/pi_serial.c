#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

static long num_steps=100000;
double step;
void main()
{
int i;

double x , pi , sum = 0.0,t1,t2;
double start=omp_get_wtime();
	step = 1.0/(double)num_steps;
	for( i = 0;i < num_steps;i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	pi = step*sum;
	
double end=omp_get_wtime();
printf("The execution time is-: %f\n",(end-start));
printf("Thevalue of pi is : %f\n",pi);

}

