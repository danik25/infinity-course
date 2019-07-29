/****************************************************************
*                Counting Sort Multi thread
* file: counting_sort_mt.c
* Related files: counting_sort_mt_test.c, counting_sort_mt.h
* #Version: V 1.0st
* Writer: Dani Benjmain
* Reviewer: Lev Shubert
* Last update: 01/07/19
****************************************************************/
#include <pthread.h> /* pthread_create */
#include <stdio.h> /* stdio.h */
#include <string.h> /* memset */

#include "counting_sort_mt.h"
#include "dani_utilities.h"

#define CHAR_NUM 256
#define THREAD_NUM 4

pthread_mutex_t dict_mutex;
size_t LUT[CHAR_NUM] = {0};

typedef struct DICTIONARY
{
    unsigned char* array;
    size_t block_size;
}dict_t;

static void* FillLut(void* struct_array);

int CountingSortMT(unsigned char *dict, size_t size)
{
    size_t i = 0;
    pthread_t char_thread[THREAD_NUM];
    dict_t struct_array[THREAD_NUM];
    unsigned char *start = dict;

    /* initializing the mutex */
    if (pthread_mutex_init(&dict_mutex, NULL) != 0) 
    {  
        return (1); 
    } 

    /* filling the LUT */ 
    for(i = 0; i < THREAD_NUM - 1; ++i)
    {
        struct_array[i].array = dict + i * (size / THREAD_NUM);
        struct_array[i].block_size = size / THREAD_NUM;
        pthread_create(&char_thread[i], NULL, FillLut, &struct_array[i]);
    }

    struct_array[i].array = dict + i * (size / THREAD_NUM);
    struct_array[i].block_size = size / THREAD_NUM + size % THREAD_NUM;
    pthread_create(&char_thread[i], NULL, FillLut, &struct_array[i]);

    for(i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(char_thread[i], NULL);
    }             

    for(i = 0; i < CHAR_NUM; ++i)
    {
        memset(dict, i, LUT[i]);
        dict += LUT[i];
    }

    #ifdef PRINT
    PURPLE("LUT\n");
    for(i = 0; i < CHAR_NUM; ++i)
    {
        printf("letter %c, number: %ld\n", (unsigned char)i, LUT[i]);
    } 
    dict = start;
    PURPLE("dictionary\n");
    for(i = 0; i < size; ++i)
    {
        putchar(dict[i]);
    }
    #endif

    return(0);
}

static void* FillLut(void* struct_array)
{
    dict_t *handle = struct_array;
    size_t local_lut[CHAR_NUM] = {0};
    size_t i = 0;

    for(i = 0; i < handle->block_size; ++i)
    {
        ++local_lut[handle->array[i]];
    }
    
    pthread_mutex_lock (&dict_mutex);
    for(i = 0; i < CHAR_NUM; ++i)
    {
        LUT[i] += local_lut[i];
    }
    pthread_mutex_unlock (&dict_mutex);

    return(NULL);
}
