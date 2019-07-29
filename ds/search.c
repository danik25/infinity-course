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
#include <assert.h> /* assert */
#include <math.h> /* sqrt */

#include "search.h"

void *BinarySearchIter(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data)
{
    int left = 0;
    int right = arr_size - 1;
    int mid = 0;
    int diff = 0;

    assert(array);
    assert(CompareFunc);

    while(left <= right)
    {
        mid = left + (right - left) / 2;
        diff = CompareFunc(data, ((char*)array + mid * element_size));
        if(0 == diff)
        {
            return((char*)array + mid * element_size);
        }
        else if(diff > 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return (NULL);
}

void *BinarySearchRec(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data)
{
    size_t left = 0;
    size_t right = arr_size - 1;
    size_t mid = 0;
    int diff = 0;

    assert(array);
    assert(CompareFunc);

    mid = left + (right - left) / 2;
    diff = CompareFunc(data, ((char*)array + mid * element_size));

    if(0 == diff)
    {
        return((char*)array + mid * element_size);
    }

    if(arr_size == 1)
    {
        return (NULL);
    }
    else if(diff > 0)
    {
        left = mid + 1;
        return(BinarySearchRec((char*)array + (mid + 1) * element_size, 
                            right - left + 1, element_size, CompareFunc, data));
    }
  
    right = mid - 1;
    return(BinarySearchRec(array, right + 1, element_size, CompareFunc, data));
}

void *JumpSearch(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data)
{
    size_t start = 0;
    size_t jumper = 1;
    size_t end = jumper;
    int jump_size = sqrt(arr_size);
    int diff = -1;

    assert(array);
    assert(CompareFunc);

    if(jumper <= arr_size)
    {
        diff = CompareFunc(data, ((char*)array + jumper * element_size));
    }
    
    /* while we haven't reached the end, and the entered data os still larger */
    while(jumper < arr_size && diff > 0)
    {
        start = end;
        jumper += jump_size;

`       /* in cade the index passed the size of the array */
        end = (jumper >= arr_size) ? arr_size -1 : jumper;
        diff = CompareFunc(data, ((char*)array + end * element_size));  
    }

    if(0 == diff)
    {
        return((char*)array + end * element_size);
    }
    /* binary search in the left array */
    return(BinarySearchRec((char*)array + start * element_size, 
            end - start, element_size, CompareFunc, data));
}