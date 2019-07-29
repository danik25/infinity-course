/****************************************************************

*                      Merge Sort

*                       =====================

* File Name: merge_sort.h

* Related files: merge_sort.c   merge_sort_test.c

* #Version: V 1.1

* Writer: Dani Benjamin      

* Reviewer: Tom Valershtein     

* Last update: 04.06.2019

****************************************************************/

#include <stdio.h>
#include "merge_sort.h"
#include "colours.h"

static void MergeTest();
static int IsBeforeInt(const void *data1, const void *data2);
static void PrintInt(int *arr, size_t size);

int main()
{
    CYAN("\n\n\t    ~TEST FILE MERGE SORT~");
    CYAN("\t\tDani Benjamin\n\n");
    YELLOW("\n********merge test********\n");
    MergeTest();
    

    CYAN("\n\t\t   THE END\n\n");
    return(0);
}

static void MergeTest()
{
    int array[] = {2, 8, 5, 3, 9, 4, 1};
    printf("before: \n");
    PrintInt(array, sizeof(array) / sizeof(int));
    MergeSort(array,
              sizeof(array) / sizeof(int),
              sizeof(int),                                                                                                                                                                                 
              IsBeforeInt);
    printf("after: \n");
    PrintInt(array, sizeof(array) / sizeof(int));
}

static int IsBeforeInt(const void *data1, const void *data2)
{
    return(*(int*)data1 < *(int*)data2);
}

static void PrintInt(int *arr, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        printf("%d -> ", arr[i]);
    }
    printf("\n");
}
