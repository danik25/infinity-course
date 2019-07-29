#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "stack.h"

static void StackTest();
static void PeekTest(stack_t *my_stack);
static void PushTest(stack_t *my_stack, const void *element);
static void SizeTest(const stack_t *stack_ptr);

int main()
{
    StackTest();

    return 0;
}

static void StackTest()
{    	
    size_t size = 4;
    size_t amount = 2;
    int elemet1 = 1;
    int elemet2 = 2;
    int elemet3 = 3;
    
    stack_t *my_stack = NULL;
    
    /*****creating a new stack*****/
    printf("----creating a new stack----\n\n");
    my_stack = StackCreate(size, amount);
    
    /*****pushing new elements*****/
    printf("\n----pushing a new elements----\n\n");
    PushTest(my_stack, &elemet1);
    PushTest(my_stack, &elemet2);
    
    printf("\n----checking a push to a full stack----\n\n");
    PushTest(my_stack, &elemet3);
    
    /*****checking the size *****/
    SizeTest(my_stack);
    
    /*****peeking*****/
    PeekTest(my_stack);
    
    printf("\n----poping element----\n\n");
    StackPop(my_stack);
    
    /*****peeking*****/
    PeekTest(my_stack);
    
    printf("\n----poping element----\n\n");
    StackPop(my_stack);
    
    printf("----checking a peek to an empty stack----\n");
    PeekTest(my_stack);
    
    printf("----checking the size of an empty stack----\n");
    SizeTest(my_stack);
    
    printf("----checking the pop command to an empty stack----\n");
    StackPop(my_stack);
    
    printf("----checking the push command to an empty stack----\n");
    PushTest(my_stack, &elemet3);
    PeekTest(my_stack);
    
    printf("----destroying the stack----\n\n");
    StackDestroy(my_stack);    
}


static void PeekTest(stack_t *my_stack)
{
	assert(my_stack);
	printf("\n****peeking****\n\n");
	if ((int*)(StackPeek(my_stack)))
	{
    	printf("the current element is: %d\n", 
    							*(int*)(StackPeek(my_stack)));
    }
    else
    {
    	printf("unsuccessfull peek, empty stack\n\n");
    } 
}

static void PushTest(stack_t *my_stack, const void *element)
{
	assert(my_stack);
	if (!StackPush(my_stack, element))
	{
		printf("successfull push of the element '%d'\n", *(char*)element);
	}
}

static void SizeTest(const stack_t *stack_ptr)
{
	int size= StackSize(stack_ptr);
	assert(stack_ptr);
	printf("\n****size of****\n\n");
	
	if (0 == size)
	{
		printf("no size, empty stack\n\n");
	}
	else 
	{
		printf("the size of the stack is: %d\n\n", size);
	}
}




