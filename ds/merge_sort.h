/****************************************************************

*                      Merge Sort

* 						=====================

* File Name: merge_sort.h

* Related files: merge_sort.c   merge_sort_test.c

* #Version: V 1.1

* Writer: Dani Benjamin      

* Reviewer: Tom Valershtein     

* Last update: 04.06.2019

****************************************************************/

#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include <stddef.h>

enum STATUS {SUCCESS, MEM_ALLOC_FAIL};


typedef int (*is_before_t)(const void *data1, const void *data2);


int MergeSort(void *array,
    		  size_t arr_size,
              size_t element_size,
              is_before_t IsBefore);

#endif