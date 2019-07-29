/******************************************************************************
 * File name  : VARIABLE SIZE MEMORY ALLOCATION
 * Version    : 1.2
 * Developer  : Dani Benjmain
 * Reviewer   : Or Stopiky
 * Date       : 1.5.19
 ******************************************************************************/
#ifndef __VSM_H__
#define __VSM_H__

#include <stddef.h> /* size_t */

/* API Description
 * VSM - Variable memory allocation, is a product that manages allocation and
         freeing proccesses of varaible sized chunks of memory requested by 
         the user. Usable size of memory will be smaller then actually allocated
         due to memory usage of the product itself.
 */

typedef struct vsm_block_header vsm_t;


/* Description:
 *              Initialize the memory pool provided by the user. works under the
                asumption that the user passes word size alligned address.
 *               
 *
 * Parameters: 
 *              pool - pointer to the user's allocated memory.
 *              pool_size - size of the user's allocated memory (in bytes).
 *
 * Return value: 
 *              pointer to the memory manager handler. NULL if failed.
 */             
vsm_t *VSMInit(void *pool, size_t pool_size);



/* Description:
 *              allocates requested number of bytes. 
 *
 * parameters: 
 *              vsm_handle - pointer to the memory manager handler.
 *              byte_num - number of bytes to allocate.
 *
 * return value: 
 *              pointer to the beginning of the allocated block. NULL if failed.
 *
 *  complexity:
 *              ~O(n).
 */ 
void *VSMAlloc(vsm_t *vsm_handle, size_t byte_num);



/* description:
 *              frees a single block (with the size of block size). 
 *
 * parameters: 
 *              block_addr - pointer to the block to be freed.
 *
 * return value: 
 *              none.
 *
 *  complexity:
 *              O(1).
 */ 
void VSMFree(void *block_addr);


/* description:
 *              get the largest free chunk.
 *
 * parameters: 
 *              vsm_handle - pointer to the memory manager handler.
 *
 * return value: 
 *              size of largest chunk. (0) if no free space.
 *
 * complexity:
 *              ~O(n).
 */
size_t VSMFindLargestChunk(vsm_t *vsm_handle);





#endif /* __VSM_H__ */ 