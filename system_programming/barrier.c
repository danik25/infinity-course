#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* semaphore */
#include <assert.h> /* assert */

#include "dani_utilities.h"

static int Barrier();

void* BarProducer(void* param);
void* BarConsumer(void* param);

#define SUM_OF_MESSAGES 5
#define CONS_N 6

enum Flag {OFF, ON};

int information[SUM_OF_MESSAGES] = {0};
int results[CONS_N][SUM_OF_MESSAGES] = {0};

size_t inf_index = 0;

int buffer[1] = {0};

sem_t bar_sem;
pthread_mutex_t bar_mutex;
pthread_cond_t bar_condition;

int consumption_flag = ON;

int main()
{
    Barrier();
    return(0);
}

static int Barrier()
{
    pthread_t prod_thread;
    pthread_t cons_thread[CONS_N];
    size_t i = 0;

    /* initialization of mutex, semaphore and conditional variable */
    sem_init (&bar_sem, 0, 0);

    if (pthread_mutex_init(&bar_mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    }

    pthread_cond_init (&bar_condition, NULL);

    /* initializing the messages array*/
    for(i = 0; i < SUM_OF_MESSAGES; ++i)
    {
        information[i] = i;
    }

    pthread_create(&prod_thread, NULL, BarProducer, NULL);

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, BarConsumer, NULL);
    }

    pthread_join(prod_thread, NULL);
    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    }

    pthread_mutex_destroy(&bar_mutex);
    return(0);
}

void* BarProducer(void* param)
{
    size_t i = 0;
    
    UNUSED(param);

    while(inf_index < SUM_OF_MESSAGES)
    {
        for(i = 0; i < CONS_N; ++i)
        {
            sem_wait(&bar_sem);
        }

        printf("\nmessage number: %ld\n", inf_index + 1);

        /* generating the message */
        buffer[0] = information[inf_index];
        ++inf_index;

        pthread_mutex_lock (&bar_mutex);
        {
            pthread_cond_broadcast (&bar_condition);
        } 
        pthread_mutex_unlock (&bar_mutex);
    }

    consumption_flag = OFF;

    return(NULL);
}

void* BarConsumer(void* param)
{
    size_t local_index = 0;

    UNUSED(param);

    while (ON == consumption_flag)
    {
        pthread_mutex_lock (&bar_mutex);
        {
            sem_post(&bar_sem);
            while(local_index == inf_index)
            {
                pthread_cond_wait (&bar_condition, &bar_mutex);
            }
            
            printf("thread ID: %lu, information: %d\n", pthread_self(), buffer[0]);
            ++local_index;
        }
         
        pthread_mutex_unlock (&bar_mutex);
    }

    return(NULL);
}