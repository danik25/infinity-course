/*******************************************************************************
*                Data Structures - Sorting  
* file name: sort_test.c                                             
* Related files: sort.c sort.h                              
* #Version: V 1.0                                                  
* writer: Dani Benjamin                                         
* reviewer: Oded Bryt                                          
* last update: 08.05.19                                        
*******************************************************************************/
#include <stdio.h> /* printf */
#include <string.h> /*memcmp */
#include <stdlib.h> /* rand */
#include <time.h> /* clock */
#include "sort.h"

#define GREEN(str)      printf("\033[1;32m%s\033[0m\n", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str)     printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str)       printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str)     printf("\033[1;35m%s\033[0m\n", str)

static int IntIsBefore(const void *first, const void *second);
static void PrintInt(int *arr, size_t size);

static void BubbleSortTest();
static void InsertionSortTest();
static void SelectionSortTest();

int main()
{
    CYAN("\n\n\t\t\t~TEST FILE SORT~");
    CYAN("\t\t\t  Dani Benjamin\n\n");
    YELLOW("\n********bubble sort test********\n");
    BubbleSortTest();
    YELLOW("\n********insertion sort test********\n");
    InsertionSortTest();
    YELLOW("\n********selection sort test********\n");
    SelectionSortTest();
    CYAN("\n\n\t\t\t   ~THE END~\n\n");
    return (0);
}

static void BubbleSortTest()
{
    int arr1[] = {3, 2};
    int exp1[] = {2, 3};
    int arr2[] = {5, 1, 4, 2, 8, 7, 13, 0, 2, 25, 12};
    int exp2[] = {0, 1, 2, 2, 4, 5, 7, 8, 12, 13, 25};

    int sample_size = 30;

    clock_t start_bubble = 0;
    clock_t end_bubble = 0;
    size_t bubble_sum = 0;
    clock_t start_qsort = 0;
    clock_t end_qsort = 0;
    size_t qsort_sum = 0;

    int arr3[5000] = {0};

    /*for flag efficiency check*/
    int arr4[5000] = {0};
    int arr5[5000] = {0};
    int num = 0;
    size_t sorted_sum = 0;
    size_t unsorted_sum = 0;

    int i = 0 , j = 0;

    PURPLE("1.");
    printf("before sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));
    BubbleSort(arr1, sizeof(arr1)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));

    (!memcmp(arr1, exp1, sizeof(arr1)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");

    PURPLE("\n2.");
    printf("before sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));
    BubbleSort(arr2, sizeof(arr2)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));

    (!memcmp(arr2, exp2, sizeof(arr2)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");

    PURPLE("\n3. 5000 randomized numbers");
    for(i = 0; i < sample_size; ++i)
    {
        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }
        start_qsort = clock();
        qsort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_qsort = clock();
        qsort_sum += end_qsort - start_qsort;

        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }

        start_bubble = clock();
        BubbleSort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_bubble = clock();
        bubble_sum += end_bubble - start_bubble;
    }

    printf("bubble, avg: %f\n", 
                    ((double)(bubble_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("qsort, avg: %f\n", 
                    ((double)(qsort_sum)/CLOCKS_PER_SEC) / sample_size);

    PURPLE("\n4. checking the efficiency of the flag");
    for(i = 0; i < sample_size; ++i)
    {
        num = 0;
        for (j = 0; j < 5000; ++j)
        {
            arr4[j] = num;
            ++num;
        }
        start_bubble = clock();
        BubbleSort(arr4, sizeof(arr4)/sizeof(int), sizeof(int), IntIsBefore);
        end_bubble = clock();
        sorted_sum += end_bubble - start_bubble;

        for (j = 0; j < 5000; ++j)
        {
            arr5[j] = rand()%20;
        }

        start_bubble = clock();
        BubbleSort(arr5, sizeof(arr5)/sizeof(int), sizeof(int), IntIsBefore);
        end_bubble = clock();
        unsorted_sum += end_bubble - start_bubble;
    }

    printf("sorted bubble: %f\n", 
                    ((double)(sorted_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("unsorted bubble: %f\n", 
                    ((double)(unsorted_sum)/CLOCKS_PER_SEC) / sample_size);
    
}

static void InsertionSortTest()
{
    int arr1[] = {1, 2};
    int exp1[] = {1, 2};
    int arr2[] = {0, 5, 1, 4, 2, 8, 7, 0};
    int exp2[] = {0, 0, 1, 2, 4, 5, 7, 8};
    int sample_size = 30;

    clock_t start_insertion = 0;
    clock_t end_insertion = 0;
    size_t insertion_sum = 0;
    clock_t start_qsort = 0;
    clock_t end_qsort = 0;
    size_t qsort_sum = 0;

    int arr3[5000] = {0};

    int i = 0 , j = 0;

    PURPLE("1.");
    printf("before sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));
    InsertionSort(arr1, sizeof(arr1)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));

    (!memcmp(arr1, exp1, sizeof(arr1)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");

    PURPLE("\n2.");
    printf("before sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));
    InsertionSort(arr2, sizeof(arr2)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));

    (!memcmp(arr2, exp2, sizeof(arr2)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");

                                                                PURPLE("\n3. 5000 randomized numbers");
    for(i = 0; i < sample_size; ++i)
    {
        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }
        start_qsort = clock();
        qsort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_qsort = clock();
        qsort_sum += end_qsort - start_qsort;

        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }
        start_insertion = clock();
        InsertionSort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_insertion = clock();
        insertion_sum += end_insertion - start_insertion;
    }

    printf("insertion, avg: %f\n", 
                    ((double)(insertion_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("qsort, avg: %f\n", 
                    ((double)(qsort_sum)/CLOCKS_PER_SEC) / sample_size);
}

static void SelectionSortTest()
{
    int arr1[] = {3, 2};
    int exp1[] = {2, 2};
    int arr2[] = {0, 5, 1, 17, 17, 8, 7, 0};
    int exp2[] = {0, 0, 1, 5, 7, 8, 17, 17};
    int sample_size = 30;

    clock_t start_selection = 0;
    clock_t end_selection = 0;
    size_t selection_sum = 0;
    clock_t start_qsort = 0;
    clock_t end_qsort = 0;
    size_t qsort_sum = 0;

    int arr3[5000] = {0};

    int i = 0 , j = 0;

    PURPLE("1.");
    printf("before sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));
    SelectionSort(arr1, sizeof(arr1)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr1, sizeof(arr1)/sizeof(int));

    (!memcmp(arr1, exp1, sizeof(arr1)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");

    PURPLE("\n2.");
    printf("before sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));
    SelectionSort(arr2, sizeof(arr2)/sizeof(int), sizeof(int), IntIsBefore);
    printf("after sort-\n");
    PrintInt(arr2, sizeof(arr2)/sizeof(int));
    (!memcmp(arr2, exp2, sizeof(arr2)/sizeof(int))) ? GREEN("success") : 
                                                                RED("fail");
    for(i = 0; i < sample_size; ++i)
    {
        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }
        start_qsort = clock();
        qsort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_qsort = clock();
        qsort_sum += end_qsort - start_qsort;

        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }

        start_selection = clock();
        SelectionSort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntIsBefore);
        end_selection = clock();
        selection_sum += end_selection - start_selection;
    }

    printf("selection, avg: %f\n", 
                    ((double)(selection_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("qsort, avg: %f\n", 
                    ((double)(qsort_sum)/CLOCKS_PER_SEC) / sample_size);

}

/*************************static functions*************************/

static int IntIsBefore(const void *first, const void *second)
{
    if(*(int*)first < *(int*)second)
    {
        return (1);
    }
    return (0);
}

static void PrintInt(int *arr, size_t size)
{
    printf("the array:\n");
    while(size > 0)
    {
        printf("%d ", *arr);
        ++arr;
        --size;
    }
    printf("\n\n");
}