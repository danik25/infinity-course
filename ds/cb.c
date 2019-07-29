#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memmove */
#include "cb.h"
#include <errno.h> /* errno, perror */
#define BYTE_SIZE 8

struct circular_buffer
{
	void *array;			/*	circular buffer handle	*/ 
	void *reader;			/*	next element to read 	*/
	void *writer;			/*	next element to write	*/
	size_t size;			/*	number of elements		*/ 
	size_t capacity;		/*	capacity of buffer		*/
};

cb_t *CBCreate(size_t capacity)
{
    cb_t *circ = NULL;
    if (0 == capacity)
    {
        return NULL;
    }
    circ = (cb_t*) malloc(sizeof(cb_t));
    circ->array = (cb_t*) malloc(capacity);
    circ->capacity = capacity;
    circ->size = 0;
    circ->reader = circ->array;
    circ->writer = circ->array;
    
    if (NULL == circ)
    {
    	return NULL;
    }
    if (NULL == circ->array)
    {
        free(circ);
    	return NULL;
    }
    return circ;
}

void CBDestroy(cb_t *buffer)
{
    assert(buffer);
    assert(buffer->array);
    free(buffer->array);
    buffer->array = NULL;
    
    free(buffer);
    buffer = NULL;
}

size_t CBWrite(cb_t *buffer, const void *src, size_t bytes_num)
{
	size_t cnt = 0;
	assert(buffer);
	assert(src);
	while(bytes_num > 0 && buffer->size < buffer->capacity) 
    {     
        memmove((char*)buffer->writer, src, 1);
        ++cnt;
        if((((size_t)buffer->writer) % 
                        ((size_t)buffer->array)) >= buffer->capacity - 1)
        {
            buffer->writer = buffer->array;
        }
        else
        {
        	buffer->writer = ((char*)buffer->writer + 1);
        }
        ++buffer->size;
        src = (char*)src + 1;
        --bytes_num;
    }
    if(bytes_num)
    {
        errno = EOVERFLOW;
    }
    return cnt;
}
size_t CBRead(cb_t *buffer, void *dest, size_t bytes_num)
{
	size_t cnt = 0;
	assert(buffer);
	assert(dest);
	while(bytes_num > 0 && buffer->size > 0 && *(char*)buffer->reader)
    {     
        *(char*)dest = *(char*)buffer->reader;
        ++cnt;
        if((((size_t)buffer->reader) % 
                        ((size_t)buffer->array)) >= buffer->capacity - 1)
        {
            buffer->reader = buffer->array;
        }
        else
        {
        	buffer->reader = (char*)buffer->reader + 1;
        }
        --buffer->size;
        --bytes_num;
        dest = (char*)dest + 1;
    }
    if(bytes_num)
    {
    	errno = ENODATA;
    }
    return cnt;
}

int CBIsEmpty(cb_t *buffer)
{
    assert(buffer);
    if(0 == buffer->size)
    {
        return 1; /*buffer is empty*/
    }
    return 0;
}

size_t CBFreeSpace(cb_t *buffer)
{
    assert(buffer);
    return buffer->capacity - buffer->size;
}

size_t CBCapacity(cb_t *buffer)
{
    assert(buffer);
    return buffer->capacity;
}






