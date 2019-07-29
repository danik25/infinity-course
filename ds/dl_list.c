/****************************************************************
*                Data Structures - Double Linked List           *
* Related files: dl_list.c 	dl_list.h	dl_list_test.c	        *
* #Version: V 1.7                                               *
* writer: Dani Benjamin                                 		*
* reviewer: Amir Tzin                               			*
* last update: 14.4.19                                          *
****************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "dl_list.h"

#define DEADBEEF (void*)0xdeadbeefdeadbeef

typedef struct dl_node {

	void *data;
	struct dl_node *next;
	struct dl_node *prev;

}dl_node_t;

struct dl_list {

	dl_node_t head;
	dl_node_t tail;
};

static dl_node_t *DLLNodeCreate(void *data, dl_node_t *next, dl_node_t *prev);

/******************************************************************************/

/*assistance function!!*/
static dl_node_t *DLLNodeCreate(void *data, dl_node_t *next, dl_node_t *prev)
{
    dl_node_t *node = NULL;
    
    node = (dl_node_t*) malloc(sizeof(dl_node_t));
    
    if (NULL == node)
    {
        return (NULL);
    }
    node->data = data;
    node->next = next;
    node->prev = prev;
    
    return (node); 
}

/******************************************************************************/

dll_t *DLCreate()
{
	dll_t *dll = (dll_t*) malloc(sizeof(dll_t));
    if(!dll)
    {
        return (NULL);
    }
    dll->head.data = DEADBEEF;
    dll->tail.data = DEADBEEF;
    
    dll->head.next = &(dll->tail);
    dll->head.prev = NULL;
    
    dll->tail.next = NULL;
    dll->tail.prev = &(dll->head);
    
    return (dll);
}

void DLDestroy(dll_t *dl_list)
{
	dl_node_t *node = NULL;
	
	assert(dl_list);
	
	node = DLBegin(dl_list);

    while(node != DLEnd(dl_list))
    {
        node = DLErase(node);
    }
	
	free(dl_list);
    dl_list = NULL;
}

int DLIsEmpty(const dll_t *dl_list)
{
    assert(dl_list);
	return (DLSameIter(DLBegin(dl_list), DLEnd(dl_list)));
}

size_t DLCount(const dll_t *dl_list)
{
	size_t cnt = 0;
	dl_node_t *node = NULL;
	
	assert(dl_list);

	for(node = DLBegin(dl_list); node != DLEnd(dl_list); node = DLNext(node))
	{
		++cnt;
	}
	return (cnt);
}

dl_iter_t DLEnd(const dll_t *dl_list)
{
    assert(dl_list);
	return (dl_iter_t)&(dl_list->tail);
}

dl_iter_t DLBegin(const dll_t *dl_list)
{
    assert(dl_list);
	return (dl_list->head.next);
}

dl_iter_t DLNext(const dl_iter_t location)
{
    assert(location);

	return (location->next);
}

dl_iter_t DLPrev(const dl_iter_t location)
{
    assert(location);

	return (location->prev);
}

void *DLGetData(const dl_iter_t location)
{
    assert(location);
	return (location->data);
}

int DLSameIter(const dl_iter_t first_iter, const dl_iter_t second_iter)
{
    assert(first_iter);
    assert(second_iter);
	return(first_iter == second_iter);
}

dl_iter_t DLInsert(dll_t *dl_list, dl_iter_t location, void *data_to_insert)
{
	dl_node_t *new_node = NULL;
	
	assert(dl_list);
	assert(location);
    
    new_node = DLLNodeCreate(data_to_insert, NULL, NULL);
	if(!new_node)
	{
		return (&dl_list->tail);
	}
	
	new_node->prev = location->prev;
	new_node->next = location;
	
	location->prev->next = new_node;
	location->prev = new_node;
	
	return 	(new_node);
}

dl_iter_t DLErase(dl_iter_t location)
{
    dl_node_t *next_node = NULL;
    
    assert(location);
    
    if(NULL == location->next || NULL == location->prev)
    {
        return (NULL);
    }
    next_node = location->next;
    
    location->prev->next = location->next;
    location->next->prev = location->prev;
    
    free(location);
    location = NULL;
    
    return (next_node);
}

dl_iter_t DLPushFront(dll_t *dl_list, void *data)
{
	assert(dl_list);
	
	return (DLInsert(dl_list, DLBegin(dl_list), data));
}

dl_iter_t DLPushBack(dll_t *dl_list, void *data)
{
    assert(dl_list);
	
	return (DLInsert(dl_list, DLEnd(dl_list), data));
}

void DLPopFront(dll_t *dl_list)
{
    assert(dl_list);
    DLErase(DLBegin(dl_list));
}

void DLPopBack(dll_t *dl_list)
{    
    assert(dl_list);
    DLErase(DLEnd(dl_list)->prev);
}

int DLForEach(dl_iter_t from, dl_iter_t to,
						 	action_function_t func , void *param)
{
    dl_iter_t node = from;
    int status = 0;
    
    assert(func);
    assert(to);
    assert(from);
    for(; node != to && (!status); node = DLNext(node)) 
    {
        status = func(node->data, param);
    }
    return (status);
}

dl_iter_t DLFind(dll_t *dl_list, dl_iter_t from, dl_iter_t to,
 		compare_function_t func, void *param)
{
    dl_iter_t node = NULL;
    
    assert(dl_list);
    assert(func);
    assert(from);
    assert(to);
    
    node = from;
    while(node != to && (!func(node->data, param)))
    {
        node = DLNext(node);
    }
    return (node);
}

void DLSplice(dll_t *src_list, dl_iter_t from, dl_iter_t to, dl_iter_t location)
{
    dl_iter_t first_src = NULL;
    dl_iter_t last_src = NULL; 
    
    assert(src_list);
    assert(from);
    assert(to);
    assert(location);
    
    if(DLSameIter(to, from))
    {
        return;
    }
    
    /*attaching the from remains*/
    from->prev->next = to;
    
    first_src = from;
    last_src = to;
    
    last_src = last_src->prev;
    
    /*attaching the to remains*/
    to->prev = from->prev;
    
    location->prev->next = first_src;
    first_src->prev = location->prev;
    location->prev = last_src;
    last_src->next = location; 
}


