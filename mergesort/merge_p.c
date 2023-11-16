#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
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


    void merge_sort(int arr[],int left,int right){
            if(left<right){
                int mid=left+(right-left)/2;
                #pragma omp parallel
                {
                    #pragma omp sections
                    {
                        #pragma omp section
                        {
                        merge_sort(arr,left,mid);
                        }
                        #pragma omp section
                        {
                        merge_sort(arr,mid+1,right);
                        }
                        #pragma omp section
                        {
                        merge(arr,left,mid,right);
                        }
                    }
                }
            }
        }
        
int main(){
        
        int arr[SIZE],i=0;
	FILE* fp;
	fp = fopen("numbers.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d",&arr[i]);
		i++;
	}
        int size = sizeof(arr)/sizeof(arr[0]);
        double t1=omp_get_wtime();
	#pragma omp parallel
    	{
  	merge_sort(arr,0,size-1);
	}
	double t2=omp_get_wtime();
	/*
	printf("Sroted array is-:\n");
	for(int i=0;i<size;i++){
	printf("%d\n",arr[i]);
	}
	*/
	printf("\n Parallel Execution time: %f\n",t2-t1);
}
        
