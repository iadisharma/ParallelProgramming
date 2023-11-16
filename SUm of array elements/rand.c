#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE *f1;
	int n;
	printf("Enter the no of ramdom numbers to be generated:- ");
	scanf("%d",&n);
	f1= fopen("Number.txt","w");
	for(int i=0;i<n;i++){
		fprintf(f1,"%d \n",rand()%n);
	}
	return 0;
}
