/*******************************************************************************
*                Data Structures - quick sort   
* file name: quick_sort.c                                             
* Related files: quick_sort.h quick_sort_test.c                               
* #Version:                                                  
* writer: Dani Benjamin                                                         
* reviewer: Michal Adler                                                
* last update: 10.6.2019                                               
*******************************************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "heap_quick_sort.h"

enum status {SUCCESS, FAIL};

static enum status Swap(void *ptr1, void* ptr2, size_t element_size);


int QuickSort(void *array, size_t arr_size, size_t element_size,
                                                         compare_t CompareFunc)
{
    void *first = array;
    void* last = (char*)array + (arr_size - 1) * element_size;
    void* pivot = last;
    size_t index = 0;

    if(first >= last)
    {
        return(SUCCESS);
    }

    while(first < last)
    {
        /* as long as the first element is smaller than the pivot */
        while(CompareFunc(first, pivot) < 0)
        {
            first = (char*)first + element_size;
            ++index;
        }
        /* as long as the last element is bigger than the pivot */
        while(CompareFunc(last, pivot) > 0)
        {
            last = (char*)last - element_size;
        }
        
        if(first < last)
        {
            if(FAIL == Swap(first, last, element_size))
            {
                return (FAIL);
            }
            first = (char*)first + element_size;
            last = (char*)last - element_size;
            ++index;
        }   
    }
    
    QuickSort(array, index, element_size, CompareFunc);
    QuickSort((char*)first, arr_size - index, element_size, CompareFunc);
    
    
    return (SUCCESS);
}


/*=========================================================================*/

static enum status Swap(void *ptr1, void* ptr2, size_t element_size)
{
    void *tmp = (void*)malloc(element_size);

    assert (ptr1);
    assert (ptr2);

    if (NULL == tmp)
    {
        return (FAIL);
    }

    memcpy(tmp, ptr1, element_size);
    memcpy(ptr1, ptr2, element_size);
    memcpy(ptr2, tmp, element_size);

    free (tmp);
    return (SUCCESS);
}
