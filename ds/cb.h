/****************************************************************
*                Data Structures - Circular buffer              *
* Related files: cb.c cb_test.c cb.h                            *
* #Version: V.01                                                *
* writer: Dani Benjamin                                         *
* reviewer: Ofer Tauber                                         *
* last update: 3.4.19                                           *
****************************************************************/ 
/*
* Circular buffers (also known as ring buffers) are fixed-size buffers 
* that work as if the memory is contiguous & circular in nature.
* As memory is generated and consumed, data does not need to be
* reshuffled - rather, the writer/reader pointers are adjusted. When data is added,
* the writer pointer advances. When data is consumed, the reader pointer advances.
* If you reach the end of the buffer, the pointers simply wrap around
* to the beginning.
*/  

/* API Design
 
	How users will interact with a circular buffer:

	* create the circular buffer container with a buffer and element sizes
	* destroy a circular buffer container
	* be able to add number of bytes to the buffer
	* be able to get number of bytes from the buffer
	* know whether the buffer is empty
	* know the current number of elements in the buffer
	* know the capacity of the buffer
*/

#ifndef _CB_H_
#define _CB_H_

#include <stddef.h> /* size_t */

typedef struct circular_buffer cb_t;

/*	Creates the circular buffer structure and returns a circular buffer handle.
 *	Parameters:	capacity in bytes
 *
 *	Return: circular buffer handle
 *
 */
cb_t *CBCreate(size_t capacity);


/* 	Free a circular buffer structure and data buffer.
 *
 *	Parameters:	buffer - pointer to circular buffer
 */
void CBDestroy(cb_t *buffer);


/* Writes <bytes_num> from <src> to <buffer>
 * rejects new data if the buffer is full
 * Returns number of bytes written on success,
 * 0 if buffer is full.
 *
 * Parameters:	buffer - pointer to circular buffer
 *				src - pointer of data source
 * 				bytes_num - number of bytes to write
 *
 * Return value: number of bytes actualy written
 *				 or 0 if buffer is full.
 *
 * Time complexity O(bytes_num).
 */
size_t CBWrite(cb_t *buffer, const void *src, size_t bytes_num);


/* Reads <bytes_num> from <buffer> to <dest>
 * Returns number of bytes actualy readed,
 * 0 if buffer is empty.

 * Parameters:	buffer - pointer to circular buffer
 *				dest - pointer of destination data to be readed
 * 				bytes_num - number of bytes to read
 *
 * Return value: number of bytes actualy readed
 				 or 0 if buffer is empty.

 * Time complexity O(bytes_num).
 */
size_t CBRead(cb_t *buffer, void *dest, size_t bytes_num);


/* Checks if buffer is empty
 *
 * Parameters:	buffer - pointer to circular buffer
 *
 * Return value: 1 if buffer is empty, 0 otherwise.
 */
int CBIsEmpty(cb_t *buffer);


/*	Returns available space of the buffer.
 	Parameters:	buffer - pointer to circular buffer
	
	Return: number of available bytes
 */
size_t CBFreeSpace(cb_t *buffer);


/*	Returns total capacity of buffer.
 	Parameters:	buffer - pointer to circular buffer
	
	Return: capacity of circular buffer in bytes
 */
size_t CBCapacity(cb_t *buffer);


#endif /* _CB_H_ */
