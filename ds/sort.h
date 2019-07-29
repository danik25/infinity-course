/*******************************************************************************
*                Data Structures - Sorting  
* file name: sort.h                                             
* Related files: sort.c sort_test.c                             
* #Version: V 1.0                                                  
* writer: Dani Benjamin                                         
* reviewer: Oded Bryt                                          
* last update: 08.05.19                                        
********************************************************************************/

#ifndef _SORT_
#define _SORT_

#include <stddef.h>  /* size_t */

/* Implementation of three basic sorting algorithm:
 * BUBBLE SORT, INSERTION SORT, SELECTION SORT.
 */  


/* The signature of the function provided by the user with the sorting rule.
 * Example for such a function decleration:
 * int IsBefore(const void *first, const void *second);
 */
typedef int (is_before_t)(const void *first, const void *second);



/* BUBBLE SORT
 *
 * Description:
 *      A simple sorting algorithm that repeatedly steps through the list,
 *      compares adjacent pairs using the IsBefore function, 
 *      and swaps them if they are in the wrong order.
 *      The pass through the list is repeated until the list is sorted.                
 *
 * Params: 
 *      array - containes the elements to be bubble-sorted.
 *      len - number of elements in the array.
 *      element_size - element size in bytes.
 *      IsBefore - the comparison function.
 *        
 * Return Value: 
 *      1 - fail
 *      0 - success
 *  
 * Time complexity:
 *      O(n^2)    
 */
int BubbleSort(void *array, size_t len, size_t element_size,
                                                          is_before_t IsBefore);


/* INSERTION SORT
 *
 * Description:
 *      A simple sorting algorithm that builds the final sorted array one item
 *      at a time. The array elements are compared with each other sequentially 
 *      using the IsBefore function, and then arranged simultaneously in some
 *      particular order.        
 *
 * Params: 
 *      array - containes the elements to be insertion-sorted.
 *      len - number of elements in the array.
 *      element_size - element size in bytes.
 *      IsBefore - the comparison function.
 *        
 * Return Value: 
 *      1 - fail
 *      0 - success
 *  
 * Time complexity:
 *      O(n^2)    
 */
int InsertionSort(void *array, size_t len, size_t element_size,
                                                          is_before_t IsBefore);


/* SELECTION SORT
 *
 * Description:
 *      A simple sorting algorithm that sorts an array by repeatedly finding the
 *      minimum element (considering the IsBefore function) from unsorted part
 *      and putting it at the beginning. This algorithm maintains two subarrays
 *      in a given array.        
 *
 * Params: 
 *      array - containes the elements to be insertion-sorted.
 *      len - number of elements in the array.
 *      element_size - element size in bytes.
 *      IsBefore - the comparison function.
 *        
 * Return Value: 
 *      1 - fail
 *      0 - success
 *  
 * Time complexity:
 *      O(n^2)    
 */
int SelectionSort(void *array, size_t len, size_t element_size, 
                                                          is_before_t IsBefore);



#endif /* _SORT_ */

