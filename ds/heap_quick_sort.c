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

static int Swap(void *ptr1, void* ptr2, size_t element_size);


int QuickSort(void *array, size_t arr_size, size_t element_size,
                                                         compare_t CompareFunc)
{
    void *first = array;
    void* last = (char*)array + (arr_size - 1)*element_size;
    void* pivot = last;
    size_t index = 0;

    while(first <= last)
    {
        /* the right element is in place, but the left isn't */
        if(CompareFunc(pivot, first) > 0 && CompareFunc(last, pivot) <= 0)
        {
            first = (char*)first + element_size;
            ++index;
        }
        /* the left element is in place, but the right isn't */
        else if(CompareFunc(pivot, first) < 0 && CompareFunc(last, pivot) > 0)
        {
            last = (char*)last - element_size;
        }
        
        else
        {
            /* both of the element aren't in place */
            if(CompareFunc(pivot, first) < 0 && CompareFunc(last, pivot) <= 0)
            {
                if(FAIL == Swap(first, last, element_size))
                {
                    return (FAIL);
                }
            }

            first = (char*)first + element_size;
            last = (char*)last - element_size;
            ++index;
        }   
    }

    if(index < arr_size)
    {
        QuickSort(array, index, element_size, CompareFunc);
        QuickSort((char*)first, arr_size - index, element_size, CompareFunc);
    }
    
    return (SUCCESS);
}


/*=========================================================================*/

static int Swap(void *ptr1, void* ptr2, size_t element_size)
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
