/******************************************************************************
 * File name  : fsm.h
 * Version    : 1.1
 * Developer  : Dani Benjamin
 * Reviewer   : Yuval Shapira
 * Date		  : 28.4.19
 ******************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h>

#include "fsm.h"

#define WORD_SIZE 8
#define PADDING(x) ((x >= WORD_SIZE) ? (WORD_SIZE - x % WORD_SIZE) : (WORD_SIZE - x))

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
	size_t increment = 0;
	size_t increment_track = 0;

	assert(pool);

	/*if the size isnt enough for the managment strucnt and one blloch header*/
	if(pool_size < sizeof(fsm_t) + sizeof(meta_t))
	{
		return (NULL);
	}

	/*assigning*/
	pool_handle = pool;
	runner = (meta_t*)pool + sizeof(fsm_t) / sizeof(meta_t);

	increment = block_size + PADDING(block_size) + sizeof(meta_t);
	increment_track = increment + sizeof(fsm_t);

	for(; (char*)runner < (char*)pool + pool_size - increment; 
										runner += increment / sizeof(meta_t))
	{
		runner->offset = increment_track; 
		increment_track += increment;
	}
	runner->offset = 0;

	/*pool handle*/
	pool_handle->next_free = *(char*)pool + sizeof(fsm_t);
	pool_handle->block_size = block_size;
	pool_handle->num_of_blocks = (pool_size - sizeof(fsm_t)) / increment;

	return (pool_handle);
}

/***************************************************************************/

void *FSMAlloc(fsm_t *fsm_handle)
{
	meta_t *runner = NULL;
	assert(fsm_handle);

	/*if there is no free blocks*/
	if((fsm_handle->next_free) == 0)
	{
		return(NULL);
	}

	/*swapping the data in the meta data strcut*/
	runner = (meta_t *)fsm_handle + fsm_handle->next_free / sizeof(meta_t);
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

	runner = (meta_t*)block_addr - sizeof(meta_t) / sizeof(meta_t);
	pool_handle = (fsm_t*)runner - runner->offset / sizeof(fsm_t);

	tmp = runner->offset;
	runner->offset = pool_handle->next_free;
	pool_handle->next_free = tmp;
}

/***************************************************************************/

size_t FSMCountFree(fsm_t *fsm_handle)
{
	meta_t* runner = NULL;
	size_t cnt = 1;

	assert(fsm_handle);

	runner = (meta_t*)fsm_handle + fsm_handle->next_free / sizeof(meta_t);
	while(runner->offset != 0)
	{
		++cnt;
		runner += fsm_handle->block_size + PADDING(fsm_handle->block_size)
										+sizeof(meta_t);
	}
	return (cnt);
}

/***************************************************************************/

size_t FSMSuggestSize(size_t block_num ,size_t block_size)
{
	return (block_num * (sizeof(meta_t) + block_size + PADDING(block_size)) + 
													sizeof(fsm_t));
}