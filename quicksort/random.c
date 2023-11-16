#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void main(){
double start,end;
FILE *fp;
fp=fopen("numbers.txt","w");
// start=omp_get_wtime();

for(int i=0;i<1000;i++){
	fprintf(fp,"%d\t",rand()%100);

}

// end=omp_get_wtime();
//printf("Execution time-:%f\n",(end-start));

}
