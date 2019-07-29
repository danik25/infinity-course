/******************************************************************************
 * File name  : fsm.h
 * Version    : 1.1
 * Developer  : Dani Benjamin
 * Reviewer   : Yuval Shapira
 * Date		  : 28.4.19
 ******************************************************************************/
#ifndef __FSM_H__
#define __FSM_H__

#include <stddef.h> /* size_t */

/* API Description
 * FSM - Fixed Size Malloc, is a product that manages allocations of fixed sized
 * blocks. user provides the pool of allocated memory.
 */


typedef struct fsm_manager fsm_t;


/* description:
 *				initialize the memory pool provided by the user
 *              to fixed size blocks. 
 *
 * parameters: 
 *              pool - pointer to the user's allocated memory.
 *				pool_size - size of the user's allocated memory (in bytes).
 *				block_size - size of each block.
 *
 * return value: 
 *				pointer to the memory manager handler or
 *				NULL if failes.
 */				
fsm_t *FSMInit(void *pool, size_t pool_size, size_t block_size);


/* description:
 *				allocates a single block (with the size of block size). 
 *
 * parameters: 
 *              fsm_handle - pointer to the memory manager handler.
 *
 * return value: 
 *				pointer to the beginning of the allocated block
 *              NULL if no blocks available.
 */	
void *FSMAlloc(fsm_t *fsm_handle);


/* description:
 * 				frees a single block (with the size of block size). 
 *
 * parameters: 
 *              block_addr - pointer to the block to be freed.
 *
 * return value: 
 *				none.
 */	
void FSMFree(void *block_addr);


/* description:
 *				counts the number of free blocks in the pool.
 *
 * parameters: 
 *              fsm_handle - pointer to the memory manager handler.
 *
 * return value: 
 *				the number of free blocks.
 *
 *  complexity:
 *				O(n).
 */	
size_t FSMCountFree(fsm_t *fsm_handle);


/* description:
 *				calculates the suggested size of memory needed
 *			    to suit the user's demands. 
 *
 * parameters: 
 *              block_num - number of blocks in the pool.
 *				block_size - size of every block in the pool.
 *
 * return value: 
 *				suggested memory size to allocate (in bytes).
 */	
size_t FSMSuggestSize(size_t block_num ,size_t block_size);


#endif /* __FSM_H__ */ 