/*******************************************************************************
*                Data Structures - quick sort   
* file name: linear_sort.h                                              
* Related files: quick_sort.c quick_sort_test.c                               
* #Version:                                                  
* writer: Dani Benjamin                                                         
* reviewer: Michal Adler                                                
* last update: 10.6.2019                                               
*******************************************************************************/
#include <stdio.h> /* printf */
#include <string.h> /*memcmp */
#include <stdlib.h> /* rand */
#include <time.h> /* clock */

#include "heap_quick_sort.h"
#include "colours.h"

typedef struct people
{
    float hight;
    char * name;
}people_t;

static int IntCompare(const void *first, const void *second);
static int StructCompare(const void *first, const void *second);
static int WordCompare(const void *first, const void *second);

static void PrintInt(int *arr, size_t size);
static void PrintChar(char **arr, size_t size);
static void PrintStructNameAndHight(people_t *array, size_t size);

static int IsSame(int *arr, int *exp, size_t size);
static int IsSameStruct(people_t *arr, people_t *exp, size_t size);
static void CheckSortInt(int *arr, int *exp, size_t size);
static void CheckSortChar(char **arr, char **exp, size_t size);

static void QuickSortTest();
static void TestStruct();



int main()
{
    CYAN("\n\n\t\t\t~TEST FILE QUICK SORT~");
    CYAN("\t\t\t     Dani Benjamin\n\n");
    YELLOW("\n********quick sort test********\n");
    QuickSortTest();
    YELLOW("\n********quick sort test with struct********\n");
    TestStruct();
    CYAN("\n\n\t\t\t\t ~THE END~\n\n");
    return (0);
}

static void QuickSortTest()
{
    int arr1[] = {3, 2};
    int exp1[] = {2, 3};
    int arr2[] = {5, 17, 0, 18, -5, 8, -55};
    int exp2[] = {-55, -5, 0, 5, 8, 17, 18};
    char* arr_str[] = {"oded's", "zapper", "kobi","zapper's", "dani's", "oded", "zombi's", "zombi"};
    char* exp_str[] = {"dani", "dani's", "kobi", "oded", "oded's", "zombi", "zombi's"};

    int sample_size = 30;

    clock_t start_q = 0;
    clock_t end_q = 0;
    size_t sum_q = 0;
    clock_t start_q_lib = 0;
    clock_t end_q_lib = 0;
    size_t sum_q_lib = 0;

    int arr3[5000] = {0};

    int i = 0 , j = 0;

    PURPLE("1.");
    CheckSortInt(arr1, exp1, sizeof(arr1)/sizeof(int));

    PURPLE("\n2.");
    CheckSortInt(arr2, exp2, sizeof(arr2)/sizeof(int));

    PURPLE("\nstr.");
    CheckSortChar(arr_str, exp_str, sizeof(arr_str)/sizeof(char*));

    PURPLE("\n3. 5000 randomized numbers");
    for(i = 0; i < sample_size; ++i)
    {
        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }
        start_q_lib = clock();
        qsort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntCompare);
        end_q_lib = clock();
        sum_q_lib += end_q_lib - start_q_lib;

        for (j = 0; j < 5000; ++j)
        {
            arr3[j] = rand()%20;
        }

        start_q = clock();
        QuickSort(arr3, sizeof(arr3)/sizeof(int), sizeof(int), IntCompare);
        end_q = clock();
        sum_q += end_q - start_q;
    }

    printf("new written qsort, avg: %f\n", 
                    ((double)(sum_q)/CLOCKS_PER_SEC) / sample_size);
    printf("library qsort, avg: %f\n", 
                    ((double)(sum_q_lib)/CLOCKS_PER_SEC) / sample_size);
    
}

static void CheckSortInt(int *arr, int *exp, size_t size)
{
    printf("before sort-\n");
    PrintInt(arr, size);
    QuickSort(arr, size, sizeof(int), IntCompare);
    printf("after sort-\n");
    PrintInt(arr, size);

    TEST(IsSame(arr, exp, size));
}

static void CheckSortChar(char **arr, char **exp, size_t size)
{
    printf("before sort-\n");
    PrintChar(arr, size);
    QuickSort(arr, size, sizeof(char*), WordCompare);
    printf("after sort-\n");
    PrintChar(arr, size);

    /*TEST(IsSame(arr, exp, size));*/
}

static void TestStruct()
{ 
    people_t array[] = 
    {{1.8, "A"},
    {1.75, "B"},
    {1.8, "C"},
    {1.6, "D"}};

    people_t exp[] =
    {{1.6, "D"},
    {1.75, "B"},
    {1.8, "C"},
    {1.8, "A"}};

    printf("before sorting:\n");
    PrintStructNameAndHight(array, sizeof(array) / sizeof(people_t));

    QuickSort(array, sizeof(array) / sizeof(people_t), sizeof(people_t),
                                                         StructCompare);
    printf("after sort:\n");
    PrintStructNameAndHight(array, sizeof(array) / sizeof(people_t));

    TEST(IsSameStruct(array, exp, sizeof(array) / sizeof(people_t)));
}

/*************************static functions*************************/

static int IntCompare(const void *first, const void *second)
{
    return(*(int*)first - *(int*)second);
}

static int WordCompare(const void *first, const void *second)
{
    return(strcmp(*(char**)first, *(char**)second));
}

static int StructCompare(const void *first, const void *second)
{
    if((float)(((people_t*)first)->hight < ((people_t*)second)->hight))
    {
        return(-1);
    }
    if((float)(((people_t*)first)->hight > ((people_t*)second)->hight))
    {
        return(1);
    }
    return(0);
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

static void PrintChar(char **arr, size_t size)
{
    printf("the array:\n");
    while(size > 0)
    {
        printf("%s ", *arr);
        ++arr;
        --size;
    }
    printf("\n\n");
}

static void PrintStructNameAndHight(people_t *array, size_t size)
{
    size_t i = 0;
    for(; i < size; ++i)
    {
        printf("name: %s, hight: %.2f \n", array[i].name, array[i].hight);
    }
    printf("\n");
}

static int IsSame(int *arr, int *exp, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        if(arr[i] != exp[i])
        {
            return(0);
        }
    }
    return(1);
}

static int IsSameStruct(people_t *arr, people_t *exp, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        if(arr[i].hight != exp[i].hight)
        {
            return(0);
        }
    }
    return(1);
}