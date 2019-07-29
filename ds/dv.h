/****************************************************************
*                       Data Structures - Dynamic vector        *
* Related files: dv.c, dv_test.c, dv.h                          *
* #Version: V.01                                                *
* writer: Dani Benjmain                                         *
* reviewer: Kobi Madrish                                        *
* last update: 1.4.19                                           *
****************************************************************/ 
/*
*   Dynamic vector is a sequence container representing 
*   array that can change in size.
*   Dynamic vector use contiguous storage locations for its elements,
*   and its size can change dynamically.
*/  

#ifndef _DV_H_
#define _DV_H_

#include <stdio.h> /* size_t */

typedef struct dynamic_vector dv_t;

/*  
*   dv_t *DVCreate(size_t capacity, size_t element_size)  
* 
*   Description:
*       Create a dynamic vector, initializing its contents 
*       depending on given capacity and element size. 
*
*   Params:
*       capacity:  the maximum size of the vector. [size_t]
*       element_size: size of element. [size_t]  
*    
*   Return value: 
*       the new vector. [dv_t *]
*/
dv_t *DVCreate(size_t capacity, size_t element_size);


/*  
*   void DVDestroy(dv_t *vector)
*   
*   Description:
*       Destroy the vector, and deallocate all the storage 
*       capacity allocated by the vector using its allocator.  
*
*   Params:
*       vector: the vector to destroy. [dv_t *] 
*/
void DVDestroy(dv_t *vector); 


/*  
*   int DVPushBack(dv_t *vector, const void *element) 
*  
*   Description:
*       Adds a new element at the end of the vector, 
*       after its current last element.
*    
*   Params:
*       vector: the vector to append to it. [dv_t *]
*       element: the element to be add. [Const void *]
*      
*   Return value: 
*       0 if success, 1 if fail (if the allocation 
*       request does not succeed). [int]
*/
int DVPushBack(dv_t *vector, const void *element);


/*  
*   void DVPopBack(dv_t *vector)  
* 
*   Description:
*       Removes the last element in the vector. 
*  
*   Params:
*       vector: the vector to remove from. [dv_t *]
*/
void DVPopBack(dv_t *vector);


/*  
*   void *DVGetItemAddress(const dv_t *vector, size_t index)  
*
*   NOTE: 
*       DVPushBack() and DVPopBack invalidates 
*       DVGetItemAddress()'s reurn value !!!!!
*
*   Description:
*       Get the address of the item at 
*       position <index> in the vector.
*        
*   Params:
*       vector: the vector to get the item address from it. [const dv_t *]
*       index: position of an element in the vector. [size_t]    
*  
*   Return value: 
*       the address of the item at the specified position in the vector [void *]
*/
void *DVGetItemAddress(const dv_t *vector, size_t index);


/*  
*   size_t DVSize(const dv_t *vector)
*  
*   Description:
*       Get the number of elements in the vector.
*    
*   Params:
*       vector: the vector to get its size. [const dv_t *]
*      
*   Return value: 
*       the nubmer of elements in the vector. [size_t]
*/
size_t DVSize(const dv_t *vector);


/*  
*   size_t DVCapacity(const dv_t *vector)
*  
*   Description:
*       Get size of current allocated storage capacity.
*    
*   Params:
*       vector: the vector to get its capacity. [const dv_t *]
*      
*   Return value: 
*       the size of the storage space currently allocated for 
*       the vector, expressed in terms of elements. [size_t]
*/
size_t DVCapacity(const dv_t *vector);
 
 
/*  
*   int DVReserve(dv_t *vector, size_t new_capacity)
*  
*   Description:
*       Request a change in capacity of the vector.
*
*   NOTE: If new_capacity < size, do not make any changes and return success.
*    
*   Params:
*       vector: the vector to change its capacity. [const dv_t *]
*       new_capacity: the new capacity to be set.[size_t]
*      
*   Return value: 
*       0 if success, 1 if fail(if the allocation 
*       request does not succeed). [int] 
*/
int DVReserve(dv_t *vector, size_t new_capacity);

#endif /* _DV_H_ */
