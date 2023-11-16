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
        #pragma omp parallel
        {
                #pragma omp for
                for (int i = 1; i < SIZE - 1; i += 2)
                {
                        if (a[i] > a[i + 1])
                        {
                                #pragma omp critical
                                {
                                        temp = a[i];
                                        a[i] = a[i + 1];
                                        a[i + 1] = temp;
                                        odd = 1;
                                }
                        }
                }
                if (odd == 1)
                {
                        printArray(a, SIZE);
                        printf("\t\tODD SORT\n\n");
                }
        }
}

void even_sort(int a[])
{
        int temp, even = 0;
        #pragma omp parallel
        {
                #pragma omp for
                for (int i = 0; i < SIZE - 1; i += 2)
                {
                        if (a[i] > a[i + 1])
                        {
                                #pragma omp critical
                                {
                                        temp = a[i];
                                        a[i] = a[i + 1];
                                        a[i + 1] = temp;
                                        even = 1;
                                }
                        }
                }
                if (even == 1)
                {
                        printArray(a, SIZE);
                        printf("\t\tEVEN SORT\n\n");
                }
        }
}

void transposition_sort(int a[])
{
        #pragma omp parallel
        {
                #pragma omp for
                for (int i = 0; i < SIZE; i++)
                {
                        odd_sort(a);
                        even_sort(a);
                }
        }
}

void main()
{
        int a[SIZE];
        double t1_parallel, t2_parallel;
        FILE *fp;
        fp = fopen("num.txt", "r");
        if (fp == NULL)
        {
                printf("FAILED to READ\n");
        }
        for (int j = 0; j < SIZE; j++)
        {
                fscanf(fp, "%d", &a[j]);
        }
        fclose(fp);

        printf("Unsorted Array:\n");
        printArray(a, SIZE);

        printf("\n\nSORTING....\n\n");

        t1_parallel = omp_get_wtime();
        #pragma omp single
        {
                transposition_sort(a);
        }
        t2_parallel = omp_get_wtime();

        printf("\nSorted Array: \n");
        printArray(a, SIZE);

        printf("\n\nExecution Time(Parallel): %lf", t2_parallel - t1_parallel);
}
