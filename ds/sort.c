/*******************************************************************************
*                Data Structures - Sorting  
* file name: sort.h                                             
* Related files: sort.c sort_test.c                             
* #Version: V 1.0                                                  
* writer: Dani Benjamin                                         
* reviewer: Oded Bryt                                          
* last update: 08.05.19                                        
********************************************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */
#include <string.h> /* memcpy */

#include "quick_sort.h"

enum stop {GO, STOP};
enum boolean {FALSE, TRUE};
enum status {SUCCESS, FAIL};

static enum status Swap(void *ptr1, void* ptr2, size_t element_size);

int BubbleSort(void *array, size_t len, size_t element_size, 
                                                    is_before_t IsBefore)
{
    char * first = NULL;
    char * second = NULL;
    size_t len_runner = len;
    int stop_flag = GO;

    assert (array);
    assert (IsBefore);

    /* run until the end, as long that swaps are made */
    while (len > 1 && stop_flag == GO)
    {
        len_runner = len;
        first = array;
        second = first + element_size;
        stop_flag = STOP;

        while (len_runner > 1)
        {
            if (FALSE == IsBefore(first, second))
            {
                if (FAIL == Swap(first, second, element_size))
                {
                    return (1);
                }
                stop_flag = GO;
            }
            
            first += element_size;
            second += element_size;
            --len_runner;
        }

        --len;
    }

    return(0);
}

int InsertionSort(void *array, size_t len, size_t element_size, 
                                                        is_before_t IsBefore)
{
    char * runner = NULL;
    char * fixer = NULL;

    assert (array);
    assert (IsBefore);

    runner = array;

    while (len > 1)
    {
        fixer = runner + element_size;
        while (FALSE == IsBefore(fixer - element_size, fixer) && fixer != array)
        {
            /* reverse bubble */
            if (FAIL == Swap(fixer, fixer - element_size, element_size))
            {
                return (1);
            }

            fixer -= element_size;
        }

        runner += element_size;
        --len;
    }
    
    return (0);
}
  
int SelectionSort(void *array, size_t len, size_t element_size, 
                                                          is_before_t IsBefore)
{
    void * first = NULL;
    char * runner = NULL;
    size_t len_copy = len;

    assert (array);
    assert (IsBefore);

    first = array;
    runner = array;

    while (len > 1)
    {
        while (len_copy > 1)
        {
            runner += element_size;
            if(FALSE == IsBefore(first, runner))
            {
                first = runner;
            }
            --len_copy;
        }

        if (FAIL == Swap(array, first, element_size))
        {
            return (1);
        }

        array = (char*)array + element_size;
        first = runner = array;
        --len;
        len_copy = len;
    }

    return (0);
}

/*============================================================================*/

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