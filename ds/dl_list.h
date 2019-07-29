/****************************************************************
*                Data Structures - Double Linked List           *
* Related files: dl_list.c 	dl_list.h	dl_list_test.c	        *
* #Version: V 1.7                                               *
* writer: Dani Benjamin                                 		*
* reviewer: Amir Tzin                               			*
* last update: 14.4.19                                          *
****************************************************************/
/*
* A Double Linked List contains an extra pointer, typically called prev 
* pointer, together with next pointer and data which are there in singly linked 
* list. The main advantage of double linked lists over single linked list 
* is A dl_list can be traversed in both forward and backward direction.
* We can quickly insert a new node before a given node. As a convention, the 
* first element we referd to is the one next to the head dummy, and the last
* element is the one previous to tail dummy.
*/  

/* API Design:
 *	
 *		This API design is an infrastructure module, allowing the user
 *		to access the structure.
 *		With the ability to access the structure, the user can add nodes,
 *		delete nodes, modify the structure itself as well as the data in
 *		any of it's fields.
 *
 *		This design supports any data type. 
 * 	                

	  		 	****************** <-- *****************<-- *****************    
NULL<--DUMMY <--* DATA  *   next * --> *  DATA  * next * -->*  DATA  * next *---> DUMMY-->NULL 
	   			******************     *****************    *****************
	   		  	    1st node 		    2nd node  ....n'th node...    Last node	
*/
#ifndef _DL_LIST_
#define _DL_LIST_

#include <stddef.h> /* size_t */

/* typedef on function pointer for readability - both functions are given */
/* as arguments to DLLForEach and DLLFind respectively. 
success(0) or failure(1).*/

typedef int (action_function_t)(void *data, void* param);
typedef int (compare_function_t)(void *data, void* param);

typedef struct dl_node* dl_iter_t;
typedef struct dl_list dll_t;


/* Create an empty doubly linked list, actually containing two dummy nodes.
 * Params: void.
 *		  
 * Return Value: 
 *		  pointer to the newly created list. 
*/
dll_t *DLCreate();


/* Destroy the doubly linked list - free all allocated memory from a given position.
 *
 * param: dl_list - the list to work on.
 * Time complexity: O(n).
*/
void DLDestroy(dll_t *dl_list);	  


/* Checks whether or not the list is empty.
 * 
 * param: dl_list - the list to work on.
 *
 * Return Value: boolean (TRUE(1) / FALSE(0)).
 *
*/
int DLIsEmpty(const dll_t *dl_list);


/* Counts elements in a given list.
 *  
 * param: dl_list - the list to work on.
 *
 * Return value: number of elements in the list.
*/
size_t DLCount(const dll_t *dl_list);


/* Finds the last element of a given list. 
 * 
 * param: dl_list - the list to work on.	
 *	  
 * Return value: a pointer to the end of the list.
*/
dl_iter_t DLEnd(const dll_t *dl_list);


/* Finds the first element of a given list. 
 *	 
 * param: dl_list - the list to work on.
 *	  
 * Return value: a pointer to the beginning of the list.
 * in case of empty list return dummy tail.
*/
dl_iter_t DLBegin(const dll_t *dl_list);


/* Gives the next element from a given location. 
 *
 * param: location - specific node to check.
 *		  
 * Return value: a pointer to the next element of a given location. 
 * If location is DLEnd()- undefined behavior. 
*/
dl_iter_t DLNext(const dl_iter_t location);


/* Gives the previous element from a given location. 
 *	
 * param: 
 *           location -   specific node to check.
 *                 
 * Return value: a pointer to the prev element of a given location.
 *  If location is DLBegin()- undefined behavior. 
*/
dl_iter_t DLPrev (const dl_iter_t location);


/* Extracts data from a given element.
 *
 * param: location - specific node to check.
 *
 * Return value: the data from the given location. 
*/
void *DLGetData(const dl_iter_t location);


/* Compares addresses of two given iterators.
 * position.
 *
 * Params: first_iter - first pointer to a node. 
 *		   second_iter - second pointer to a node.
 *
 * Return Value: boolean (TRUE(1) / FALSE(0)).
*/
int DLSameIter(const dl_iter_t first_iter, const dl_iter_t second_iter);


/* Creates and inserts an element before a given location.
 * Params:
 *		  dl_list - A list to insert an element to.
 *		  location - a reference location.		 
 *		  data_to_insert - the data to insert.	
 * Return value : 
 *        pointer to inserted node if succeded. tail dummy if failed.  
*/
dl_iter_t DLInsert(dll_t *dl_list, dl_iter_t location, void *data_to_insert);


/* Removes an element from a list and erases it's content.
 * Params: 
 *		  location - the element to be removed.
 *		  
 * Return value : 
 *        pointer to the element after the removed one if succeded.
 *		  If location is DLBegin()- undefined behavior. 
*/
dl_iter_t DLErase(dl_iter_t location);


/* Create and insert an element to the beginning of the list.
 * Params: 
 *		  dl_list - A list to insert an element to.
 *		  data - data of the inserted element.
 * Return value : 
 *        pointer to inserted element or end dummy if fails. 
*/
dl_iter_t DLPushFront(dll_t *dl_list, void *data);


/* Create and insert an element to the end of the list.
 * Params: 
 *		  dl_list - a list to insert an element to.
 *		  data - data of the inserted element.
 * Return value : 
 *        pointer to inserted element or end dummy if fails. 
*/
dl_iter_t DLPushBack(dll_t *dl_list, void *data);


/* Remove a node from the beginning of the list.
 * Params: 
 *		  dl_list - a list to remove an element from.
*/
void DLPopFront(dll_t *dl_list);


/* Remove a node from the end of the list.
 * Params: 
 *		  dl_list - a list to remove an element from.
*/
void DLPopBack(dll_t *dl_list);


/* Apply a provided function on a given sequence of elements. 
 * Params: 
 *		  from - start position.
 * 		  to - end position (up to and not including).
 *		  func - user provided function.
 * 		  param - additional parameter provided by user.
 * Return value : 
 *        status - success(0) or failure(1). 
*/
int DLForEach(dl_iter_t from, dl_iter_t to,
						 	action_function_t func , void *param);


/* Search if a given data exists on a provided list. 
 * Params: 
 *		  dl_list - a list from which the sequence is given.
 *		  from - start position.
 * 		  to - end position (up to and not including).
 *        param - data to find.
 * Return value : 
 *        pointer to the match or end dummy if no match.
*/
dl_iter_t DLFind(dll_t *dl_list, dl_iter_t from, dl_iter_t to,
 		compare_function_t func, void *param);


/* Insert a sequence of elements before a given location.
 * Params: 
 *		  src_list - the list to transfer the sequence from. 
 *		  from - start position.
 * 		  to - end position (up to and not including).
 *		  location - node to insert the sequence before.
 *        in case src_list is the same list as location list the behaiver is 
 *        undefined.
*/
void DLSplice(dll_t *src_list, dl_iter_t from, dl_iter_t to, dl_iter_t location);

#endif /* _DL_LIST_ */

