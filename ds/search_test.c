/****************************************************************
*                      Search
*                   =====================
* File Name: search.h
* Related files: search.c, search_test.c
* #Version: V 1.0
* Writer: Dani Benjamin 
* Reviewer: Tom Valershtein
* Last update: 11.06.19
****************************************************************/

#include <stdio.h> /* printf */

#include "search.h"
#include "colours.h"

/* test functions */
static void TestSearch();
static void TestBinarySearchIter(int *arr, int *to_find, size_t arr_size, size_t loop_size);
static void TestBinarySearchRec(int *arr, int *to_find, size_t arr_size, size_t loop_size);
static void TestJumpSearch(int *arr, int *to_find, size_t arr_size, size_t loop_size);

/* user functions */
static int CompareInt(const void *data1, const void *data2);

#define TYPE int

int main()
{
    TestSearch();
    return(0);
}

static void TestSearch()
{
    int arr1[] = {1, 4, 7, 9, 10};
    int to_find1[] = {1, 10, 7, 12};

    int arr2[] = {5};
    int to_find2[] = {5, 3};


    YELLOW("\nbinary search iter\n");
    PURPLE("1. first, last, middle, doesnt exsists");
    TestBinarySearchIter(arr1, to_find1, sizeof(arr1) / sizeof(int), sizeof(to_find1) / sizeof(int));
    PURPLE("\n2. list with one element - exsists, doesnt exsists");
    TestBinarySearchIter(arr2, to_find2, sizeof(arr2) / sizeof(int), sizeof(to_find2) / sizeof(int));


    YELLOW("\nbinary search rec\n");
    PURPLE("1. first, last, middle, doesnt exsists");
    TestBinarySearchRec(arr1, to_find1, sizeof(arr1) / sizeof(int), sizeof(to_find1) / sizeof(int));
    PURPLE("\n2. list with one element - exsists, doesnt exsists");
    TestBinarySearchRec(arr2, to_find2, sizeof(arr2) / sizeof(int), sizeof(to_find2) / sizeof(int));
 

    YELLOW("\njump search rec\n");
    PURPLE("1. first, last, middle, doesnt exsists");
    TestJumpSearch(arr1, to_find1, sizeof(arr1) / sizeof(int), sizeof(to_find1) / sizeof(int));
    PURPLE("\n2. list with one element - exsists, doesnt exsists");
    TestJumpSearch(arr2, to_find2, sizeof(arr2) / sizeof(int), sizeof(to_find2) / sizeof(int));
   

    printf("\n");
    
    

}

static void TestBinarySearchIter(int *arr, int *to_find, size_t arr_size, size_t loop_size)
{
    size_t i = 0;
    for(i = 0; i < loop_size - 1; ++i)
    {
        TEST(*(int*)BinarySearchIter(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == to_find[i]);
    }
    TEST(BinarySearchIter(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == NULL);
}

static void TestBinarySearchRec(int *arr, int *to_find, size_t arr_size, size_t loop_size)
{
    size_t i = 0;
    for(i = 0; i < loop_size - 1; ++i)
    {
        TEST(*(int*)BinarySearchRec(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == to_find[i]);
    }
    TEST(BinarySearchRec(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == NULL);
}

static void TestJumpSearch(int *arr, int *to_find, size_t arr_size, size_t loop_size)
{
    size_t i = 0;
    for(i = 0; i < loop_size - 1; ++i)
    {
        TEST(*(int*)JumpSearch(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == to_find[i]);
    }
    TEST(JumpSearch(arr, arr_size, sizeof(int),
                                       CompareInt, &to_find[i]) == NULL);
}



/*============================================================================*/

static int CompareInt(const void *data1, const void *data2)
{
    return(*(int*)data1 - *(int*)data2);
}