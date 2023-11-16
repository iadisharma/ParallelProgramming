#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

#define SIZE 1000

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; 
	int i = (low - 1); 
	for (int j = low; j <= high- 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++; 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}


void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
			quickSort(arr,low, pi - 1);
			quickSort(arr, pi + 1, high);
	}
}


void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
	printf("%d\n", arr[i]);
	printf("\n");
}


int main()
{
	double start_time, run_time;
	int arr[SIZE],i=0;
	FILE* fp;
	fp = fopen("numbers.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d",&arr[i]);
		i++;
	}
	int n = sizeof(arr)/sizeof(arr[0]);
	start_time = omp_get_wtime();
	quickSort(arr, 0, n-1);
	run_time = omp_get_wtime() - start_time;
	printf("Sorted array: \n");
	printArray(arr, n);
  	printf("\n");
	printf("\nSerial Execution time was %lf seconds\n ",run_time);
	
	return 0;
}
