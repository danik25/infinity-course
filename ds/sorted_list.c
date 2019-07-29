/****************************************************************
*                Data Structures - Sorted List                  *
* Related files:    sorted_list.c    dl_list.h                  *
*	            sorted_list.h    sorted_list_test.c	            *
* #Version: V 1.4                                               *
* Writer: Dani Benjamin                                	        *
* Reviewer: Tom Valershtein                                    	*
* Last update: 16.4.19                                          *
****************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/ 

#include "sorted_list.h"
#include "dl_list.h"


struct sorted_list {

    sort_compare_function_t *IsBefore;
    void * param;
    dll_t *list;

};


sorted_list_t *SortCreate(sort_compare_function_t is_before, void *param)
{
    sorted_list_t *sorted = (sorted_list_t*) malloc(sizeof(sorted_list_t));
    dll_t *dll = NULL; 
    
    if(!sorted)
    {
        return (NULL);
    }
    
    dll = DLCreate();

    if(!dll)
    {
        free(sorted);
        return (NULL);
    }
    
    sorted->IsBefore = is_before;
    sorted->list = dll;
    sorted->param = param;
    
    return (sorted);
}

void SortDestroy(sorted_list_t *sorted_list)
{
    assert(sorted_list);
    
    DLDestroy(sorted_list->list);
    free(sorted_list);
    sorted_list = NULL;
}

int SortIsEmpty(const sorted_list_t *sorted_list)
{
    assert(sorted_list);
    
    return (DLIsEmpty(sorted_list->list));
}

size_t SortSize(const sorted_list_t *sorted_list)
{
    assert(sorted_list);
    
    return (DLCount(sorted_list->list));
}

sorted_iter_t SortEnd(const sorted_list_t *sorted_list)
{
    assert(sorted_list);
    
    return (DLEnd(sorted_list->list));
}

sorted_iter_t SortBegin(const sorted_list_t *sorted_list)
{
    assert(sorted_list);
    
    return (DLBegin(sorted_list->list));
}

sorted_iter_t SortNext(const sorted_iter_t location)
{
    assert(location);
    
    return (DLNext(location));
}

sorted_iter_t SortPrev(const sorted_iter_t location)
{
    assert(location);
    
    return (DLPrev(location));
}

void *SortGetData(const sorted_iter_t location)
{
    assert(location);
    
    return (DLGetData(location));
}

int SortIsSameIter(const sorted_iter_t first_iter, const sorted_iter_t second_iter)
{
    assert(first_iter);
    assert(second_iter);
    
    return (DLSameIter(first_iter, second_iter));
}

sorted_iter_t SortErase(sorted_iter_t location)
{
    assert(location);
    
    return (DLErase(location));
}

sorted_iter_t SortInsert(sorted_list_t *sorted_list, void *data_to_insert)
{
    sorted_iter_t inserted_node = NULL;
    sorted_iter_t answer = NULL; 
    
    assert(sorted_list);
    
    inserted_node = SortBegin(sorted_list);
    while(inserted_node != SortEnd(sorted_list) && 
         (!sorted_list->IsBefore(data_to_insert, SortGetData(inserted_node), 
                                                    sorted_list->param)))
    {
        inserted_node = SortNext(inserted_node);
    }
    answer = (DLInsert(sorted_list->list, inserted_node, data_to_insert));
    if(answer == SortEnd(sorted_list))
    {
        return (NULL);
    }
    return (answer);
}

void *SortPopFront(sorted_list_t *sorted_list)
{
    void * data = NULL;
    
    assert(sorted_list);
    
    if(SortIsEmpty(sorted_list))
    {
        return (NULL);
    }
    
    data = SortGetData(SortBegin(sorted_list));
    DLPopFront(sorted_list->list);
    return (data);
    
}

void *SortPopBack(sorted_list_t *sorted_list)
{
    void * data = NULL;
    
    assert(sorted_list);
    
    if(SortIsEmpty(sorted_list))
    {
        return (NULL);
    }
    
    data = SortGetData(SortPrev(SortEnd(sorted_list)));
    DLPopBack(sorted_list->list);
    return (data);
    
}

int SortForEach(sorted_iter_t from, sorted_iter_t to,
						 	         sort_action_function_t func , void *param)
{
    assert(from);
    assert(to);
    assert(func);
    
    return (DLForEach(from, to, func , param));
}

sorted_iter_t SortFind(sorted_list_t *sorted_list, sorted_iter_t from, 
                  sorted_iter_t to, sort_is_match_function_t func, void *param)
{
    assert(sorted_list);
    assert(from);
    assert(to);
    assert(func);
    
    return (DLFind(sorted_list->list, from, to, func, param));
}

void SortMerge(sorted_list_t *to, sorted_list_t *from)
{
    sorted_iter_t node_to = NULL;
    sorted_iter_t node_from = NULL;
    sorted_iter_t node_from_end = NULL;
    
    assert(to);
    assert(from);
    
    if(SortIsEmpty(from))
    {
        free(from->list);
        free(from);
        from = NULL;
        return;
    }
    
    node_to = SortBegin(to);
    node_from = SortBegin(from);
    node_from_end = node_from;
    
    for(node_to = SortBegin(to); node_to != SortEnd(to) && 
            node_from != SortEnd(from); node_to = SortNext(node_to))
    {
        if(to->IsBefore(SortGetData(node_from), 
                                SortGetData(node_to), to->param))
        {
            while(node_from_end != SortEnd(from) && 
                        to->IsBefore(SortGetData(node_from_end), 
                                SortGetData(node_to), to->param))
            {
                node_from_end = SortNext(node_from_end);
            }
            DLSplice(from->list, node_from, node_from_end, node_to);
            node_from = node_from_end;                    
        }
    }
    while(node_from_end != SortEnd(from))
    {
        node_from_end = SortNext(node_from_end);
    }
    DLSplice(from->list, node_from, node_from_end, node_to);
    
    free(from->list);
    free(from);
    from = NULL;
    
}




