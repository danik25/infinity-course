#include "uid.h"

size_t cnt = 0;
UID_t g_bad_uid = {0, {0}, 0};
/*
UID_t g_bad_uid = UIDCreate();
g_bad_uid.counter += 1;
*/
UID_t UIDCreate()
{
    UID_t new_uid = {0, {0}, 0};
    new_uid.pid = getpid();
    gettimeofday(&new_uid.time, NULL);
    new_uid.counter = ++cnt;

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