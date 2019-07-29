/****************************************************************
*                <<<<<<<< ASSIGNMENT NAME >>>>>>>>              *
* Related files: Priority.c, Priority_test.c                    *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Or Stopiky                                          *
* Last update: 17/04/19                                         *
****************************************************************/ 
#include <stdlib.h> /*free*/
#include <assert.h> /*assert*/

#include "sorted_list.h"
#include "pq.h"

struct pqueue {
    
    sorted_list_t *sorted_list;
    
};

pqueue_t *PQCreate(int (is_before)(void *data1, void *data2, void *param),
                                                                  void *param)
{
    pqueue_t *s_q = (pqueue_t *) malloc(sizeof(pqueue_t));
    sorted_list_t *s_list = NULL;

    if(!s_q)
    {
        return (NULL);
    }
    
    s_list = SortCreate(is_before, param);

    if(!s_list)
    {
        free(s_q);
        return (NULL);
    }

    s_q->sorted_list = s_list;
    return (s_q);
}


void PQDestroy(pqueue_t *queue)
{
    assert(queue);

    SortDestroy(queue->sorted_list);
    free(queue);
    queue = NULL;
}

int PQEnqueue(pqueue_t *queue, void *data)
{
    assert(queue);

    if(SortInsert(queue->sorted_list, data))
    {
        return(0);
    }
    return (1);
}

void *PQDequeue(pqueue_t *queue)
{
    assert(queue);

    return (SortPopFront(queue->sorted_list));
}

void *PQPeek(const pqueue_t *queue)
{
    assert(queue);

    if(PQIsEmpty(queue))
    {
        return (NULL);
    }

    return (SortGetData(SortBegin(queue->sorted_list)));
}

int PQIsEmpty(const pqueue_t *queue)
{
    assert(queue);

    return (SortIsEmpty(queue->sorted_list));
}

size_t PQSize(const pqueue_t *queue)
{
    assert(queue);

    return (SortSize(queue->sorted_list));
}

void PQClear(pqueue_t *queue)
{
    assert(queue);

    while(!PQIsEmpty(queue))
    {
        PQDequeue(queue);
    }
}

void *PQRemove(pqueue_t *queue, int(* is_match_func)(void *data, void *arge),
                                                                    void *data)
{
    sorted_iter_t node = NULL;
    void * removed_data = NULL;
    node = SortFind(queue->sorted_list, SortBegin(queue->sorted_list), 
        SortEnd(queue->sorted_list), is_match_func, data);
    if(node != SortEnd(queue->sorted_list))
    {
        removed_data = SortGetData(node);
        SortErase(node);
    }
    return (removed_data);
}