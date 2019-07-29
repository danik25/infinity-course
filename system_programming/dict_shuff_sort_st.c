/****************************************************************
*        dictionary shuffle and sort mt - Single Threaded       
* file: dict_shuff_sort_st.c
* Related files: dict_shuff_sort_st_test.c, dict_shuff_sort_st.h      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Oded Bryt
* Last update: 03/07/19
****************************************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include <sys/types.h> /* ssizest */
#include <pthread.h> /* pthread_create */


#include "dict_shuff_sort_st.h"
#include "dani_utilities.h"

/************************** threaded qsrot functions **************************/

#define MAX_DEPTH 4

typedef struct QSORT
{
    char *array;
    size_t start;
    size_t end;
    size_t element_size;
    compare_t CompareFunc;
    size_t depth;
}sort_var_t;
                                                   
static void* QuickSortRecMT(void* param);

static void AssignStruct(sort_var_t* thread_handle,  char *array, size_t start, 
            size_t end, size_t element_size, size_t depth, compare_t CompareFunc);



/******************************************************************************/
/*////////////////////////////////////////////////////////////////////////////*/
/************************** no threads qsrot functions ************************/
static int QuickSortRec(char *array, size_t start, size_t end, 
                                size_t element_size, compare_t CoompareFunc);

/******************************************************************************/

/* mutual functions*/
static int SwapData(char *array, size_t index_1, size_t index_2, 
                                                        size_t element_size);
static int Partition(char *array, ssize_t * start_index, 
            ssize_t * end_index, ssize_t * pivot_index, 
            compare_t CompareFunc, 
            size_t element_size);



/*============================================================================*/
/*                         THREADED QUICK SORT                                  */ 
/*============================================================================*/

int QuickSortMT(void *array, size_t arr_size, size_t element_size, 
                                                        compare_t CompareFunc)
{
    void* status = 0;
    sort_var_t handle;
    
    assert(array);
    assert(CompareFunc);

    AssignStruct(&handle, array, 0, arr_size - 1, element_size, 0, CompareFunc);
    
    status = QuickSortRecMT(&handle);

    if(NULL != status)
    {
        return(SUCCESS);
    }
    return (FAIL);
}

static void* QuickSortRecMT(void* param)
{
    sort_var_t *handle = param;
    ssize_t pivot_index = 0;
    ssize_t start_index = 0;
    ssize_t end_index = 0;

    assert(param);

    pivot_index = handle->start;
    start_index = handle->start;
    end_index = handle->end;
    
    if (start_index >= end_index)
    {
        return(param);
    }
    
    if(FAIL == Partition(handle->array, &start_index, &end_index, &pivot_index, 
            handle->CompareFunc, handle->element_size))
    {
        return(NULL);
    }
    
    if(handle->depth < MAX_DEPTH)
    {
        sort_var_t thread_handle[2];
        pthread_t thread_array[2];

        /* assiging the structs */
        AssignStruct(&thread_handle[0], handle->array, handle->start, 
                    start_index - 1, handle->element_size, 
                    handle->depth + 1, 
                    handle->CompareFunc);

        AssignStruct(&thread_handle[1], handle->array, start_index, 
                    handle->end, handle->element_size, 
                    handle->depth + 1, handle->CompareFunc);


        pthread_create(&thread_array[0], NULL, QuickSortRecMT, 
                                                    &thread_handle[0]);
        pthread_create(&thread_array[1], NULL, QuickSortRecMT, 
                                                    &thread_handle[1]);

        pthread_join(thread_array[0], NULL);
        pthread_join(thread_array[1], NULL);
    }
            
    else
    {
        sort_var_t rec_handle;

        AssignStruct(&rec_handle, handle->array, handle->start, 
                    start_index - 1, handle->element_size, MAX_DEPTH,
                    handle->CompareFunc);

        QuickSortRecMT(&rec_handle);

        AssignStruct(&rec_handle, handle->array, start_index, 
                    handle->end, handle->element_size, MAX_DEPTH,
                    handle->CompareFunc);
        
        QuickSortRecMT(&rec_handle);
    }

    return (param);   
}

static void AssignStruct(sort_var_t* thread_handle,  char *array, size_t start, 
        size_t end, size_t element_size, size_t depth, compare_t CompareFunc)
{
    thread_handle->array = array;
    thread_handle->start = start;
    thread_handle->end = end;
    thread_handle->element_size = element_size;
    thread_handle->depth = depth;
    thread_handle->CompareFunc = CompareFunc;
}

/*============================================================================*/
/*                        NO THREAD QUICK SORT                                */ 
/*============================================================================*/

int QuickSort(void *array,
              size_t arr_size,
              size_t element_size,
              compare_t CompareFunc)
{
    int status = 0;
    
    assert(array);
    assert(CompareFunc);
    
    status = QuickSortRec(array, 0, arr_size - 1, element_size, CompareFunc);
    
    return (status);
}

static int QuickSortRec(char *array, size_t start, size_t end, 
                            size_t element_size, compare_t CompareFunc)
{
    ssize_t pivot_index = start;
    ssize_t start_index = start;
    ssize_t end_index = end;
    
    if (start >= end)
    {
        return(SUCCESS);
    }

    if(FAIL == Partition(array, &start_index, &end_index, &pivot_index, CompareFunc, 
                                                    element_size))
    {
        return(FAIL);
    }
    
    QuickSortRec(array, start, start_index - 1, element_size, CompareFunc);
    QuickSortRec(array, start_index, end, element_size, CompareFunc);

    return (SUCCESS);   
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~mutual functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int SwapData(char *array, size_t data_1, size_t data_2, 
                                                        size_t element_size)
{
    void *temp = (void*)malloc(element_size +1);

    if (NULL == temp)
    {
        return (FAIL);
    }
    
    memcpy(temp, array + (data_2 * element_size), element_size);
    memcpy(array + (data_2 * element_size),
           array + (data_1 * element_size), 
           element_size);

    memcpy(array + (data_1 * element_size), temp, element_size);
    
    free(temp);
    
    return (SUCCESS);
}

static int Partition(char *array, ssize_t * start_index, 
            ssize_t * end_index, ssize_t * pivot_index, 
            compare_t CompareFunc, 
            size_t element_size)
{
    while (*start_index <= *end_index)
    {
        while (0 > CompareFunc((array + *start_index * element_size),
                               (array + *pivot_index * element_size)))
        {
            ++(*start_index);
        }
        
        while (0 < CompareFunc((array + *end_index * element_size),
                               (array + *pivot_index * element_size)))
        {
            --(*end_index);
        }
        
        if (*start_index <= *end_index)
        {
            if (FAIL == SwapData(array, *start_index, *end_index, element_size))
            {
                return (FAIL);
            }

            ++(*start_index);
            --(*end_index);
        }
    }
    return (SUCCESS);
}

/*============================================================================*/
/*                                      END                                   */ 
/*============================================================================*/
