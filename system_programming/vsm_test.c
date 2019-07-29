/******************************************************************************
 * File name  : VARIABLE SIZE MEMORY ALLOCATION
 * Version    : 1.2
 * Developer  : Dani Benjmain
 * Reviewer   : Or Stopiky
 * Date       : 1.5.19
 ******************************************************************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "vsm.h"

#define GREEN(str) printf("\033[1;32m%s\033[0m\n", str)
#define RED(str) printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str) printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str) printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str) printf("\033[1;35m%s\033[0m\n", str)

static void VsmTest();
static void InitTest();
static void AllocTest();
static void FreeTest();
static void FindLargestChunkTest();

int main()
{
    CYAN("\n\n\t\t\t~TEST FILE VSM~");
    CYAN("\t\t\t Dani Benjamin\n\n");
    
    VsmTest();
    YELLOW("\n********alloc test********\n");
    InitTest();
    YELLOW("\n********alloc test********\n");
    AllocTest();
    YELLOW("\n********free test********\n");
    FreeTest();
    YELLOW("\n********find largest chunk test********\n");
    FindLargestChunkTest();

    CYAN("\n\n\t\t\t   ~THE END~\n\n");
    return(0);
}

static void VsmTest()
{
    void *vsm = (void*)malloc(100);
    vsm = VSMInit(vsm, 100);

    free(vsm);
}

static void InitTest()
{
    void *vsm = (void*)malloc(15);
    void *tmp = NULL;
    PURPLE("1. asking for a size too small:");
    
    tmp = VSMInit(vsm, 15);
    (!tmp) ? GREEN("success") : RED("fail");

    free(vsm);
}

static void AllocTest()
{
    void *vsm = (void*)malloc(100);
    void* tmp = NULL;
    void* allocs[] = {0, 0, 0};
    vsm = VSMInit(vsm, 100);

    PURPLE("1. asking for a size too big:");
    tmp = VSMAlloc(vsm, 100);
    (!tmp) ? GREEN("success") : RED("fail");

    PURPLE("\n2. allocating the whole memory:");
    /* allocating the whole memory */
    allocs[0] = VSMAlloc(vsm, 30);
    allocs[1] = VSMAlloc(vsm, 16);
    allocs[2] = VSMAlloc(vsm, 15);

    ((char*)allocs[2] - (char*)allocs[1] == 24 && (char*)allocs[1] - 
    (char*)allocs[0] == 40 &&  (char*)allocs[2] - (char*)allocs[0] == 64) 
                ? GREEN("success") : RED("fail");

    free(vsm);
}

static void FreeTest()
{
    void *vsm = (void*)malloc(168);
    void* allocs[] = {0, 0, 0, 0, 0};
    vsm = VSMInit(vsm, 168);

    /*allocating 5 allocations*/
    allocs[0] = VSMAlloc(vsm, 10);
    allocs[1] = VSMAlloc(vsm, 20);
    allocs[2] = VSMAlloc(vsm, 32);
    allocs[3] = VSMAlloc(vsm, 8);
    allocs[4] = VSMAlloc(vsm, 40);

    VSMFree(allocs[1]);
    VSMFree(allocs[2]);

    (VSMFindLargestChunk(vsm) == 64) ? GREEN("success") : RED("fail");

    free(vsm);
}

static void FindLargestChunkTest()
{
    void *vsm = (void*)malloc(168);
    size_t i = 0;
    int status = 0;
    void* allocs[] = {0, 0, 0, 0, 0};
    int chunks[] = {10, 20, 32, 8, 40};
    size_t exp_size[] = {152, 128, 96, 56, 40, 0};
    vsm = VSMInit(vsm, 168);

    for(; i < sizeof(allocs) / sizeof(void*); ++i)
    {
        if(VSMFindLargestChunk(vsm) != exp_size[i])
        {
            status = 1;
        }
        allocs[i] = VSMAlloc(vsm, chunks[i]);
    }
    if(VSMFindLargestChunk(vsm) != exp_size[i])
    {
        status = 1;
    }
    PURPLE("1. checking size after ech allocation");
    (!status) ? GREEN("success") : RED("fail");

    /*freeing the edges*/
    VSMFree(allocs[0]);
    VSMFree(allocs[4]);

    PURPLE("\n2. checking while freeing and allocating");
    (VSMFindLargestChunk(vsm) == 40) ? GREEN("success") : RED("fail");

    VSMFree(allocs[2]);
    VSMFree(allocs[3]);
    (VSMFindLargestChunk(vsm) == 96) ? GREEN("success") : RED("fail");

    allocs[2] = VSMAlloc(vsm, 48);
    (VSMFindLargestChunk(vsm) == 40) ? GREEN("success") : RED("fail");

    free(vsm);
}