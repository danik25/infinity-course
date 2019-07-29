/****************************************************************
*                Data Structures - Singly Linked List           *
* Related files:                                                *
* #Version: V 1                                                 *
* writer: Dani Benjamin                                         *
* reviewer: Oded Bryt                                           *
* last update: 10.4.19                                          *
****************************************************************/

#ifndef _SL_LIST_
#define _SL_LIST_
#include <stddef.h> /* size_t */
 
/*
 * A singly linked list is a data structure consisting of a group of nodes,
 * linked together. Each node consists of data elements and a link
 * to the next node. The main advantage of linked lists over simple arrays 
 * is that the nodes can be inserted anywhere in the list without reallocating
 * the entire array because the nodes in a linked list do not need to be stored
 * contiguously in memory. However, nodes in the list cannot be accessed by 
 * index but must be accessed by traversing the list.
*/  

/* API Design:
	
		This API design is an infrastructure module, allowing the user
		to access the structure.
		With the ability to access the structure, the user can add nodes,
		delete nodes, modify the structure itself as well as the data in
		any of it's fields.

		This design supports any data type. 
	

	******************     *****************    *****************    
  	* DATA  *   next * --> *  DATA  * next * -> *  DATA  * next *---> NULL 
	******************     *****************    *****************
	   	  1st node 		    2nd node  ....n'th node...    Last node	
*/


/* typedef on function pointer for readability - both functions are given */
/* as arguments to SLLForEach and SLLFind respectively. */
typedef int (action_function_t)(void *data, void* param);
typedef int (is_match_function_t)(void *data, void* param);

 
typedef struct sl_node {
		    	  	
		void * data;
		struct sl_node *next; 

} sl_node_t;



/* Create a node, can connect the new node to other existing nodes.

 * Params:
		  next - pointer to the node that will be pointed by the created node.
				 (NULL if node does not point to any other node).
		  data - pointer to the data that will be inserted to the node.
 
 * Return Value: pointer to the created node. 
*/

sl_node_t *SLLCreate(void *data, sl_node_t *next);



/* Destroy the linked list - free all allocated memory from a given position.

 * Params: 
		  node - reference node.

 * Time complexity: O(n).
*/
void SLLDestroy(sl_node_t *node);	  



/* Insert a node before a given location.

 * Params: 
		  node_to_insert - desired node to be inserted. 
		  node_location  - node that will be pointed to by the inserted node.
		  

 * Return value : pointer to inserted node
*/

sl_node_t *SLLInsert(sl_node_t *node_to_insert, sl_node_t *node_location);



/* Insert a node after a given location.

 * Params: 
		  node_location  - the node that will point to the inserted node.
		  node_to_insert - the node to be inserted.

 * Return value : pointer to inserted node. 
*/

sl_node_t *SLLInsertAfter(sl_node_t *node_to_insert, sl_node_t *node_location);



/* Remove a node from a given location.Cannot remove the last node from a list.

 * Params: 
		  node_to_remove - the node that will be removed from list.

 * Return value : a pointer to the removed node.
*/
sl_node_t *SLLRemove(sl_node_t *node_to_remove);


/* Remove a node from the list after a given location.

 * Params: 
		  location  - the node that points to the node to be removed.

 * Return value : a pointer to the removed node. 
*/
sl_node_t *SLLRemoveAfter(sl_node_t *location);


/* Apply <action_func> on all nodes starting from <node>.

 * Params: 
		  node - reference node.

 * Return value : success / type of failure.
*/
int SLLForEach(sl_node_t *node, action_function_t func, void *param);



/* Find if a certain data matches data on the list.

 * Params: 
		  node - reference node.
		  data - the data to be found.	

 * Return value : pointer to node that holds relevant data.
*/
sl_node_t *SLLFind(sl_node_t *node, is_match_function_t func, void *param);


/* Count the number of nodes on the list, from a reference node.

 * Params: 
		  node - reference node.

 * Return value : number of nodes on the list.
*/
size_t SLLCount(const sl_node_t *node);



/* Reverse the direction of the singly linked list.

 * Params: 
		  node - reference node.

 * Return value : a pointer to the new first node of the list.
*/
sl_node_t *SLLFlip(sl_node_t *node);


/* Find intersections - a shared node between two lists.

 * Params: 
		  node_1 - reference node of first list.
  		  node_2 - reference node of second list.

 * Time complexity: O(n).

 * Return value : a pointer to the shared node.
*/
sl_node_t *SLLFindIntersection(const sl_node_t *node_1, 
       						   const sl_node_t *node_2);



/* Finds if a loop exists within the list.

 * Params: 
		  node  - reference node.
	
 * Return value : 1 if loop found, 0 if not.
*/
int SLLHasLoop(sl_node_t *node);


#endif /* _SL_LIST_ */
