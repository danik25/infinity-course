/****************************************************************
*                Data Structures - Singly Linked List           *
* Related files:                                                *
* #Version: V 1                                                 *
* writer: Dani Benjamin                                         *
* reviewer: Oded Bryt                                           *
* last update: 10.4.19                                          *
****************************************************************/ 

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "sl_list.h"


/****************************************************************/

sl_node_t *SLLCreate(void *data, sl_node_t *next)
{
    sl_node_t *sl_node = NULL;
    sl_node = (sl_node_t*) malloc(sizeof(sl_node_t));
    if (NULL == sl_node)
    {
        return NULL;
    }
    
    sl_node->data = data;
    sl_node->next = next;
    
    return (sl_node); 
}

/****************************************************************/

void SLLDestroy(sl_node_t *node)
{
    sl_node_t *tmp = NULL;
    
    while(node != NULL)
    {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

/****************************************************************/

sl_node_t *SLLInsert(sl_node_t *node_to_insert, sl_node_t *node_location)
{
	void *tmp = NULL;
	
	assert(node_location);
	
	/* saving the location data */
	tmp = node_location->data;
	
	/* switching the data between the inserted node and the location node */
	node_location->data = node_to_insert->data;
	node_to_insert->data = tmp;
	
	node_to_insert->next = node_location->next;
	node_location->next = node_to_insert;

	return (node_location);
}

/****************************************************************/

sl_node_t *SLLInsertAfter(sl_node_t *node_to_insert, sl_node_t *node_location)
{
    assert(node_to_insert);
    assert(node_location);
    
    node_to_insert->next = node_location->next;
    node_location->next = node_to_insert;
    
    return (node_to_insert); 
}

/****************************************************************/

sl_node_t *SLLRemove(sl_node_t *node_to_remove)
{
	sl_node_t *tmp_next = NULL;
	void *tmp = NULL;
	
	assert(node_to_remove);
	
	if(NULL == node_to_remove->next)
	{
		return (NULL);
	}
	
	/* switching the data between the removed node and the next one */
	tmp = node_to_remove->next->data;
	node_to_remove->next->data = node_to_remove->data;
	node_to_remove->data = tmp;
	
	/* detaching the pointer to the removed node */
	tmp_next = node_to_remove->next;
	node_to_remove->next = node_to_remove->next->next;
	tmp_next->next = NULL;
	
	return (tmp_next);
}

/****************************************************************/

sl_node_t *SLLRemoveAfter(sl_node_t *location)
{
	sl_node_t *tmp = NULL;
	
	assert(location);
	
	if(NULL == location->next)
	{
		return NULL;
	}

    tmp = location->next;
    location->next = location->next->next; 

    tmp->next = NULL;
    
    return (tmp);  
}
/****************************************************************/

int SLLForEach(sl_node_t *node, action_function_t func, void *param)
{
    int status = 0;
    
    assert(node);
    assert(func);
    
    while(node != NULL)
    {
        status = func(node->data, param);
        if(status)
        {
            return (status); /*fail*/
        }
        node = node->next;
    }
    return (status);
}

/****************************************************************/

sl_node_t *SLLFind(sl_node_t *node, is_match_function_t func, void *param)
{
    assert(func);
    while(node != NULL)
    {
        if(func(node->data, param))
        {
            return (node);
        }
        node = node->next;
    }
    return (NULL);
}

/****************************************************************/

size_t SLLCount(const sl_node_t *node)
{
	size_t cnt = 0;
	
	if(NULL == node)
	{
		return (0);
	}
	
	while(node != NULL)
	{
		node = node->next;
		++cnt;
	}
	
	return (cnt);
}

/****************************************************************/
sl_node_t *SLLFlip(sl_node_t *node)
{
    sl_node_t *tmp = NULL;
	sl_node_t *tmp_next = NULL;
	
	assert(node);
	
	while(node)
	{
	    /* appending pointers */
	    tmp = tmp_next;
	    tmp_next = node;
	    node = node->next;
	    
	    /* assign "next" to "previous" */
	    tmp_next->next = tmp;
	}
	
	node = tmp_next;
	
	return (node);
}

/****************************************************************/

sl_node_t *SLLFindIntersection(const sl_node_t *node_1, 
       						   const sl_node_t *node_2)
{
	int gap = 0;
	
	assert(node_1);
	assert(node_2);
	
	gap = SLLCount(node_1) - SLLCount(node_2);
	if(gap > 0)
	{
		while(gap > 0)
		{
			node_1 = node_1->next;
			--gap;
		}
	}
	else
	{
		gap *= -1;
		while(gap > 0)
		{
			node_2 = node_2->next;
			--gap;
		}
	}
	while(node_1 != NULL)
	{
		if(node_1 == node_2)
		{
			return ((sl_node_t *)node_1);
		}
		
		node_1 = node_1->next;
		node_2 = node_2->next;
	}
	return (NULL);	
}

/****************************************************************/

int SLLHasLoop(sl_node_t *node)
{
	sl_node_t *by_one = NULL;
	sl_node_t *by_two = NULL;
	
	assert(node);
	
	by_one = node;
	by_two = node->next;
	
	while (by_one && by_two && by_two->next)
	{
		if(by_one == by_two)
		{
			return (1);
		}
		by_one = by_one->next;
		by_two = by_two->next->next;
	}
	return (0);
}


