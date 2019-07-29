/****************************************************************
*                       uid - Mulithread Threaded      
* file: uid_test_MT.c
* Related files: uid_MT.c, uid_MT.h      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Ayala Rosel
* Last update: 04/07/19
****************************************************************/
#include <pthread.h> /* pthread_create */
#include <stdio.h> /*printf*/
#include <time.h>

#include "uid_MT.h"
#include "dani_utilities.h"

#define UID_NUM 1000

typedef struct threads_var
{
    pthread_mutex_t *uid_mutex;
    pthread_cond_t *uid_condition;
    size_t *wait_counter;
    size_t index;
}wait_t;

UID_t uid_array[UID_NUM] = {0};

static void UIDTest();
static void WaitForOthers(wait_t *wait, size_t num);
static void TestUidCorrectness();
static void * ThreadCreate(void *param);

int main()
{
    UIDTest();
    return (0);
}

static void UIDTest()
{
    int i = 0;

    wait_t handles[UID_NUM] = {0};
    pthread_t thread_array[UID_NUM];

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
    size_t counter = 0;

    for(i = 0; i < UID_NUM; ++i)
    {
        handles[i].uid_mutex = &mutex;
        handles[i].uid_condition = &condition;
        handles[i].wait_counter = &counter;
        handles[i].index = i;

        pthread_create(&thread_array[i], NULL, ThreadCreate, &handles[i]);
    } 

    for(i = 0; i < UID_NUM; ++i)
    {
        pthread_join(thread_array[i], NULL);
    }
    
    TestUidCorrectness();
}

static void WaitForOthers(wait_t *wait, size_t num)
{
    pthread_mutex_lock (wait->uid_mutex);

    if(*wait->wait_counter == num - 1)
    {
        *wait->wait_counter = 0;
        pthread_cond_broadcast(wait->uid_condition);
    }
    else
    {
        *wait->wait_counter += 1;
        pthread_cond_wait (wait->uid_condition, wait->uid_mutex);
    }
    pthread_mutex_unlock (wait->uid_mutex);
}

static void TestUidCorrectness()
{
    size_t i = 0, j = 0;
    int status = 0;

    for(i = 0; i < UID_NUM; ++i)
    {
        for(j = i + 1; j < UID_NUM; ++j)
        {
            if(uid_array[i].counter == uid_array[j].counter)
            {
                status = 1;
            }
        }
    }
    TEST(!status);
}

static void * ThreadCreate(void *param)
{
    wait_t *uid = param;
    WaitForOthers(uid, UID_NUM);
    uid_array[uid->index] = UIDCreate();

    return(NULL);
}