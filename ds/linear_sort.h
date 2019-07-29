/*******************************************************************************
*                Data Structures - Linear Sorting   
* file name: linear_sort.h                                              
* Related files: linear_sort.c linear_sort_test.c                               
* #Version: V 2.1                                                  
* writer: Dani Benjamin                                                         
* reviewer: Lev Shubert                                                 
* last update: 14.5.2019                                               
*******************************************************************************/ 

#ifndef _LINEAR_SORT_H_
#define _LINEAR_SORT_H_

#include <stddef.h>  /* size_t */

/* Implementation of two linear non-comparison sorting algorithms:
 * COUNTING SORT and RADIX SORT.
 */  


/* The signature of the function provided by the user with the sorting rule.
 * the function get key and convert it to number.
 */
typedef size_t (*key_to_num_t)(const void *key, const void *arg);



/* COUNTING SORT
 *
 * Description:
 *      An algorithm for sorting a collection of objects 
 *      according to keys that are non-negativ integers.
 *      It operates by counting the number of objects 
 *      that have each distinct key value, 
 *      and using arithmetic on those counts to determine 
 *      the positions of each key value in the result sequence.  
 *      
 *      This implementation preserves stability.            
 *
 * Params: 
 *      arr - containes the elements to be sorted.
 *      len - number of elements in the array.
 *      element_size - element size in bytes.
 *      KeyToNum - from-key-to-number conversion function.
 *      arg - argument for KeyToNum function.
 *      range - range of values in the array.
 *        
 * Return Value: 
 *      1 - fail
 *      0 - success
 *  
 * Time complexity:
 *      O(n + k)      
 */
int CountingSort(void *arr, size_t len, size_t element_size,
                 key_to_num_t KeyToNum, const void *arg, size_t range);

/*
 * RADIX SORT
 *
 * Description:
 *      a non-comparative integer sorting algorithm 
 *      that sorts data with integer keys by grouping keys 
 *      by the individual digits which share the same 
 *      significant position and value.            
 *
 * Params: 
 *      arr - containes the elements to be sorted.
 *      len - number of elements in the array.
 *      element_size - element size in bytes.
 *      KeyToNum - from-key-to-number conversion function.
 *      arg - argument for KeyToNum function.
 *      max_digits_num - maximum digits of element in the array.
 *        
 * Return Value: 
 *      1 - fail
 *      0 - success
 *  
 * Time complexity:
 *      O(n + k)      
 */
int RadixSort(void *arr, size_t len, size_t element_size,
                 key_to_num_t KeyToNum, const void *arg, size_t max_digits_num);


#endif /* _LINEAR_SORT_H_ */