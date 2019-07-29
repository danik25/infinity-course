#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <unistd.h> /* sleep */
#include <semaphore.h> /* semaphore */

#include "dani_utilities.h"


#define SIZE 100

sem_t counter;
size_t sum_of_dividors = 0;

size_t numbers_array[SIZE] = {0};

static void *InsertI(void* i);

int main()
{
    size_t i = 0;
    int status = 0;
    pthread_t thread[SIZE];
    int index[SIZE] = {0};
    pthread_attr_t kill;
    pthread_attr_init(&kill);
    pthread_attr_setdetachstate (&kill, PTHREAD_CREATE_DETACHED);

    sem_init (&counter, 0, 0);

    for(i = 0; i < SIZE; ++i)
    { 
        index[i] = i;
        while(pthread_create(&thread[i], &kill, InsertI, &index[i]))
        {
            ;
        }
    }

    for(i = 0; i < SIZE; ++i)
    {
        sem_wait (&counter);
    }
  
    for(i = 0; i < SIZE; ++i)
    {
        /*printf("%ld ", numbers_array[i]);*/
        if(numbers_array[i] != i + 1)
        {
            status = 1;
        }
    }
    printf("\n");
    TEST(!status);
    
    pthread_attr_destroy(&kill);
    return(0);
}

static void *InsertI(void* i)
{
    printf("%ld \n", pthread_self());
    numbers_array[*(int*)i] = *(int*)i + 1;
    sem_post (&counter);
    return(NULL);
}

