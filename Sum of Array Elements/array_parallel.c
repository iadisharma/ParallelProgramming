#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
int a[10000],i,psum=0,sum=0,tid;
double t1,t2;
int numt;
	for(int i=0;i<10000;i++){
		a[i]=1;
	}
t1=omp_get_wtime();
#pragma omp parallel default (shared) private(i,tid,psum)
{
	int from,to,psum=0;
	tid=omp_get_thread_num();//thread_num
	numt=omp_get_num_threads();
	from=(10000/numt)*tid;
	to=(10000/numt)*(tid+1)-1;
	if(tid==numt-1){
		to=10000-1;
	}
	printf(" Hello from %d to %d , my range =%d to %d\n",tid,numt,from,to);
	for(i=from;i<=to;i++){
		psum+=a[i];
	}
	#pragma omp critical
	{
		sum+=psum;	
	}
}
t2=omp_get_wtime();
printf("Execution time is-:%f\n",(t2-t1));
printf("Sum is-:%d\n",sum);
return 0;
}
