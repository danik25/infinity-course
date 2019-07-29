#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <stdlib.h> /* malloc */

#include "dani_utilities.h"

#define SIZE 10

size_t sum_of_dividors = 0;

typedef struct DIVIDORS
{
    size_t number;
    size_t start;
    size_t end;
}dividors_t;

pthread_mutex_t mutex;


static void *SumDivisors(void* handler);

int main()
{
    size_t num = 2000000000;

    size_t i = 0;
    pthread_t thread[SIZE + 1] = {0};
    dividors_t *handler = (dividors_t*)malloc(sizeof(dividors_t) * (SIZE + 1)) ;
    size_t block_size = num / SIZE;

    if(NULL == handler)
    {
        return(1);
    }

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 
    
    for(i = 0; i < SIZE; ++i)
    { 
        handler[i].number = num;
        handler[i].start = i * block_size + 1;
        handler[i].end = (i + 1) * block_size;

        while(pthread_create(&thread[i], NULL, SumDivisors, &handler[i]))
        {
            ;
        }
    }

    handler[i].number = num;
    handler[i].start = i * block_size + 1;
    handler[i].end = num;

    while(pthread_create(&thread[i], NULL, SumDivisors, &handler[i]))
    {
        ;
    }

    for(i = 0; i < SIZE + 1; ++i)
    {
        pthread_join (thread[i], NULL);
    }

    

    printf("thread: %lu\n", sum_of_dividors);
    free(handler);
    pthread_mutex_destroy(&mutex);


    
    return(0);
}


static void *SumDivisors(void* handler)
{
    size_t i = 0;
    
    for(i = ((dividors_t*)handler)->start; i <= ((dividors_t*)handler)->end; ++i)
    {
        if(((dividors_t*)handler)->number % i == 0)
        {
            pthread_mutex_lock (&mutex);
            sum_of_dividors += i;
            pthread_mutex_unlock (&mutex);
        }
    }
    return(NULL);
}

