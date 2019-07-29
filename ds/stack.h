/****************************************************************
*                       Data Structures - Stack                 *
* Related files: stack_test.c, stack.h, stack_test.c            * *															    *
* writer: Dani Benjamin                                         *
* reviewer: Ofer Tauber                                         *
* last update: 29.3.19                                          *
****************************************************************/        
       
#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h> /* size_t */

typedef struct stack stack_t;

/*creates the stack with capacitiy of <capacitiy>, for element of size
 <element_size>. returns a pointer to stack*/
stack_t *StackCreate(size_t element_size, size_t capacity);


/*destroy the stack and free the allocated memory*/
void StackDestroy(stack_t *stack_ptr);


/*insert element <element> to the top of the stack(by value).
*returns 0 to denote success or 1 to denote failure (pushing a full stack).*/
int StackPush(stack_t *stack_ptr, const void *element);


/*remove the element in top of tghe stack(without returning it's value)*/
void StackPop(stack_t *stack_ptr);


/*returns pointer to the top element without modifying the stack*/
void *StackPeek(const stack_t *stack_ptr);


/*returns the size of the stack without modifying it*/
size_t StackSize(const stack_t *stack_ptr);

#endif /*_STACK_H_*/
