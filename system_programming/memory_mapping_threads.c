#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <stdlib.h> /* rand */

#include "dani_utilities.h"

static void * Consume(void * param);
static void * Produce(void * param);
static void TwoThreads();

enum Flag {OFF, ON};
#define SIZE 5

int main()
{
    YELLOW("two threads:\n");
    TwoThreads();
    
    return(0);
}

int array[SIZE];
int flag = 0;

static void TwoThreads()
{
    static int var = 1;
    int local_var = 1;
    size_t *heap_main = (size_t*)malloc(sizeof(size_t));

    pthread_t thread_write;
    pthread_t thread_read;

    ++var;
    pthread_create(&thread_write, NULL, Produce, NULL);
    pthread_create(&thread_read, NULL, Consume, NULL);

    pthread_join(thread_write, NULL);
    pthread_join(thread_read, NULL);
}

static void * Consume(void * param)
{
    size_t i = 0;
    size_t i_consumer = 0;
    static int var_consumer = 5;
    size_t *heap_consumer = (size_t*)malloc(sizeof(size_t));

    UNUSED(param);

    for(i = 0; i < SIZE; ++i)
    {
        while(0 != flag)
        {
            ;
        }
        flag = ON;
        array[i] = i;
    }
    var_consumer = 8;
    heap_consumer = &i_consumer;
    return(NULL);
}

static void * Produce(void * param)
{
    size_t i = 0;
    size_t i_Produce = 0;
    static int var_Produce = 5;
    size_t *heap_Produce = (size_t*)malloc(sizeof(size_t));

    UNUSED(param);

    for(i = 0; i < SIZE; ++i)
    {
        while(0 == flag)
        {
            ;
        }
        flag = OFF;
        printf("%d\n", array[i]);
    }
    var_Produce = 8;
    return(NULL);
}