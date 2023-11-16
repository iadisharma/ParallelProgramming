#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define SIZE 10000


void merge(int arr[],int l,int m,int r)
{
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	int L[n1],R[n2];
	for(i=0;i<n1;i++)
		L[i] = arr[l+i];
	for(j=0;j<n2;j++)
		R[j] = arr[m+1+j];
	
	i=0;
	j=0;
	k=l;
	
	while(i<n1 && j<n2)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while(i<n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while(j<n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergesort(int arr[],int l,int r)
{
	if(l<r)
	{
		int m = l+(r-l)/2;
		mergesort(arr,l,m);
		mergesort(arr,m+1,r);
		merge(arr,l,m,r);
	}
}


int main()
{
	int arr[SIZE],i=0;
	FILE* fp;
	fp = fopen("numbers.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d",&arr[i]);
		i++;
	}
	double start,end;
	start = omp_get_wtime();
	int size = sizeof(arr)/sizeof(arr[0]);
	mergesort(arr,0,size-1);
	/*for(int i=0;i<size;i++)
	{
		printf("%d\n",arr[i]);
	}
	*/
	end = omp_get_wtime();
	printf("\n Serial Execution time: %f\n",end-start);
	
	
	return 0;
}
