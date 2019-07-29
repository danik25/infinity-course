/******************************************************************************
 * File name  : VARIABLE SIZE MEMORY ALLOCATION
 * Version    : 1.2
 * Developer  : Dani Benjmain
 * Reviewer   : Or Stopiky
 * Date       : 1.5.19
 ******************************************************************************/
 
#include <sys/types.h> /* ssize_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* abs */
#include "vsm.h"
 
#define END 0
#define WORD_SIZE 8
#define BYTE_SIZE 1
#define HEADER_SIZE sizeof(vsm_t)
#define TAIL_HEADER_SIZE sizeof(vsm_t)
#define PADDING(x) (WORD_SIZE - x % WORD_SIZE) % WORD_SIZE 
#define NEG(x) (-x)

struct vsm_block_header
{
    ssize_t block_size;/* negative number represents free space while positive
                          number represents allocated space. */
};


static void VSMDefrag(vsm_t *vsm_handle);

/***************************************************************************/

vsm_t *VSMInit(void *pool, size_t pool_size)
{
    char* flag = NULL;
    vsm_t* handle = NULL;

    assert(pool);

    if(pool_size < HEADER_SIZE + TAIL_HEADER_SIZE + BYTE_SIZE)
    {
        return (NULL);
    }

    /*assigning the END flag*/
    flag = (char*)pool + pool_size - WORD_SIZE;
    ((vsm_t*)flag)->block_size = END;

    handle = pool;
    handle->block_size = NEG((pool_size - HEADER_SIZE - TAIL_HEADER_SIZE));

    return (handle);
}

/***************************************************************************/

void *VSMAlloc(vsm_t *vsm_handle, size_t byte_num)
{
    char* runner = NULL;
    void* return_runner = NULL;
    ssize_t actual_size = 0;
    ssize_t tmp_size = 0;

    assert(vsm_handle);

    VSMDefrag(vsm_handle);
    runner = (char*)vsm_handle;
    actual_size = byte_num + PADDING(byte_num);

    /* run until arriving to a space big enough for requested size, 
                                                    but not the end */
    while(NEG(((vsm_t*)runner)->block_size) < actual_size && 
                                ((vsm_t*)runner)->block_size != END)
    {
        runner += abs(((vsm_t*)runner)->block_size) + HEADER_SIZE;
    }
    if(((vsm_t*)runner)->block_size == END || 0 == actual_size)
    {
        return (NULL);
    }

    /* enough space for requested size, another header and a word size block*/
    if (NEG((((vsm_t*)runner)->block_size)) >= actual_size + 
                                        WORD_SIZE + (ssize_t)HEADER_SIZE)
    {
        return_runner = (char*)runner + HEADER_SIZE;

        tmp_size = ((vsm_t*)runner)->block_size;

        ((vsm_t*)runner)->block_size = actual_size;
        /* creating the next header */
        runner += actual_size + HEADER_SIZE;
        ((vsm_t*)runner)->block_size = NEG((abs(tmp_size) - actual_size - 
                                                                HEADER_SIZE));

        return (return_runner);
    }

    ((vsm_t*)runner)->block_size = NEG((((vsm_t*)runner)->block_size));
    return ((char*)runner + HEADER_SIZE);
}

/***************************************************************************/

void VSMFree(void *block_addr)
{
    char* runner = NULL;

    assert(block_addr);

    runner = (char*)block_addr;
    runner -= HEADER_SIZE;

    ((vsm_t*)runner)->block_size = NEG((((vsm_t*)runner)->block_size));
}

/***************************************************************************/

size_t VSMFindLargestChunk(vsm_t *vsm_handle)
{
    char* runner = NULL;
    size_t max_size = 0;

    assert(vsm_handle);

    VSMDefrag(vsm_handle);

    runner = (char*)vsm_handle;

    while(((vsm_t*)runner)->block_size != END)
    {
        if(NEG(((vsm_t*)runner)->block_size) > (ssize_t)max_size)
        {
            max_size = abs(((vsm_t*)runner)->block_size);
        }
        runner += abs(((vsm_t*)runner)->block_size) + HEADER_SIZE;
    }
    return(max_size);
}

/*============================================================================*/

static void VSMDefrag(vsm_t *vsm_handle)
{
    char* base = NULL;
    char* runner = NULL;
    ssize_t sum = 0;

    assert(vsm_handle);

    base = (char*)vsm_handle;
    runner = (char*)vsm_handle;
    sum = 0;

    while(((vsm_t*)runner)->block_size != END)
    {
        /* run while blocks are free, and not reaching the end */
        while(((vsm_t*)runner)->block_size < 0 && 
                                    ((vsm_t*)runner)->block_size != END)
        {
            sum += ((vsm_t*)runner)->block_size - HEADER_SIZE;
            runner += abs(((vsm_t*)runner)->block_size) + HEADER_SIZE;
        }
        if (sum != 0)
        {
            ((vsm_t*)base)->block_size = sum + HEADER_SIZE;
        }
        /* updating the base with the new sum */
        if(((vsm_t*)runner)->block_size != END)
        {
            runner += abs(((vsm_t*)runner)->block_size) + HEADER_SIZE;
        }
        
        base = runner;
        sum = 0;  
    }
}
