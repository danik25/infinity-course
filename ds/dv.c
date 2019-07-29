#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memmove*/
#include "dv.h"

struct dynamic_vector{

	void *array;
	size_t size; /* number of elements */ 
	size_t init_capacity; /* minimum capacity */
	size_t current_capacity; 
	size_t element_size;

};

dv_t *DVCreate(size_t capacity, size_t element_size)
{
    dv_t *vector = (dv_t*) malloc(sizeof(dv_t));
    vector -> array = (dv_t*) malloc(capacity * element_size);
    vector -> element_size = element_size;
    vector -> init_capacity = capacity;
    vector -> current_capacity = capacity;
    vector -> size = 0;
    
    if (NULL == vector || NULL == vector -> array)
    {
    	return NULL;
    }
    return vector;
}

void DVDestroy(dv_t *vector)
{
    assert(vector);
	
    free(vector -> array);
    vector -> array = NULL;
    free(vector);
    vector = NULL;
}

int DVPushBack(dv_t *vector, const void *element)
{
    dv_t *tmp = NULL;
    assert(vector);
	assert(element);
	if (vector -> size == vector -> current_capacity )
	{
	    tmp = realloc(vector -> array,
	                 2 * (vector -> current_capacity * vector -> element_size));
	    if (!tmp)
	    {
	        return 1;
	    }
	    vector -> array = tmp;
	    vector -> current_capacity *= 2;
	}

	memmove((char*)vector -> array + (vector -> size * vector -> element_size),
	    element, vector -> element_size);
	vector -> size += 1;
		
	return 0;
}

void *DVGetItemAddress(const dv_t *vector, size_t index)
{
    assert(vector);
    if(index >= vector -> size)
    {
        return (NULL);
    }
    return ((char*)vector -> array + index * (vector -> element_size));
}

void DVPopBack(dv_t *vector)
{
    dv_t *tmp = NULL;
    size_t tmp_vector = vector -> current_capacity;
    assert(vector);
    
    if(0 == vector -> size)
    {
        return;
    }  
    
    vector -> size -= 1;
    /* making the vector samller by half */
    if (vector -> size * 4 <= vector -> current_capacity)
    {
        if(vector -> init_capacity * 2 <= vector -> current_capacity)
        {
            tmp_vector /= 2;
        }
        else
        {
            tmp_vector = vector -> init_capacity;
        }
        
        tmp = realloc(vector -> array, 
                            tmp_vector * vector -> element_size);
        /* checking if the reallocation failed */
        if (tmp)
        {
            vector -> current_capacity = tmp_vector;
            vector -> array = tmp;
        }
    }
}

size_t DVSize(const dv_t *vector)
{
    assert(vector);
    return vector -> size;
}

size_t DVCapacity(const dv_t *vector)
{
    assert(vector);
    return vector -> current_capacity;
}

int DVReserve(dv_t *vector, size_t new_capacity)
{
    dv_t *tmp = NULL;
    assert(vector);
    if (new_capacity > vector -> current_capacity)
    {
        tmp = realloc(vector -> array, 
                        new_capacity * vector -> element_size);
        /* checking if the reallocation failed */
        if (tmp)
        {
            vector -> array = tmp;
            vector -> current_capacity = new_capacity;
            return 0;
        }
    }
    return 1;
}



