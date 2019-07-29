/******************************************************************************
 * File name  : fsm.h
 * Version    : 1.2
 * Developer  : Dani Benjamin
 * Reviewer   : Ayala Rosel
 * Date		  : 30.4.19
 ******************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fsm.h"

#define END 0
#define WORD_SIZE 8
#define PADDING(x) (WORD_SIZE - x % WORD_SIZE) % WORD_SIZE 
                                                   

struct fsm_manager
{
	size_t next_free;
	size_t block_size;
	size_t num_of_blocks;
};

/* block header struct */ 
typedef struct block_metadata
{	
	size_t offset;
}meta_t;

/***************************************************************************/

fsm_t *FSMInit(void *pool, size_t pool_size, size_t block_size)
{
	fsm_t *pool_handle = NULL;
	meta_t *runner = NULL;
	size_t real_block_size = 0;
	size_t real_block_size_track = 0;
	size_t i = 0;

	assert(pool);

	/*if the size isnt enough for the managment strucnt and one blloch header*/
	if(pool_size < sizeof(fsm_t) + sizeof(meta_t) + block_size)
	{
		return (NULL);
	}
	/*assigning*/
	pool_handle = pool;
	runner = (meta_t*)((char*)pool + sizeof(fsm_t));

	real_block_size = block_size + PADDING(block_size) + sizeof(meta_t);
	real_block_size_track = real_block_size + sizeof(fsm_t);

	/*pool handle*/
	pool_handle->next_free = sizeof(fsm_t);
	pool_handle->block_size = block_size;
	pool_handle->num_of_blocks = (pool_size - sizeof(fsm_t)) / real_block_size;

	if((pool_size - real_block_size * pool_handle->num_of_blocks - 
							sizeof(fsm_t)) >= sizeof(meta_t) + block_size)
	{
		++pool_handle->num_of_blocks;
	}

	for(i = 1; i < pool_handle->num_of_blocks; ++i,
								runner += real_block_size / sizeof(meta_t))
	{
		runner->offset = real_block_size_track; 
		real_block_size_track += real_block_size;
	}
	runner->offset = END;

	return (pool_handle);
}

/***************************************************************************/

void *FSMAlloc(fsm_t *fsm_handle)
{
	meta_t *runner = NULL;

	assert(fsm_handle);

	/*if there is no free blocks*/
	if(END == (fsm_handle->next_free))
	{
		return(NULL);
	}

	/*swapping the data in the meta data strcut*/
	runner = (meta_t *)((char*)fsm_handle + fsm_handle->next_free);
	fsm_handle->next_free = runner->offset;
	runner->offset = (runner - (meta_t *)fsm_handle) * sizeof(meta_t);

	return ((char*)runner + sizeof(meta_t));
}

/***************************************************************************/

void FSMFree(void *block_addr)
{
	fsm_t *pool_handle = NULL;
	meta_t* runner = NULL;
	size_t tmp = 0;

	assert(block_addr);

	runner = (meta_t*)((char*)block_addr - sizeof(meta_t));
	pool_handle = (fsm_t*)((char*)runner - runner->offset);

	tmp = runner->offset;
	runner->offset = pool_handle->next_free;
	pool_handle->next_free = tmp;
}

/***************************************************************************/

size_t FSMCountFree(const fsm_t *fsm_handle)
{
	meta_t* runner = NULL;
	size_t cnt = 1;

	assert(fsm_handle);

	runner = (meta_t*)((char*)fsm_handle + fsm_handle->next_free);

    if(END == fsm_handle->next_free)
    {
        return(0);
    }

	while(runner->offset != END)
	{
		++cnt;
		runner = (meta_t*)((char*)fsm_handle +runner->offset);
	}
	return (cnt);
}


/***************************************************************************/

size_t FSMSuggestSize(size_t block_num ,size_t block_size)
{
	return (block_num * (sizeof(meta_t) + block_size + PADDING(block_size)) + 
													sizeof(fsm_t));
}