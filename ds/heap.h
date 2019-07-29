/****************************************************************
*                Data Structures - Heap
* file: heap.h
* Related files: heap.c heap_test.c
* #Version: V 1.2
* Writer: Dani Benjamin
* Reviewer: Moshe Greenberg
* Last update: 06/06/19
***************************************************************/

#ifndef _HEAP_
#define _HEAP_

#include <stddef.h>  /* size_t */


/*
 * API Design: a heap is a specialized tree-based data structure which is
 *             essentially an almost complete[1] tree that satisfies the heap
 *             property: in a max heap, for any given node C, if P is a parent
 *             node of C, then the key (the value) of P is greater than or
 *             equal to the key of C.
 */



typedef struct heap heap_t;

/* compare_t  Description:
 *
 * return value: an integer "num" such that:
 *
 *  num < 0 if data1 < data2
 *  num = 0 if data1 = data2
 *  num > 0 if data1 > data2
 *
*/
typedef int (compare_t)(const void *data1, const void *data2, void *param);


/* is_match_t  Description: determine if param is equal to data in the heap.
 *
 * return value: Boolean  - TRUE is match, FALSE otherwise
 *
 *
*/
typedef int (is_match_t)(const void *data1, void *param);





/* Description: creates the heap and its handle.
 *
 * Params: CompareFun - the sorting function
 *         param - parameter for the funcion.
 *
 * Return Value: a pointer to the handle.
 *              NULL in case of failure.
*/
heap_t *HeapCreate(compare_t CompareFunc, void *param);


/* Description: frees the heap and its handle.
 *              If heap is NULL, no operation is performed.
 *
 * Params: heap - pointer to the handle.
 *
*/
void HeapDestroy(heap_t *heap);


/* Description: insert data to the heao
 *
 *
 *
 * Params: heap - pointer to the handle.
 *         data - data to ins ert.
 *
 * Return value: status - 0 - SUCCESS, different value otherwise.
 */
 int HeapInsert(heap_t *heap, const void *data);


/* Description: remove an element by param determined by user.
 *
 *
 *
 * Params: heap - pointer to the handle.
 *         IsMatch - matching function.
 *         param - parameter to matching function.
 *
 * Return value: pointer to the data removed, NULL if no removal
 *               was made.
 */
void *HeapRemove(heap_t *heap, is_match_t IsMatch, void *param);


/* Description: removes the top element of the heap.
 *
 *
 *
 * Params: heap - pointer to the handle.
 *
 */
void HeapPop(heap_t *heap);


/* Description: display the data of the top element of the heap.
 *
 *
 *
 * Params: heap - pointer to the handle.
 *
 *
 * Return value: the data of the top element - NULL if heap is empty.
 */
void *HeapPeek(const heap_t *heap);



/* Description: retrieves the number of elements in the heap.
 *
 *
 *
 * Params: heap - pointer to the handle.
 *
 *
 * Return value: number of elements.
 */
size_t HeapSize(const heap_t *heap);


/* Description: checks if the heap is empty.
 *
 *
 *
 * Params: heap - pointer to the handle.
 *
 *
 * Return value: Boolean - TRUE (1) if empty, FALSE(0) otherwise.
 */
int HeapIsEmpty(const heap_t *heap);


#endif /* _HEAP_ */