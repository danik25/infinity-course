#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include <stddef.h> /* size_t */



/****************************************************************
*                <<<<<<<< ASSIGNMENT NAME >>>>>>>>              *
* Related files: Priority.c, Priority_test.c                    *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Or Stopiky                                          *
* Last update: 17/04/19                                         *
****************************************************************/  
/* API DESCRIPTION:
 *
 * Priority queues are a type of container adaptors, specifically designed such 
 * that its first element is always the greatest of the elements it contains, 
 * according to some strict ordering criterion supplied by the user.
 *
 *
 * 
 */
 

typedef struct pqueue pqueue_t;


/* Description: 
            Creates an empty priority queue.
 *                  
 * Params: 
 *      Is_before - a user supplied function that will determine the 
 *      priority for sorting the elements of the queue.
 *      Param - an additional paramater for the use of the user.      
 *        
 * Return Value: 
 *        Pointer to the newly created queue.        
*/
pqueue_t *PQCreate(int (is_before)(void *data1, void *data2, void *param),
                                                                  void *param);


/* Description:
 *          Free all allocated memory of the queue and destroy the queue. 
 *
 * Params:
 *      queue - the priority queue to be destroyed.  
 *        
 *        
 * Return Value: void       
*/
void PQDestroy(pqueue_t *queue);



/* Description: 
 *          Unserts an element to the queue in a location determined by its
 *          priority.
 *
 * Params: 
 *       queue - the queue to insert to.    
 *       data - the data to insert. 
 *        
 * Return Value: 
 *         status - success(0) or failure(1).
*/
int PQEnqueue(pqueue_t *queue, void *data);



/* Description:
 *          Removes the element with the highest priority from the queue.
 *          Time complexity: O(n)
 *
 * Params:
 *     queue - the queue to remove from.
 *               
 * Return Value: 
 * 
 *      The data of the removed element.
 *      If the queue is empty - returns NULL.     
*/
void *PQDequeue(pqueue_t *queue);



/* Description:
 *          Shows the data of the element with the highest priority.
 *
 * Params:
 *      queue - the queue to look at.  
 *             
 * Return Value: 
 *          The data of the highest priority element.
 *          If the queue is empty - returns NULL.
*/
void *PQPeek(const pqueue_t *queue);



/* Description:
 *          Checks whether the queue is empty or not.
 *
 * Params:
 *      queue - the queue to look in.
 *            
 * Return Value: 
 *      Boolean (TRUE(1) / FALSE(0)).           
*/
int PQIsEmpty(const pqueue_t *queue);



/* Description:
 *          Counts number of element in the queue.
 *
 * Params:
 *     queue - the queue to count.   
 *        
 * Return Value: 
 *      Number of elements.
 *          
*/
size_t PQSize(const pqueue_t *queue);



/* Description:
 *          Free all allocated memory of the queue's elements leaving an
 *          empty queue without destroying it.
 *
 * Params:
 *      queue - te queue to clear.
 *        
 *        
 * Return Value: 
 *              void.
*/
void PQClear(pqueue_t *queue);



/* Description:
 *          Removes a specific element from the queue that matches a user 
 *          specified data.
 * 
 * Params:
 *     is_match_func - used to compare the user data with the queue elements and
 *                     find if a match exist (boolean function).    
 *                     data - the user supplied data for comarison.
 *        
 * Return Value: 
 *              The data of the removed element or NULL if element was not 
 *              found.
*/
void *PQRemove(pqueue_t *queue, int (is_match_func)(void *data, void *args),
                                                                    void *args);
                                                                    
#endif /* _PRIORITY_QUEUE_ */