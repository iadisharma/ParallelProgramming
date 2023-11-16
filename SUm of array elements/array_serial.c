#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
	int a[10000];
	for(int i=0;i<10000;i++){
		a[i]=1;
	}
	double start=omp_get_wtime();
	int c=0,sum=0;
	for(int i=0;i<10000;i++){
		sum+=a[i];
		//printf("%d\t",a[i]);
	}
	double end=omp_get_wtime();
	printf("Execution time is-:%f\n",(end-start));
	printf("Sum is-:%d\n",sum);
}
