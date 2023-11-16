#include<stdio.h>
#include<stdlib.h>

void main(){
	FILE *f1;
	f1=fopen("num.txt","w");
	for(int i = 0; i < 10; i++){
		fprintf(f1,"%d\n", rand()%10);
	}
}
