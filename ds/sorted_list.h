/****************************************************************
*                Data Structures - Sorted List                  *
* Related files:    sorted_list.c    dl_list.h                  *
*	            sorted_list.h    sorted_list_test.c	            *
* #Version: V 1.4                                               *
* Writer: Dani Benjamin                                	        *
* Reviewer: Tom Valershtein                                    	*
* Last update: 16.4.19                                          *
****************************************************************/ 
/*
 * Sorted list is a list that its elements are ordered 
 * by a function provided by user. 
 * The list can be traversed in both forward and backward direction.
*/  

/* API Design:
 *	
 *      This API is desgined to store elements in a sorted way, in a list.
 *		This design supports adding and removing elements. 
 *		Note that the sorting is done by the user provided compare function. 
 *		This design supports any data type. 
*/


#ifndef _SORTED_LIST_
#define _SORTED_LIST_

#include <stddef.h> /* size_t */


typedef int (sort_action_function_t)(void *data, void *param);
typedef int (sort_is_match_function_t)(void *data, void *param);

/* Compare between two data.
 *
 * Params:
 *		data1 - data from new element.
 *		data2 - data from list's elements.
 *      param - additional parameter provided by user.
 *
 * Return Value: 
 *      boolean (TRUE(1) / FALSE(0)).
*/
typedef int (sort_compare_function_t)(void *data1, void *data2, void *param);

typedef struct sorted_list sorted_list_t;
typedef void * sorted_iter_t;


/* Create an empty sorted list, 
 * actually containing two dummy nodes.
 *	
 * Param:
 *		func - compare function.
 *      param - additional parameter provided by user.
 *	  
 * Return Value: 
 *		  pointer to the newly created list. 
*/
sorted_list_t *SortCreate(sort_compare_function_t is_before, void *param);


/* Destroy the sorted list - 
 * free all allocated memory from a given position.
 *
 * Param: 
 *      sorted_list - the sorted list to work on.
 *
 * Time complexity: O(n).
*/
void SortDestroy(sorted_list_t *sorted_list);	  


/* Checks whether or not the sorted list is empty.
 * 
 * Param: 
 *      sorted_list - the sorted list to work on.
 *
 * Return Value: 
 *      boolean (TRUE(1) / FALSE(0)).
*/
int SortIsEmpty(const sorted_list_t *sorted_list);


/* Counts elements in a given sorted list.
 *  
 * Param: 
 *      sorted_list - the sorted list to work on.
 *
 * Return value: 
 *      number of elements in the sorted list.
*/
size_t SortSize(const sorted_list_t *sorted_list);


/* Finds the last element of a given sorted list. 
 * 
 * Param: 
 *      sorted_list - the sorted list to work on.	
 *	  
 * Return value: 
 *      a pointer to the end of the sorted list (tail dummy).
*/
sorted_iter_t SortEnd(const sorted_list_t *sorted_list);


/* Finds the first element of a given sorted list. 
 *	 
 * Param: 
 *      sorted_list - the sorted list to work on.
 *	  
 * Return value: 
 *      a pointer to the beginning of the sorted list.
 *      in case of empty list return dummy tail.
*/
sorted_iter_t SortBegin(const sorted_list_t *sorted_list);


/* Gives the next element from a given location. 
 *
 * Param: 
 *      location - specific node to check.
 *		  
 * Return value: 
 *      a pointer to the next element of a given location.
 *      In case location points to tail dummy, 
 *      it is undefined behavier- return NULL. 
*/
sorted_iter_t SortNext(const sorted_iter_t location);


/* Gives the previous element from a given location. 
 *	
 * Param:  
 *      location - specific node to check.
 *                 
 * Return value: 
 *      a pointer to the prev element of a given location.
 *      in case location points to first element or in case of empty list, 
 *      it is undefined behavier- return NULL. 
*/
sorted_iter_t SortPrev(const sorted_iter_t location);


/* Extracts data from a given element.
 *
 * param: 
 *      location - specific node to check.
 *
 * Return value: 
 *      the data from the given location. 
*/
void *SortGetData(const sorted_iter_t location);


/* Compares addresses of two given iterators.
 *
 * Params: 
 *      first_iter - first pointer to a node. 
 *      second_iter - second pointer to a node.
 *
 * Return Value: 
 *      boolean (TRUE(1) / FALSE(0)).
*/
int SortIsSameIter(const sorted_iter_t first_iter, 
                                               const sorted_iter_t second_iter);


/* Erase an element in a specific location.
 *
 * Params:
 *      location - pointer to the node to be erased.
 *	
 * Return value : 
 *      pointer to next node after the erased node.
 *      in case location points to end, 
 *      it is undefined behavier- return NULL. 
*/
sorted_iter_t SortErase(sorted_iter_t location);


/* Creates and inserts an element to the given sorted list,
 * so the list will stay sorted (insertion location determined by 
 * the compare function).
 *
 * Params:
 *      sorted_list - a sorted list to insert an element to.	 
 *      data_to_insert - the data to insert.
 *	
 * Return value : 
 *      pointer to inserted node if succeded. 
 *      NULL if failed.  
 *
 * Time complexity: O(n).
*/
sorted_iter_t SortInsert(sorted_list_t *sorted_list, void *data_to_insert);


/* Remove a node from the beginning of a sorted list.
 *
 * Param: 
 *      sorted_list - a sorted list to remove an element from.
 *
 * Return value : 
 *      pointer to the data of the removed node, if succeded.
 *      NULL if failed. 
*/
void *SortPopFront(sorted_list_t *sorted_list);


/* Remove a node from the end of a sorted list.
 *
 * Param: 
 *      sorted_list - a sorted list to remove an element from.
 *
 * Return value : 
 *      pointer to the data of the removed node, if succeded.
 *      NULL if failed.  
*/
void *SortPopBack(sorted_list_t *sorted_list);


/* Apply a provided function on a given sequence of elements. 
 *
 * NOTE: IF DATA IS ALTERED WITH <action function>, SORTING IS NOT GUARENTEED.
 *
 * Params: 
 *      from - start position.
 *      to - end position (up to and not including).
 *      func - user provided function.
 *      param - additional parameter provided by user.
 *
 * Return value : 
 *      status - success(0) or failure(1). 
*/
int SortForEach(sorted_iter_t from, sorted_iter_t to,
						 	          sort_action_function_t func, void *param);


/* Search if a given data exists on a provided sorted list. 
 *
 * Params: 
 *      sorted_list - a sorted list from which the sequence is given.
 *      from - start position.
 *      to - end position (up to and not including).
 *      param - data to find.
 *
 * Return value : 
 *      pointer to the match node,
 *      or tail dummy if no match.
*/
sorted_iter_t SortFind(sorted_list_t *sorted_list, sorted_iter_t from, 
                  sorted_iter_t to, sort_is_match_function_t func, void *param);


/* Merge two sorted lists into one sorted list <to>. 
 * <from> will be destroyed.
 *
 * Params: 
 *      to - sorted list to merge <second_list> into
 *      from - sorted list to merge.
 *
 * Time Complexity: O(n).
*/
void SortMerge(sorted_list_t *to, sorted_list_t *from);

#endif /* _SORTED_LIST_ */
