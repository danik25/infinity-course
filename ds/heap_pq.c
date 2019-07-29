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

#include "heap.h"
#include "heap_pq.h"

struct pqueue {
    
    heap_t *heap;
    
};

pqueue_t *PQCreate(int (is_before)(const void *data1, const void *data2, void *param),
                                                                  void *param)
{
    pqueue_t *s_q = (pqueue_t *) malloc(sizeof(pqueue_t));
    heap_t *s_heap = NULL;

    if(!s_q)
    {
        return (NULL);
    }
    
    s_heap = HeapCreate(is_before, param);

    if(!s_heap)
    {
        free(s_heap);
        return (NULL);
    }

    s_q->heap = s_heap;
    return (s_q);
}


void PQDestroy(pqueue_t *queue)
{
    assert(queue);

    HeapDestroy(queue->heap);
    free(queue);
    queue = NULL;
}

int PQEnqueue(pqueue_t *queue, void *data)
{
    assert(queue);
    if(!HeapInsert(queue->heap, data))
    {
        return(0);
    }
    return (1);
}

void *PQDequeue(pqueue_t *queue)
{
    void * data = NULL;

    assert(queue);

    data = HeapPeek(queue->heap);
    HeapPop(queue->heap);
    return(data);
}

void *PQPeek(const pqueue_t *queue)
{
    assert(queue);

    if(PQIsEmpty(queue))
    {
        return (NULL);
    }

    return (HeapPeek(queue->heap));
}

int PQIsEmpty(const pqueue_t *queue)
{
    assert(queue);

    return (HeapIsEmpty(queue->heap));
}

size_t PQSize(const pqueue_t *queue)
{
    assert(queue);

    return (HeapSize(queue->heap));
}

void PQClear(pqueue_t *queue)
{
    assert(queue);

    while(!PQIsEmpty(queue))
    {
        PQDequeue(queue);
    }
}

void *PQRemove(pqueue_t *queue, int(* is_match_func)(const void *data, void *arge),
                                                                    void *data)
{
    assert(queue);

    return(HeapRemove(queue->heap, is_match_func, data));
}