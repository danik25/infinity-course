/****************************************************************
*                Data Structures - Heap
* file: heap.c
* Related files: heap.h heap_test.c
* #Version: V 1.1
* Writer: Dani Benjamin
* Reviewer: Moshe Greenberg
* Last update: 06/06/19
***************************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "heap.h"
#include "dv.h"

#define CAPACITY 10
#define PTR_SIZE sizeof(void*)
#define PARENT(index) (((index) - (1)) / (2))
#define LEFT_CHILD(index) (((2) * (index)) + (1))
#define RIGHT_CHILD(index) (((2) * (index)) + (2))
#define UNUSED(x) (void)(x)

static void SwapPointers(void **ptr1, void **ptr2);
static void HeapifyUp(void** first_address, void** second_address, 
                                            size_t index, heap_t *heap);
static void HeapifyDown(void** element, size_t index, heap_t *heap);
static int FindElementIndex(heap_t *heap, is_match_t IsMatch, void *data);
static int SmallChildIndex(heap_t *heap, size_t index); 
static int IsMatchStub(const void *data1, void *param);

enum STATUS {SUCCESS, FAIL};

struct heap
{
	size_t size;
	compare_t *CompareFunc;
	void *param;
	dv_t *vector;
};

/*****************************************************************************/

heap_t *HeapCreate(compare_t CompareFunc, void *param)
{
    heap_t* heap_handle = NULL;

    assert(CompareFunc);

    heap_handle = (heap_t*)malloc(sizeof(heap_t));

    if(NULL == heap_handle)
    {
        return(NULL);
    }

    heap_handle->size = 0;
    heap_handle->CompareFunc = CompareFunc;
    heap_handle->param = param;
    heap_handle->vector = DVCreate(CAPACITY, PTR_SIZE);

    if(NULL == heap_handle->vector)
    {
        free(heap_handle);
        heap_handle = NULL;
        return(NULL);
    }

    return(heap_handle);
}

/*****************************************************************************/

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DVDestroy(heap->vector);
    free(heap);
    heap = NULL;
}

/*****************************************************************************/

int HeapInsert(heap_t *heap, const void *data)
{
    size_t index = 0;
    void** first_address = NULL;
    void** second_address = NULL; 

    assert(heap);

    if(DVPushBack(heap->vector, &data))
    {
        return(FAIL);
    }

    index = DVSize(heap->vector) - 1;  

    first_address = DVGetItemAddress(heap->vector, index);
    second_address = DVGetItemAddress(heap->vector, PARENT(index));

    HeapifyUp(first_address, second_address, index, heap);
    ++heap->size;
    
    return(SUCCESS);
}

/*****************************************************************************/

void *HeapRemove(heap_t *heap, is_match_t IsMatch, void *param)
{
    size_t index = 0;
    void** element = NULL;
    void** parent = NULL;
    void* last_element = NULL;
    void* data = NULL;

    assert(heap);
    assert(IsMatch);

    index = FindElementIndex(heap, IsMatch, &param);

    /* if the data to remove doesn't exists */
    if(index >= heap->size)
    {
        return (NULL);
    }
    element = DVGetItemAddress(heap->vector, index);

    /* switching between the element to be removed and the last element, 
                                        and then removing the last element */
    data = *(void**)DVGetItemAddress(heap->vector, index);
    last_element = DVGetItemAddress(heap->vector, heap->size - 1);
    SwapPointers(element, last_element);
    
    --heap->size;

    if(LEFT_CHILD(index) > heap->size - 1)
    {
        parent = DVGetItemAddress(heap->vector, PARENT(index));
        HeapifyUp(element, parent, index, heap);
    }
    else
    {
        HeapifyDown(element, index, heap);
    }

    DVPopBack(heap->vector);
    return(data);
}

/*****************************************************************************/

void HeapPop(heap_t *heap)
{
    assert(heap);

    HeapRemove(heap, IsMatchStub, heap->param);
}

/*****************************************************************************/

void *HeapPeek(const heap_t *heap)
{
    void **tmp_data = NULL;
    assert(heap);

    tmp_data = DVGetItemAddress(heap->vector, 0);

    if(NULL == tmp_data)
    {
        return (NULL);
    }

    return(*tmp_data);
}

/*****************************************************************************/

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return(heap->size);
}

/*****************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return(0 == heap->size);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void SwapPointers(void **ptr1, void **ptr2)
{
    void *temp = NULL;

    assert(ptr1);
    assert(ptr2);

    temp = *ptr1;
    *ptr1= *ptr2;
    *ptr2 = temp;
}

static void HeapifyUp(void** first_address, void** second_address, 
                                            size_t index, heap_t *heap)
{
    while(index > 0 && (heap->CompareFunc(*first_address, *second_address, 
                                                            heap->param) < 0))
    {
        SwapPointers(first_address, second_address);

        index = PARENT(index);

        first_address = DVGetItemAddress(heap->vector, index);
        second_address = DVGetItemAddress(heap->vector, PARENT(index));
    }
}

static void HeapifyDown(void** element, size_t index, heap_t *heap)
{
    void** small_child = NULL;
    size_t child_index = 0;

    child_index = SmallChildIndex(heap, index);

    small_child = DVGetItemAddress(heap->vector, child_index); 

    while(child_index < heap->size && 
            (heap->CompareFunc(*element, *small_child, heap->param) >= 0))
    {
        SwapPointers(element, small_child);

        element = small_child;

        child_index = SmallChildIndex(heap, child_index);
        small_child = DVGetItemAddress(heap->vector, child_index);
    }
}

static int SmallChildIndex(heap_t *heap, size_t index) 
{
    void** left_child = NULL;
    void** right_child = NULL;
    int child_index = 0;

    if(RIGHT_CHILD(index) > heap->size - 1 || LEFT_CHILD(index) > heap->size)
    {
        return(LEFT_CHILD(index));
    }

    left_child = DVGetItemAddress(heap->vector, LEFT_CHILD(index));
    right_child = DVGetItemAddress(heap->vector, RIGHT_CHILD(index));

    child_index = 
            (heap->CompareFunc(*left_child, *right_child, heap->param) < 0) ?
            LEFT_CHILD(index) : RIGHT_CHILD(index);

    return(child_index);
}

static int FindElementIndex(heap_t *heap, is_match_t IsMatch, void *data)
{
    size_t i = 0;
    void **elem = NULL;
    void **p_data = data;

    for(i = 0; i < heap->size; ++i)
    {
        elem = DVGetItemAddress(heap->vector, i);
        if(IsMatch(*elem, *p_data))
        {
            return(i);
        }
    }
    return(i);
}

static int IsMatchStub(const void *data1, void *param)
{
    UNUSED(data1);
    UNUSED(param);
    return(1);
}