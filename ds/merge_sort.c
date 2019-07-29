/****************************************************************

*                      Merge Sort

*                       =====================

* File Name: merge_sort.h

* Related files: merge_sort.c   merge_sort_test.c

* #Version: V 1.1

* Writer: Dani Benjamin      

* Reviewer: Tom Valershtein     

* Last update: 04.06.2019

****************************************************************/

#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "merge_sort.h"

static void RecMergeSort(void *arr, void* tmp_res, size_t start, size_t end,
                                is_before_t IsBefore, size_t element_size);
static void Merge(void *arr, void *res, size_t start, size_t mid, size_t end, 
                                is_before_t IsBefore, size_t element_size);

#define START_OF_ARRAY 0

int MergeSort(void *array, size_t arr_size, 
                    size_t element_size, is_before_t IsBefore)
{
    void* handle = (void*)malloc(element_size*arr_size);

    assert(array);
    assert(IsBefore);

    if(NULL == handle)
    {
        return (MEM_ALLOC_FAIL);
    }
    RecMergeSort(array, handle, START_OF_ARRAY, arr_size - 1, IsBefore, element_size);
   
    free(handle);

    return(SUCCESS);
}

static void RecMergeSort(void *arr, void* tmp_res, size_t start, size_t end,
                                is_before_t IsBefore, size_t element_size)
{
    size_t mid = 0;

    assert(arr);
    assert(tmp_res);
    assert(IsBefore);

    if(start >= end)
    {
        return ;
    }
    
    mid = (start + end) / 2;
    RecMergeSort(arr, tmp_res, start, mid, IsBefore, element_size);
    RecMergeSort(arr, tmp_res, mid + 1, end, IsBefore, element_size);
    Merge(arr, tmp_res, start, mid, end, IsBefore, element_size);
       
}

static void Merge(void *arr, void *res, size_t start, size_t mid, size_t end, 
                                is_before_t IsBefore, size_t element_size)
{
    size_t left = start;
    size_t right = mid + 1;
    char res_index = start;
    char *arr_copy = NULL;
    char *res_copy = NULL;

    assert(arr);
    assert(res);
    assert(IsBefore);

    arr_copy = (char*)arr;
    res_copy = (char*)res;

    while(left <= mid && right <= end)
    {
        if(IsBefore((arr_copy + right * element_size), 
                        (arr_copy + left * element_size)))
        {
            memcpy(res_copy + res_index * element_size, 
                        arr_copy + right * element_size, element_size);
            ++right;
        }

        else
        {
            memcpy(res_copy + res_index * element_size, 
                        arr_copy + left * element_size, element_size);
            ++left;
        }
        ++res_index;
    }

    
    memcpy(res_copy + res_index * element_size, 
            arr_copy + right * element_size, (end - right + 1) * element_size);
   
    memcpy(res_copy + res_index * element_size, 
            arr_copy + left * element_size, (mid - left + 1) * element_size); 

    memcpy((char*)arr + start * element_size, 
            (char*)res_copy + start * element_size, (end - start + 1) * element_size);  
}