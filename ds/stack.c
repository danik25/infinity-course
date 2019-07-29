#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/

#include "stack.h"

struct stack
{
    void *end;
    void *current;
	size_t element_size;
	void *head;
};

stack_t *StackCreate(size_t element_size, size_t capacity)
{    
    stack_t *stack = malloc(sizeof(stack_t));
    stack -> head = malloc(capacity * element_size);
    
    stack -> end = (char*)stack -> head + capacity * element_size;
    stack -> element_size = element_size;
    /*current is pointing to one element size under the head*/
    stack -> current = (char*)stack -> head - element_size;
    
    if (NULL == stack || NULL == stack->head)
    {
    	return NULL;
    }
    return stack;
}

void StackDestroy(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
    free(stack_ptr -> head);
    stack_ptr -> head = NULL;
    free(stack_ptr);
    stack_ptr = NULL;
}

int StackPush(stack_t *stack_ptr, const void *element)
{
	assert(stack_ptr);
	assert(element);
	/*empty stack*/
	if (stack_ptr -> current == NULL)
	{
	    stack_ptr -> current = (char*)stack_ptr -> head - stack_ptr ->
	                                element_size;
	}
	else if (stack_ptr -> head == NULL)
	{
	    fprintf(stderr, "%s", "unsuccessfull push, no stack\n\n");
	        return 1;
	}

    else if ((char*)stack_ptr -> current + stack_ptr -> element_size == 
    								stack_ptr -> end)
    {
        fprintf(stderr, "%s", "unsuccessfull push, full stack\n\n");
     	return 1; /*full stack*/
    }
    stack_ptr -> current = (char*)stack_ptr -> current + 
    								stack_ptr -> element_size;
    memcpy(stack_ptr -> current, element, stack_ptr -> element_size);
    
    return 0;
}

void StackPop(stack_t *stack_ptr)
{
	assert(stack_ptr);
	
    if (stack_ptr -> current < stack_ptr -> head)
    {
        fprintf(stderr, "%s", "unsuccessfull pop, empty stack\n\n");
    }
    else
    {
        stack_ptr -> current = (char*)stack_ptr -> current - stack_ptr ->
                                                                element_size;
        /*if it was the last element in the stack*/
        if (stack_ptr -> current < stack_ptr -> head)
        {
        	stack_ptr -> current = NULL;
        }
    }
}

void *StackPeek(const stack_t *stack_ptr)
{
	assert (stack_ptr);
    return stack_ptr->current;
}

size_t StackSize(const stack_t *stack_ptr)
{	
	size_t size = ((char*)stack_ptr->current - (char*)stack_ptr->head +
	                        stack_ptr->element_size)/stack_ptr->element_size;
	
	assert(stack_ptr);
	
	if (stack_ptr -> current < stack_ptr -> head)
	{
		return 0;
	}
	return size;
}







