/****************************************************************
*                   uid - Mulithread Threaded       
* file: uid_MT.h
* Related files: uid_test_MT.c, uid_MT.c      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Ayala Rosel
* Last update: 04/07/19
****************************************************************/

#ifndef _UID_
#define _UID_

#include <sys/types.h> /*pid_t*/
#include <sys/time.h> /*time_val*/
#include <unistd.h> /*getpid*/

typedef struct uid
{
    pid_t pid;
    struct timeval time;
    size_t counter;
}UID_t;

extern UID_t g_bad_uid;

/*creation of a new unique ID*/
UID_t UIDCreate();

/*checks whether two UIDs are the same*/
int UIDIsSame(UID_t uid1, UID_t uid2);

/*checks whether the UID is useable*/
int UIDIsBad(UID_t uid);

#endif /* _UID_ */