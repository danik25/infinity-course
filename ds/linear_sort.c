/*******************************************************************************
*                Data Structures - Linear Sorting   
* file name: linear_sort.c                                             
* Related files: linear_test.c linear_sort.c                               
* #Version: V 2.1                                                  
* writer: Dani Benjamin                                                         
* reviewer: Lev Shubert                                                     
* last update: 14.5.2019                                               
*******************************************************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include "linear_sort.h"

#define UNUSED(x) (void)(x)
static size_t Key(const void *key, const void *arg);

typedef struct assistance_struct
{
    size_t index;
    key_to_num_t user_func;
    const void* user_arg;
}assistance_struct_t;

int CountingSort(void *arr, size_t len, size_t element_size,
                 key_to_num_t KeyToNum, const void *arg, size_t range)
{
    size_t *index = NULL;
    char * tmp = NULL;
    char * runner = NULL;
    size_t i = 0;

    assert(arr);
    assert(KeyToNum);

    runner = arr;
    index = (size_t*)calloc(range, sizeof(size_t));

    if(NULL == index)
    {
        return (1);
    }

    tmp = (char*)malloc(len * element_size);

    if(NULL == tmp)
    {
        free(index);
        index = NULL;
        return (1);
    }

    /* filling the index lut */
    for(i = 0; i < len; ++i, runner += element_size)
    {
        *(index + KeyToNum(runner, arg)) += 1;
    }

    /* adjusting the index lut */
    i = 1;
    for(i = 1; i < range; ++i)
    {
        *(index + i) = *(index + i) + *(index + i - 1);
    }

    /* filling the temporary array */
    i = 0;
    runner = (char*)arr + (len - 1) * element_size;
    for(i = 0; i < len; ++i, runner -= element_size)
    {
        memcpy(tmp + (index[KeyToNum(runner, arg)] - 1) * element_size, 
                                                runner, element_size);
        index[KeyToNum(runner, arg)] -= 1;
    }

    memcpy(arr, tmp, len * element_size);

    free(tmp);
    tmp = NULL;
    free(index);
    index = NULL;

    return (0);
}

int RadixSort(void *arr, size_t len, size_t element_size,
                 key_to_num_t KeyToNum, const void *arg, size_t max_digits_num)
{
    size_t i = 0;
    assistance_struct_t argument = {0 ,0 , 0}; 

    assert(arr);
    assert(KeyToNum);

    argument.index = 0;
    argument.user_func = KeyToNum;
    argument.user_arg = arg;
    
    for(i = 0; i < max_digits_num; ++i)
    {
        if(1 == CountingSort(arr, len, element_size, Key, &argument, 10))
        {
            return(1);
        }
        ++argument.index;     
    }    
    return(0);
}

static size_t Key(const void *key, const void *arg)
{
    assistance_struct_t *func_struct = NULL;
    size_t num = 0;
    size_t i = 0;

    assert(key);
    assert(arg);

    func_struct = (assistance_struct_t *)arg;
    num = func_struct->user_func(key, func_struct->user_arg);

    for(i = 0; i < func_struct->index; ++i)
    {
        num /= 10;
    }

    return((size_t)((num%10)));
}