/****************************************************************
*                Data Structures - Hash Table`
* file: hash_table.h
* Related files: hash_table.c, hash_table_test.c
* #Version: V 1.1
* Writer: Dani Benjmain
* Reviewer: Idan Argaman
* Last update: 04/06/19
****************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dl_list.h"
#include "hash_table.h"

enum STATUS {SUCCESS, FAIL};

struct hash_table
{
    size_t capacity;
    hash_func_t *HashFunc;
    compare_function_t *CompareFunc;
    size_t size;
    dll_t *table[1];
};

static void FillHash(dll_t *table[1], size_t capacity); 

hash_t *HashCreate(size_t capacity, hash_func_t HashFunc, 
                                    compare_function_t CompareFunc)
{
    hash_t *hash_handle = (hash_t*)malloc(sizeof(hash_t) + 
                                    sizeof(void*) * (capacity - 1));
    assert(HashFunc);
    assert(CompareFunc);

    if(NULL == hash_handle)
    {
        return (NULL);
    }

    hash_handle->capacity = capacity;
    hash_handle->HashFunc = HashFunc;
    hash_handle->CompareFunc = CompareFunc;
    hash_handle->size = 0;

    FillHash(hash_handle->table, capacity);

    return(hash_handle);
}

void HashDestroy(hash_t *table)
{
    size_t i = 0;

    assert(table);

    for(i = 0; i < table->capacity; ++i)
    {
        if(NULL != table->table[i])
        {
            DLDestroy(table->table[i]);
        }
    }
    free(table);
    table = NULL;
}

int HashInsert(hash_t *table, const void *data)
{
    size_t key = 0;
    dl_iter_t element = NULL;

    assert(table);

    key = table->HashFunc(data) % table->capacity;

    if(NULL == table->table[key])
    {
        table->table[key] = DLCreate(); 
        if(NULL == table->table[key])
        {
            return(FAIL);
        }
    }
    else
    {
        element = DLFind(table->table[key], 
                         DLBegin(table->table[key]), 
                         DLEnd(table->table[key]),
                         table->CompareFunc, (void*)data);

        if(!DLSameIter(element, DLEnd(table->table[key])))
        {
            DLErase(element);
            --table->size;
        }
    }

    if(DLEnd(table->table[key]) == DLPushFront(table->table[key], (void*)data))
    {
        return(FAIL);
    }
    ++table->size;
    return(SUCCESS);
}

void HashRemove(hash_t *table, void *data)
{
    size_t key = 0;
    dl_iter_t element = NULL;

    assert(table);

    key = table->HashFunc(data) % table->capacity;

    if(NULL == table->table[key])
    {
        return; 
    }
    
    element = DLFind(table->table[key], 
                     DLBegin(table->table[key]), 
                     DLEnd(table->table[key]),
                     table->CompareFunc, (void*)data);

    if(DLEnd(table->table[key]) != element)
    {
        DLErase(element);    
        --table->size;
    } 
}

void *HashFind(const hash_t *table, const void *data)
{
    dl_iter_t element = NULL;
    size_t key = 0;

    assert(table);

    key = table->HashFunc(data) % table->capacity;

    if(NULL == table->table[key])
    {
        return (NULL);
    }
    
    element = DLFind(table->table[key], 
                     DLBegin(table->table[key]), 
                     DLEnd(table->table[key]),
                     table->CompareFunc, (void*)data);
    
    if(DLEnd(table->table[key]) == element)
    {
        return(NULL);
    }

    return(DLGetData(element));
}

size_t HashSize(const hash_t *table)
{
    assert(table);

    return(table->size);
}

int HashForEach(hash_t *table, action_func_t ActFunc, void *param)
{
    size_t i = 0;
    for(i = 0; i < table->capacity; ++i)
    {
        if(NULL != table->table[i])
        {
            if(DLForEach(DLBegin(table->table[i]), DLEnd(table->table[i]),
                            ActFunc , param))
            {
                return(FAIL);
            }
        }
    }
    return(SUCCESS);
}
/*----------------------------------------------------------------------------*/

static void FillHash(dll_t *table[1], size_t capacity)
{
    size_t i = 0;
    for(i = 0; i < capacity; ++i)
    {
        table[i] = NULL;
    }
}