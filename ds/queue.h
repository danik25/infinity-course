/****************************************************************
*                Data Structures - Queue                        *
* Related files: queue.c, queue_test.c                          *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Lev Shubert                                         *
* Last update: 10/04/19                                         *
****************************************************************/  

#ifndef _QUEUE_ /* INCLUDE_GUARD */
#define _QUEUE_
#include <stddef.h> /* size_t */

/*
 * Queue is an abstract data type or a linear data structure, just like stack
 * data structure, in which the first element is inserted from one end called  
 * the REAR(also called tail), and the removal of existing element takes place 
 * from the other end called as FRONT(also called head).This makes queue as  
 * FIFO(First in First Out) data structure, which means that element inserted  
 * first will be removed first.The difference between stacks and queues is in 
 * removing.In a stack we remove the item the most recently added; in a queue, 
 * difference between stacks and queues is in removing. In a stack we remove 
 * we remove the the item the most recently added; in a queue, we remove the  
 * item the least recently added. 
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
 */

typedef struct Queue queue_t;

/* 
 * Create a queue.
 * Return Value:  
 * if secceded -pointer to the created queue.
 * if failed - NULL. 
 */
queue_t *QCreate(void);

/* Destroy the queue- free all allocated memory.*/
void QDestroy(queue_t *queue);	  


/* 
 * Insert a member to the end of the queue.
 *  
 * Params: 
 *		  queue - the queue. 
 *		  data  - the data to be inserted.
 * Return value : 
 *        0-(success), 1-(failure).
 */
int QEnqueue(queue_t *queue, void *data);


/* 
 * Remove a member from the head of the queue.
 * returns a pointer to data
 */ 
void *QDequeue(queue_t *queue);


/* 
 * return a pointer to data at the head of the queue.
 * Return value : 
 *		  a pointer to the head's data. 
 */
void *QPeek(const queue_t *queue);


/* 
 * count number of elements in the queue
 *
 * Return value : 
 *       queue's length.
 */
size_t QSize(const queue_t *queue);


/* 
 * a boolean function that checks if queue has no elements.
 *	
 * Return value : 
 *		  1 - empty, 0 - not empty.
 */
int QIsEmpty(const queue_t *queue);


/* 
 * joins two queues together. free memory of <from> queue.
 * Params: 
 *		  to   - Will be at the head of the new queue.
 *		  from - will come after the <to> and will end the new queue.
 * Return value : 
 *		  a pointer to new appended queue.
 */
queue_t *QAppend(queue_t *to, queue_t *from);

#endif /* _QUEUE_ */
