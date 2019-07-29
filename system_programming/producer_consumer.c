#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <stdlib.h> /* rand */
#include <semaphore.h> /* semaphore */
#include <string.h> /* strcmp */
#include <signal.h> /* sig_atomic_t */

#include "queue.h"
#include "dani_utilities.h"

enum Flag {OFF, ON};

#define SIZE 5

/* threads macros */
#define CONS_N 5
#define PROD_N 5
#define ARRAY_SIZE 100
/* 1.3 */
#define BUFFER_SIZE 10

/* ex's functions */
static void TwoThreads();
static int ManyThreads();
static int CircularBufferOneMutex();
static int CircularBufferTwoMutex();
static int CircularBufferAtomic();
static int CircularBufferIndexes();

/* two threads functions - 1.1 */
static void * Consume(void * param);
static void * Produce(void * param);

/* many threads functions - 1.2 */
static void * ManyConsumes(void * param);
static void * ManyProduces(void * param);

/* circular buffer functions - 1.3 */
/*1.3a*/
static void * BuffProd(void * param);
static void * BuffCons(void * param);

/*1.3b*/
static void * BuffCons2(void * param);

/*1.3c*/
static void * BuffProdAtomic(void * param);
static void * BuffConsAtomic(void * param);

/*1.3d*/
static void * BuffProdD(void * param);
static void * BuffConsD(void * param);


/* 1.1 */
int array[SIZE];
int flag = 0;

/* 1.2 */
int array_of_values[ARRAY_SIZE] = {0};
size_t index = 0;
sem_t counter;

/****** circular buffer ******/
typedef struct CIRC_BUF
{
    int circ_array[ARRAY_SIZE];
    size_t write_i;
    size_t read_i;
}circ_buf_t;

sem_t min_cnt;
sem_t max_cnt;

pthread_mutex_t mutex2;
sig_atomic_t buff_cnt_write = 0;
sig_atomic_t buff_cnt_read;

int circ_values[ARRAY_SIZE * 3];

/****************************/

/* general */
pthread_mutex_t mutex;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                                /* functions */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int argc, char *argv[])
{
    UNUSED(argc);

    if(NULL == argv[1])
    {
        printf("no input\n");
    }

    else if(0 == strcmp(argv[1], "1.1"))
    {
        YELLOW("two threads:\n");
        TwoThreads();
    }

    else if(0 == strcmp(argv[1], "1.2"))
    {
        YELLOW("\nmany threads:\n");
        ManyThreads();
    }

    else if(0 == strcmp(argv[1], "1.3a"))
    {
        YELLOW("\ncircular buffer: 1 mutex, 2 semaphore\n");
        CircularBufferOneMutex();
    } 

    else if(0 == strcmp(argv[1], "1.3b"))
    {
        YELLOW("\ncircular buffer: 2 mutexes, 2 semaphore\n");
        CircularBufferTwoMutex();
    }

    else if(0 == strcmp(argv[1], "1.3c"))
    {
        YELLOW("\ncircular buffer: 2 atomics, 1 mutex, 1 list\n");
        CircularBufferAtomic();
    }

    else if(0 == strcmp(argv[1], "1.3d"))
    {
        YELLOW("\ncircular buffer: read and write indexes, 2 mutex\n");
        CircularBufferIndexes();
    }

    else
    {
        printf("wrong input\n");
    }
    

    return(0);
}


/*============================ two threads - 1.1 ============================*/

static void TwoThreads()
{
    pthread_t thread_write;
    pthread_t thread_read;

    pthread_create(&thread_write, NULL, Produce, NULL);
    pthread_create(&thread_read, NULL, Consume, NULL);

    pthread_join(thread_write, NULL);
    pthread_join(thread_read, NULL);
}

static void * Consume(void * param)
{
    size_t i = 0;

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
    return(NULL);
}

static void * Produce(void * param)
{
    size_t i = 0;

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
    return(NULL);
}

/*============================ many threads - 1.2 ============================*/

static int ManyThreads()
{
    queue_t *handle = QCreate();
    size_t i = 0;
    pthread_t prod_thread[PROD_N];
    pthread_t cons_thread[CONS_N];

    sem_init (&counter, 0, 0);

    if(NULL == handle)
    {
        return(1);
    }

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_create(&prod_thread[i], NULL, ManyConsumes, handle);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, ManyProduces, handle);
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_join(prod_thread[i], NULL);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    }
    

    pthread_mutex_destroy(&mutex);
    QDestroy(handle);

    return(0);
}

static void * ManyProduces(void * queue)
{
    while(1)
    {
        pthread_mutex_lock (&mutex);
        {
            array_of_values[index] = rand() % 1000;
            printf("produce: %d\n", array_of_values[index]);
            QEnqueue((queue_t*)queue, &array_of_values[index]);
            index = (index > ARRAY_SIZE) ? 0 : index + 1;
            sem_post (&counter);
        }
        pthread_mutex_unlock (&mutex);
    }

    return(NULL);
}

static void * ManyConsumes(void * queue)
{
    void* ans = NULL;
    while(1)
    {
        sem_wait (&counter);
        
        pthread_mutex_lock (&mutex);
        {
            ans = QDequeue((queue_t*)queue);
            if(NULL != ans)
            {
                printf("consumed:%d \n", *(int*)ans);
            }
        }
        pthread_mutex_unlock (&mutex);
        
    }

    return(NULL);
}

/*=========================== circular buffer - 1.3 ==========================*/
/*************************************1.3a*************************************/
static int CircularBufferOneMutex()
{
    size_t i = 0;
    pthread_t prod_thread[PROD_N];
    pthread_t cons_thread[CONS_N];
    circ_buf_t handler = {{0}, 0, 0};

    sem_init (&min_cnt, 0, 0);
    sem_init (&max_cnt, 0, ARRAY_SIZE);
    

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_create(&prod_thread[i], NULL, BuffProd, &handler);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, BuffCons, &handler);
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_join(prod_thread[i], NULL);
    }
    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    } 

    pthread_mutex_destroy(&mutex);

    return(0);
}

static void * BuffProd(void * param)
{
    circ_buf_t* handle = param;
    while(1)
    {
        sem_wait (&max_cnt);

        pthread_mutex_lock (&mutex);
        {
            handle->circ_array[handle->write_i % ARRAY_SIZE] = handle->write_i;

            printf("produce: %d\n", 
                        handle->circ_array[handle->write_i % ARRAY_SIZE]);
            ++handle->write_i;
            handle->write_i %= ARRAY_SIZE;
        }
        pthread_mutex_unlock (&mutex);

        sem_post (&min_cnt);  
    }

    return(NULL);
}

static void * BuffCons(void * param)
{
    circ_buf_t* handle = param;
    while(1)
    {
        sem_wait (&min_cnt);

        pthread_mutex_lock (&mutex);
        {
            printf("#consemued#: %d\n", 
                        handle->circ_array[handle->read_i % ARRAY_SIZE]);
            ++handle->read_i;
            handle->read_i %= ARRAY_SIZE;
        } 
        pthread_mutex_unlock (&mutex);

        sem_post (&max_cnt);
        
    }

    return(NULL);
}

/*************************************1.3b*************************************/

static int CircularBufferTwoMutex()
{
    size_t i = 0;
    pthread_t prod_thread[PROD_N];
    pthread_t cons_thread[CONS_N];
    circ_buf_t handler = {{0}, 0, 0};

    sem_init (&min_cnt, 0, 0);
    sem_init (&max_cnt, 0, ARRAY_SIZE);
    

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 
    if (pthread_mutex_init(&mutex2, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_create(&prod_thread[i], NULL, BuffProd, &handler);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, BuffCons2, &handler);
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_join(prod_thread[i], NULL);
    }
    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    } 

    pthread_mutex_destroy(&mutex);

    return(0);
}

static void * BuffCons2(void * param)
{
    circ_buf_t* handle = param;
    while(1)
    {
        sem_wait (&min_cnt);

        pthread_mutex_lock (&mutex2);
        {
            printf("#consemued#: %d\n", 
                        handle->circ_array[handle->read_i % ARRAY_SIZE]);
            ++handle->read_i;
            handle->read_i %= ARRAY_SIZE;
        }
        pthread_mutex_unlock (&mutex2);

        sem_post (&max_cnt);
        
    }
    return(NULL);
}

/*************************************1.3c*************************************/

static int CircularBufferAtomic()
{
    queue_t *handle = QCreate();
    size_t i = 0;
    pthread_t prod_thread[PROD_N];
    pthread_t cons_thread[CONS_N];

    /* filling the values array */
    for(i = 0; i < ARRAY_SIZE * 3; ++i)
    {
        circ_values[i] = i;
    }

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_create(&prod_thread[i], NULL, BuffProdAtomic, handle);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, BuffConsAtomic, handle);
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_join(prod_thread[i], NULL);
    }
    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    QDestroy(handle);

    return (0);
}

static void * BuffProdAtomic(void * param)
{
    queue_t * atomic_handle = param;
    size_t i = 0;
    while(1)
    {
        pthread_mutex_lock (&mutex);
        {
            if(buff_cnt_write <= BUFFER_SIZE)
            {
                if(QEnqueue(atomic_handle, &circ_values[i]))
                {
                    return(NULL);
                }

                printf("produce: %d\n", circ_values[i]);
                ++buff_cnt_write;
            }        
            
            ++i;
            i %= (ARRAY_SIZE * 3);
        }
        pthread_mutex_unlock (&mutex);
    }

    return(NULL);
}

static void * BuffConsAtomic(void * param)
{
    void * data = NULL;
    queue_t * handle = param;
    size_t i = 0;
    while(1)
    {
        if(!QIsEmpty(handle))
        {
            pthread_mutex_lock (&mutex);
            {
                data = QDequeue(handle);
                if(NULL != data)
                {
                    --buff_cnt_write;
                    printf("#consemued#: %d\n", *(int*)data);            
                }
                ++i;
            }
            pthread_mutex_unlock (&mutex);
        }         
    }
    return(NULL);
}

/*************************************1.3d*************************************/

static int CircularBufferIndexes()
{
    size_t i = 0;
    pthread_t prod_thread[PROD_N];
    pthread_t cons_thread[CONS_N];
    circ_buf_t handler = {{0}, 0, 0};
    

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    } 
    if (pthread_mutex_init(&mutex2, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return (1); 
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_create(&prod_thread[i], NULL, BuffProdD, &handler);
    }

    for(i = 0; i < CONS_N; ++i)
    {
        pthread_create(&cons_thread[i], NULL, BuffConsD, &handler);
    }

    for(i = 0; i < PROD_N; ++i)
    {
        pthread_join(prod_thread[i], NULL);
    }
    for(i = 0; i < CONS_N; ++i)
    {
        pthread_join(cons_thread[i], NULL);
    } 

    pthread_mutex_destroy(&mutex);

    return(0);
}

static void * BuffProdD(void * param)
{
    circ_buf_t* handle = param;
    while(1)
    {
        pthread_mutex_lock (&mutex);
        if(handle->write_i - handle->read_i < ARRAY_SIZE - 1)  
        {
            handle->circ_array[handle->write_i % ARRAY_SIZE] = 
                            (handle->write_i % ARRAY_SIZE);

            printf("produce: %d\n", 
                            handle->circ_array[handle->write_i % ARRAY_SIZE]);
            ++handle->write_i;
        }
        pthread_mutex_unlock (&mutex); 
    }

    return(NULL);
}

static void * BuffConsD(void * param)
{
    circ_buf_t* handle = param;
    while(1)
    {
        pthread_mutex_lock (&mutex2);
        if(handle->read_i < handle->write_i)
        {
            printf("#consemued#: %d\n", 
                    handle->circ_array[handle->read_i % ARRAY_SIZE]);
            ++handle->read_i;

        }        
        pthread_mutex_unlock (&mutex2);
        
    }
    return(NULL);
}
