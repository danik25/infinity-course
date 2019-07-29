/****************************************************************
*                Data Structures - Heap
* file: heap.h
* Related files: heap.c heap_test.c
* #Version: V 1.1
* Writer: Dani Benjamin
* Reviewer: Moshe Greenberg
* Last update: 06/06/19
***************************************************************/
#include <stdio.h> /* printf */

#include "heap.h"
#include "colours.h"

#define UNUSED(x) (void)(x)

static void HeapTestCreate();
static void HeapTestInsertNPeek();
static void HeapTestRemoveNPop();
static void HeapTestSizeNIsEmpty();
static void HeapTestIntegration();

/* user functions */
static int CompareInt(const void *data1, const void *data2, void *param);
static int IsMatchInt(const void *data1, void *param);


int main()
{
    CYAN("\n\n\t   ~TEST FILE HEAP~");
    CYAN("\t     Dani Benjamin\n\n");
    
    YELLOW("\n********create test********\n");
    HeapTestCreate();
    YELLOW("\n********insert & peek test********\n");
    HeapTestInsertNPeek();
    YELLOW("\n********remove ans pop********\n");
    HeapTestRemoveNPop();
    YELLOW("\n********size & isempty test********\n");
    HeapTestSizeNIsEmpty();
    YELLOW("\n********integration********\n");
    HeapTestIntegration();

    CYAN("\n\t\t   THE END\n\n");
    return(0);
}

static void HeapTestCreate()
{
    heap_t *new_heap = HeapCreate(CompareInt, NULL);
    TEST(new_heap);
    HeapDestroy(new_heap);
}

static void HeapTestInsertNPeek()
{
    heap_t *new_heap = HeapCreate(CompareInt, NULL);
    int input[] = {5, 1, 7, 3, 0, 8};
    int exp[6] = {5, 1, 1, 1, 0, 0}; 
    size_t i = 0;
    int status = 0;

    /*if(HeapPeek(new_heap) != NULL)
    {
        status = 1;
    }
    */

    for(i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        HeapInsert(new_heap, &input[i]);
        if(*(int*)HeapPeek(new_heap) != exp[i])
        {
            status = 1;
        }
    }

    TEST(!status); 

    HeapDestroy(new_heap);
}

static void HeapTestRemoveNPop()
{
    heap_t *new_heap = HeapCreate(CompareInt, NULL);
    int input[9] = {1, 0, 8, 5, 3, 9, 4, 2, 18};
    int to_remove[9] = {1, 9, 8, 100, 0, 0, 0, 0, 0};
    int exp[] = {18, 8, 18};
    int ans = 0;
    void *null_ans = NULL;
    size_t i = 0;


    for(i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        HeapInsert(new_heap, &input[i]);
    }

    PURPLE("1. removing a branch\n"); 
    ans = *(int*)HeapRemove(new_heap, IsMatchInt, &to_remove[0]);
    TEST(HeapSize(new_heap) == 8 && ans == to_remove[0]); 

    PURPLE("\n2. removing a leaf\n"); 
    ans = *(int*)HeapRemove(new_heap, IsMatchInt, &to_remove[1]);
    TEST(HeapSize(new_heap) == 7 && ans == to_remove[1]);

    PURPLE("\n3. removing the last node\n"); 
    ans = *(int*)HeapRemove(new_heap, IsMatchInt, &to_remove[2]);
    TEST(HeapSize(new_heap) == 6 && ans == to_remove[2]);

    PURPLE("\n4. removing non existing element\n"); 
    null_ans = HeapRemove(new_heap, IsMatchInt, &to_remove[3]);
    TEST(HeapSize(new_heap) == 6 && null_ans == NULL);

    PURPLE("\n5. poping\n");
    HeapPop(new_heap);
    TEST(*(int*)HeapPeek(new_heap) != exp[2]);

    HeapDestroy(new_heap);
}

static void HeapTestSizeNIsEmpty()
{
    heap_t *new_heap = HeapCreate(CompareInt, NULL);
    int input[] = {5, 1, 7, 3, 2, 8};
    size_t i = 0;
    int status = 0;

    status = (!HeapIsEmpty(new_heap));

    for(i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        HeapInsert(new_heap, &input[i]);
        if(HeapSize(new_heap) != i + 1)
        {
            status = 1;
        }
    }

    if(HeapIsEmpty(new_heap))
    {
        status = 1;
    }

    TEST(!status);
    HeapDestroy(new_heap);
}

static void HeapTestIntegration()
{
    heap_t *new_heap = HeapCreate(CompareInt, NULL);

    int input[] = {7, 6, 5, 4, 3};

    int to_remove[5] = {3, 4, 5, 6, 7};
    int exp[] = {4, 5, 6, 7};
    int ans = 0;

    size_t i = 0;
    int status = 0;

    /* inserting */
    for(i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        HeapInsert(new_heap, &input[i]);
        if(*(int*)HeapPeek(new_heap) != input[i] || HeapSize(new_heap) != i + 1)
        {
            status = 1;
        }
    }

    /* removing */
    for(i = 0; i < sizeof(input) / sizeof(int) - 1; ++i)
    {
        ans = *(int*)HeapRemove(new_heap, IsMatchInt, &to_remove[i]);
        if(*(int*)HeapPeek(new_heap) != exp[i] && HeapSize(new_heap) == 5 - i 
                    && ans != to_remove[i])
        {
            status = 1;
        }
    }

    HeapPop(new_heap);

    /*if(HeapPeek(new_heap) != NULL && !HeapIsEmpty(new_heap))
    {
        status = 1;
    }*/

    HeapPop(new_heap);
    HeapRemove(new_heap, IsMatchInt, &to_remove[0]);

    TEST(!status);
    HeapDestroy(new_heap);
}

/*============================================================================*/

static int CompareInt(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    return(*(int*)data1 - *(int*)data2);
}

static int IsMatchInt(const void *data1, void *param)
{
    return(*(int*)data1 == *(int*)param);
}