#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define ASIZE 100000
int main(){
int i,psum=0,tid;
double t1,t2;
int numt;
double x , pi=0.0 , sum = 0.0,fpi=0.0,step=0.0;
t1=omp_get_wtime();
#pragma omp parallel default (shared) private(i,tid,sum,pi)
{

	int from,to,psum=0;
	tid=omp_get_thread_num();
	numt=omp_get_num_threads();
	printf("%d adn %d",tid,numt);
	from=(ASIZE/numt)*tid;
	to=(ASIZE/numt)*(tid+1)-1;
	step = 1.0/(double)(ASIZE);
	printf("My range is from -:%d to %d and step is-:%f\n",from,to,step);
	for( i = from;i<=to;i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	pi = step*sum;
	#pragma omp critical
	{
		fpi+=pi;
	}
	
}
t2=omp_get_wtime();
printf("Execution time is-:%f\n",(t2-t1));
printf("Pi-:%f\n",fpi);
return 0;
}
