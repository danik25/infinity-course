/*******************************************************************************
*                Data Structures - Linear Sorting   
* file name: linear_sort_test.c                                             
* Related files: linear_sort.h linear_sort.c                               
* #Version: V 2.1                                                  
* writer: Dani Benjamin                                                         
* reviewer: Lev Shubert                                                     
* last update: 14.5.2019                                               
*******************************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /*memcmp */
#include <stdlib.h> /* rand */
#include <time.h> /* clock */
#include "linear_sort.h"

#define GREEN(str)      printf("\033[1;32m%s\033[0m\n", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str)     printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str)       printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str)     printf("\033[1;35m%s\033[0m\n", str)

#define UNUSED(x) (void)(x)

typedef struct people
    {
        float hight;
        char * name;
    }people_t;

typedef struct random_numbers
{
    int number;
    char * name;
}random_numbers_t;

/*counting conversion and print*/
static size_t KeyToNumInt(const void *key, const void *arg);
static size_t KeyToNumStruct(const void *key, const void *arg);
static void PrintStructNameAndHight(people_t *array, size_t size);
static void PrintInt(int *array, size_t size);

/*counting tests*/
static void TestCounting();
static void TestCountingInt(int *array, int *exp, size_t size, size_t range);
static void TestCountingStruct();
static void TestCountingBenchmark();

/*radix conversion and print*/
static size_t KeyToNumStructRadix(const void *key, const void *arg);
static void PrintStructRadix(random_numbers_t *array, size_t size);

/*radix tests*/
static void TestRadixInt();
static void TestRadixStruct();

/*function for qsort*/
static int IntIsBefore(const void *first, const void *second);

int main()
{
    CYAN("\n\n\t\t~TEST FILE SORT- count and radix~");
    CYAN("\t\t\t Dani Benjamin\n\n");
    YELLOW("\n********count********\n");
    TestCounting();
    
    YELLOW("\n********radix********\n");
    TestRadixInt();
    TestRadixStruct();
    
    PURPLE("\n********benckmark case********\n");
    TestCountingBenchmark();

    CYAN("\n\n\t\t\t   ~THE END~\n\n");
    return (0);
}

static void TestCounting()
{
    int array[] = {2, 5, 1, 9, 3};
    int exp[] = {1, 2, 3, 5, 9};
    size_t size = sizeof(array) / sizeof(int);
    PURPLE("\n********int case********\n");
    TestCountingInt(array, exp, size, 10);
    PURPLE("\n********struct case********\n");
    TestCountingStruct();
}

static void TestCountingInt(int *array, int *exp, size_t size, size_t range)
{
    size_t elm_size = sizeof(int);
    printf("before sorting:\n");
    PrintInt(array, size);
    CountingSort(array, size, elm_size, KeyToNumInt, NULL, range);
    printf("after sort:\n");
    PrintInt(array, size);
    (!memcmp(array, exp, size)) ? GREEN("success") : RED("fail");

}

static void TestCountingStruct()
{ 
    people_t array[] = 
    {{1.8, "A"},
    {1.75, "B"},
    {1.8, "C"},
    {1.6, "D"}};

    people_t exp[] =
    {{1.6, "D"},
    {1.75, "B"},
    {1.8, "A"},
    {1.8, "C"}};

    printf("before sorting:\n");
    PrintStructNameAndHight(array, sizeof(array) / sizeof(people_t));
    CountingSort(array, 4, sizeof(people_t), KeyToNumStruct, NULL, 181);
    printf("after sort:\n");
    PrintStructNameAndHight(array, sizeof(array) / sizeof(people_t));

    (!memcmp(array, exp, sizeof(array) / sizeof(people_t))) ? GREEN("success") : RED("fail");
}

static void TestCountingBenchmark()
{
    int arr1[5000] = {0};
    size_t i = 0 , j = 0;

    size_t sample_size = 20;
    size_t len = 5000;

    clock_t start_counting = 0;
    clock_t end_counting = 0;
    size_t counting_sum = 0;

    clock_t start_radix = 0;
    clock_t end_radix = 0;
    size_t radix_sum = 0;

    clock_t start_qsort = 0;
    clock_t end_qsort = 0;
    size_t qsort_sum = 0;

    for(i = 0; i < sample_size; ++i)
    {
        for (j = 0; j < len; ++j)
        {
            arr1[j] = rand()%10000;
        }
        start_qsort = clock();
        qsort(arr1, sizeof(arr1)/sizeof(int), sizeof(int), IntIsBefore);
        end_qsort = clock();
        qsort_sum += end_qsort - start_qsort;

        for (j = 0; j < len; ++j)
        {
            arr1[j] = rand()%20;
        }

        start_counting = clock();
        CountingSort(arr1, len, sizeof(int), KeyToNumInt, NULL, 21);
        end_counting = clock();
        counting_sum += end_counting - start_counting;

        for (j = 0; j < 5000; ++j)
        {
            arr1[j] = rand()%20;
        }

        start_radix = clock();
        RadixSort(arr1, len, sizeof(int), KeyToNumInt, NULL, 2);
        end_radix = clock();
        radix_sum += end_radix - start_radix;
    }

    printf("counting, avg: %f\n", 
                    ((double)(counting_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("radix, avg: %f\n", 
                    ((double)(radix_sum)/CLOCKS_PER_SEC) / sample_size);
    printf("qsort, avg: %f\n", 
                    ((double)(qsort_sum)/CLOCKS_PER_SEC) / sample_size);
}

static void TestRadixInt()
{
    int array[] = {12, 25, 31, 193, 13, 4};
    int exp[] = {4, 12, 13, 31, 25, 193};
    PURPLE("\n********int case********\n");
    printf("before sorting:\n");
    PrintInt(array, sizeof(array) / sizeof(int));
    RadixSort(array, sizeof(array) / sizeof(int), sizeof(int),
                 KeyToNumInt, NULL, 3);
    printf("after sort:\n");
    PrintInt(array, sizeof(array) / sizeof(int));
    (!memcmp(array, exp, sizeof(array) / sizeof(int))) ? 
                            GREEN("success") : RED("fail");
    printf("\n");
    
}

static void TestRadixStruct()
{ 
    random_numbers_t array[] = 
    {{12345, "A"},
    {7, "B"},
    {22222222, "C"},
    {31, "D"}};

    random_numbers_t exp[] =
    {{7, "B"},
    {31, "D"},
    {12345, "A"},
    {22222222, "C"}};

    printf("before sorting:\n");
    PrintStructRadix(array, sizeof(array) / sizeof(people_t));
    RadixSort(array, 4, sizeof(people_t), KeyToNumStructRadix, NULL, 8);
    printf("after sort:\n");
    PrintStructRadix(array, sizeof(array) / sizeof(people_t));

    (!memcmp(array, exp, sizeof(array) / sizeof(people_t))) ? 
                                    GREEN("success") : RED("fail");
    printf("\n");
}
/******************************counting****************************************/
/*============================================================================*/

static size_t KeyToNumInt(const void *key, const void *arg)
{
    UNUSED(arg);
    return (size_t)(*(int*)(key));
}

static size_t KeyToNumStruct(const void *key, const void *arg)
{
    UNUSED(arg);
    return ((size_t)((((people_t *)key)->hight) * 100));
}

/*============================================================================*/

static void PrintInt(int *array, size_t size)
{
    size_t i = 0;
    for(; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
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

/********************************radix*****************************************/
static size_t KeyToNumStructRadix(const void *key, const void *arg)
{
    UNUSED(arg);
    return ((size_t)((((random_numbers_t *)key)->number)));
}

static void PrintStructRadix(random_numbers_t *array, size_t size)
{
    size_t i = 0;
    for(; i < size; ++i)
    {
        printf("name: %s, number: %d \n", array[i].name, array[i].number);
    }
    printf("\n");
}
/*--------------------------qsort's function-------------------------------*/

static int IntIsBefore(const void *first, const void *second)
{
    if(*(int*)first < *(int*)second)
    {
        return (1);
    }
    return (0);
}