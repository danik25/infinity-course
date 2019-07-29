/****************************************************************
*                Data Structures - Queue                        *
* Related files: queue.c, queue_test.c                          *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Lev Shubert                                         *
* Last update: 10/04/19                                         *
****************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "queue.h"
#include "sl_list.h"


struct Queue {	    	  	
				sl_node_t *head;	
				sl_node_t *tail;

};

queue_t *QCreate(void)
{
    queue_t *new_q = NULL;
    size_t address = 0;
    new_q = (queue_t*) malloc(sizeof(queue_t));
    address = 0xDEADBEEF;
    if(!new_q)
    {
        return (NULL);
    }
    new_q->head = SLLCreate((void*)address, NULL);
    new_q->tail = new_q->head;
    
    return (new_q);    
}

void QDestroy(queue_t *queue)
{
    assert(queue);
    SLLDestroy(queue->head);
    free(queue);
    queue = NULL;
}

int QEnqueue(queue_t *queue, void *data)
{
    sl_node_t *tmp = NULL;
    
    assert(queue);
    
    tmp = SLLCreate(data, NULL);
    if(!queue->tail)
    {
        return (1); /* fail */ 
    }
  
    queue->tail = SLLInsert(tmp, queue->tail);
	queue->tail = queue->tail->next;
	
    return (0); /* success */
}

void *QDequeue(queue_t *queue)
{
	sl_node_t *answer = NULL;
    void *answer_data = NULL;
    
    assert(queue);
    
	if(queue->head == queue->tail)
	{
		return (NULL);
	}

    if(1 == QSize(queue))
    {
    	queue->tail = queue->head;
    }
    answer_data = queue->head->data;
    answer = SLLRemove(queue->head);
    
    SLLDestroy(answer);
    
    answer = NULL;
    
    return (answer_data);
}

void *QPeek(const queue_t *queue)
{
	void *data = NULL;
	
	assert(queue);
	
	data = queue->head->data;
	
	if(data != (void*)0xdeadbeef)
	{
		return (data);
	}
	return (NULL);
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	return (queue->head == queue->tail);
}

size_t QSize(const queue_t *queue)
{
	assert(queue);
	return (SLLCount(queue->head) - 1);
}

queue_t *QAppend(queue_t *to, queue_t *from)
{
	assert(to);
	assert(from);
	
	if(QIsEmpty(from))
	{
	    QDestroy(from);
	    return (to);
	}

	to->tail->next = from->head;
	
	free(SLLRemove(to->tail));
	to->tail = from->tail;
	
	free(from);
	
	return (to);
}







