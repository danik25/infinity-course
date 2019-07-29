#ifndef  _HEAP_QUICK_SORT_H_
#define  _HEAP_QUICK_SORT_H_

#include <stddef.h> /* size_t */

/****************************************************************
*                      Heap + Quick Sort
*           =====================
* File Name: heap_quick_sort.h
* Related files: heap_quick_sort.c, heap_quick_sort_test.c
* #Version: V 1.0
* Writer:  
* Reviewer:
* Last update:
****************************************************************/

 
typedef int (*compare_t)(const void *data1, const void *data2);



/*  Description   : sorts a received array based on Heap Sort algorithm.
 *
 *  Input         : arr          - array to be sorted by the function
 *                  arr_size     - size of array
 *                  element_size - size in bytes of each element in array
 *                  func         - function by which the array will be sorted
 *
 *  Return Values : 0 - Successfully sorted
 *                 -1 - Failed sorting
 *
 *  Complexity    : Time  - O(n*log(n))
 *                  Place - O(n)
 *
 *  Stability     : stable
 */
int HeapSort(void *array, size_t arr_size, size_t element_size,
                                                         compare_t CompareFunc);

/*  Description   : sorts a received array based on Quick Sort algorithm.
 *
 *  Input         : arr          - array to be sorted by the function
 *                  arr_size     - size of array
 *                  element_size - size in bytes of each element in array
 *                  func         - function by which the array will be sorted
 *
 *  Return Values : 0 - Successfully sorted
 *                 -1 - Failed sorting
 *
 *  Complexity    : Time  - O(n*log(n))
 *                  Place - O(n)
 *
 *  Stability     : stable
 */
int QuickSort(void *array, size_t arr_size, size_t element_size,
                                                         compare_t CompareFunc);

int QuickSortMT(void *array,
              size_t arr_size,
              size_t element_size,
              compare_t CompareFunc);
                                                          
#endif /* _HEAP_QUICK_SORT_H_  */
