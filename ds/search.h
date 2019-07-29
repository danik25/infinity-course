#ifndef  _SEARCH_H_
#define  _SEARCH_H_

#include <stddef.h> /* size_t */

/****************************************************************
*                      Search
* 					=====================
* File Name: search.h
* Related files: search.c, search_test.c
* #Version: V 1.0
* Writer: Dani Benjamin 
* Reviewer: Tom Valershtein
* Last update: 11.06.19
****************************************************************/


typedef int (*compare_t)(const void *data1, const void *data2);

/*	Description: 	Binary search function.
 *	Input: 			sorted array to search, size of the array, array element
 *					size, compare function, data to search.
 *	Return Values:	Pointer to found element - on success,
 *				    NULL                     - otherwise.
 *  Complexity:     O(log(n)).
 *  Auxiliary Space:O(1).
 */
void *BinarySearchIter(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data);

/*	Description: 	Recursive binary search function.
 *	Input: 			sorted array to search, size of the array, array element
 *					size, compare function, data to search.
 *	Return Values:	Pointer to found element - on success,
 *				    NULL                     - otherwise.
 *  Complexity:     O(log(n)).
*  Auxiliary Space:O(1).
 */         
void *BinarySearchRec(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data);

/*	Description: 	Jump searching algorithm function.
 *	Input: 			sorted array to search, size of the array, array element
 *					size, compare function, data to search.
 *	Return Values:	Pointer to found element - on success,
 *				    NULL                     - otherwise.
 *  Complexity:     O(√n).
 *  Auxiliary Space:O(1).
 */         
void *JumpSearch(const void *array, size_t arr_size, size_t element_size,
                                       compare_t CompareFunc, const void *data);
#endif /* _SEARCH_H_  */
