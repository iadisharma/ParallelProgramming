#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

#define ARRAY_MAX_SIZE 1000
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


void quicksort(int arr[], int low, int high)
{
	if (low < high)
	{

		int pi = partition(arr, low, high);

		#pragma omp task firstprivate(arr,low,pi)
		{
			quicksort(arr,low, pi - 1);

		}
		#pragma omp task firstprivate(arr, high,pi)
		{
			quicksort(arr, pi + 1, high);

		}


	}
}


void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d\t ", arr[i]);
	printf("\n");
}


int main()
{


	double start_time, run_time;
  	int arr[ARRAY_MAX_SIZE],i=0;
		FILE* fp;
	fp = fopen("numbers.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d",&arr[i]);
		i++;
	}
	int n = sizeof(arr)/sizeof(arr[0]);


		int pi = partition(arr, 0, n-1);

#pragma omp parallel sections
{
		#pragma omp section
		{
			quicksort(arr,0, pi - 1);
		}
		#pragma omp section
		{
			quicksort(arr, pi + 1, n-1);
		}
}
omp_set_num_threads(8);
start_time = omp_get_wtime();
#pragma omp parallel
 {
	
	 int id = omp_get_thread_num();
    	 int nthrds = omp_get_num_threads();
	 //printf("Thread is %d\n",id);
	 #pragma omp single nowait
	 {

	 	quicksort(arr, 0, n-1);

	 }
}
	quicksort(arr,0,n-1);
	run_time = omp_get_wtime() - start_time;
	printf("\nParallel Execution time was %lf seconds\n ",run_time);
	//printf("Sorted array: \n");
//	printArray(arr, n);
  	printf("\n");
	return 0;
}
