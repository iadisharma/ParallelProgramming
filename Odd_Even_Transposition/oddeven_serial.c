#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 10

void printArray(int a[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
}

void odd_sort(int a[])
{
	int temp, odd = 0;
        for (int i = 1; i < SIZE - 1; i += 2)
        {
        	if (a[i] > a[i+1]){
                	temp = a[i];
                	a[i] = a[i + 1];
                	a[i + 1] = temp;
                	odd = 1;
                }
        }
       	if (odd == 1)
        {
        	printArray(a, SIZE);
                printf("\t\tODD SORT\n\n");
        }

}

void even_sort(int a[])
{
	int temp, even = 0;
	for (int i = 0; i < SIZE - 1; i += 2)
        {
        	if (a[i] > a[i + 1])
                {
                	temp = a[i];
                        a[i] = a[i + 1];
                        a[i + 1] = temp;
                        even = 1;
                }
        }
        if (even == 1)
        {
       		printArray(a, SIZE);
        	printf("\t\tEVEN SORT\n\n");
        }
}

void transposition_sort(int a[]){
	for(int i = 0; i < SIZE; i++){
		odd_sort(a);
		even_sort(a);
	}
}

void main()
{
    int a[SIZE];
    double t1_serial, t2_serial;
    FILE * fp;
    fp = fopen("num.txt", "r");
    if(fp == NULL){
    	printf("FAILED to READ\n");
    }
    for(int j = 0; j < SIZE; j++){
    	fscanf(fp, "%d", &a[j]);
    }
    fclose(fp);
    printf("Unsorted Array:\n");
    printArray(a, SIZE);

    printf("\n\nSORTING....\n\n");

    t1_serial = omp_get_wtime();
    transposition_sort(a);
    t2_serial = omp_get_wtime();

    printf("\nSorted Array: \n");
    printArray(a, SIZE);

    printf("\nExecution Time(Serial): %lf", t2_serial - t1_serial);
    printf("\n");
}

