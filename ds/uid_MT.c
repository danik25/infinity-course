/****************************************************************
*                       uid - Mulithread Threaded      
* file: uid_MT.c
* Related files: uid_test_MT.c, uid_MT.h      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Ayala Rosel
* Last update: 04/07/19
****************************************************************/
#include <pthread.h> /* pthread_create */
#include "uid_MT.h"

size_t cnt = 0;
UID_t g_bad_uid = {0, {0}, 0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


UID_t UIDCreate()
{
    UID_t new_uid = {0, {0}, 0};
    new_uid.pid = getpid();
    gettimeofday(&new_uid.time, NULL);

    pthread_mutex_lock(&mutex);
    new_uid.counter = ++cnt;
    pthread_mutex_unlock(&mutex);

    return (new_uid);
}

int UIDIsSame(UID_t uid1, UID_t uid2)
{
    return(uid1.pid == uid2.pid && uid1.time.tv_sec == uid2.time.tv_sec
                    && uid1.time.tv_usec == uid2.time.tv_usec 
                    && uid1.counter == uid2.counter);
}

int UIDIsBad(UID_t uid)
{
    
    return(UIDIsSame(g_bad_uid, uid));
}

