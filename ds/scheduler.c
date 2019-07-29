/****************************************************************
*                   Scheduler                                   *
* Related files: scheduler.c, scheduler_test.c scheduler.h      *
*                task.c, task.h uid.h, uid.c                    *
* #Version: V 1.3                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Moshe Greenberg                                     *
* Last update: 21/04/19                                         *
****************************************************************/
#include <time.h> /* time_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "scheduler.h"
#include "pq.h" /* pqueue_t */

#define UNUSED(x) (void)(x)

/*compare function*/
int IsBefore(void *data1, void *data2, void *param);
/*compare function*/
int IsMatch(void *data, void* arg);

UID_t g_bad_uid;

struct sched {

    pqueue_t *scheduler;
	int kill_flag; /* flag to stop the run() function. 1 = stop, 0 = run */
};

sched_t * SCHCreate()
{
    sched_t *sched = (sched_t *) malloc(sizeof(sched_t));
    if(!sched)
    {
        return(NULL);
    }
    sched->scheduler = PQCreate(IsBefore, NULL);
    if(!sched->scheduler)
    {
        free(sched);
        return(NULL);
    }
    sched->kill_flag = 0;

    return (sched);
}

void SCHDestroy(sched_t *sched)
{
    assert(sched);
    while(!PQIsEmpty(sched->scheduler))
    {
        TaskDestroy(PQDequeue(sched->scheduler));
    } 
    PQDestroy(sched->scheduler);
    free(sched);
    sched = NULL;
}

UID_t SCHAdd(sched_t *sched, task_function_t act_func, void *param,
                                                          size_t interval)
{
    task_t *task = NULL;

    assert(sched);
    assert(act_func);

    task = TaskCreate(act_func, param, interval);
    if(!task)
    {
        return(g_bad_uid);
    }
    PQEnqueue(sched->scheduler, task);

    return(TaskGetUID(task));
}

int SCHRemove(sched_t *sched, UID_t task_id)
{
    void *removed = NULL;

    assert(sched);

    removed = PQRemove(sched->scheduler, IsMatch, &task_id);

    if(!removed)
    {
        return(1);
    }
    free(removed);
    removed = NULL;
    return(0);
}

int SCHRun(sched_t *sched)
{
    size_t i = 0;
    int status = 0;
    void *tmp_deq = NULL;
    sched->kill_flag = 0;
    for(i = 0; i < SCHSize(sched); ++i)
    {
        TaskTimeUpdate(PQPeek(sched->scheduler));
        tmp_deq = PQDequeue(sched->scheduler);
        PQEnqueue(sched->scheduler, tmp_deq); 
    }
    while(!sched->kill_flag)
    {
        if(SCHIsEmpty(sched))
        {
            return(0);
        }
        sleep(TaskGetTimeToRun(PQPeek(sched->scheduler)) - time(NULL));
        status = TaskRun(PQPeek(sched->scheduler));
        if(status == 1 || status == -1)
        {
            SCHRemove(sched, TaskGetUID(PQPeek(sched->scheduler)));
        }
        else
        {
            TaskTimeUpdate(PQPeek(sched->scheduler));
            tmp_deq = PQDequeue(sched->scheduler);
            PQEnqueue(sched->scheduler, tmp_deq);  
        }
    }
    return (1);
}

void SCHStop(sched_t *sched)
{
    assert(sched);
    sched->kill_flag = 1;
}

size_t SCHSize(const sched_t *sched)
{
    assert(sched);
    return (PQSize(sched->scheduler));
}

int SCHIsEmpty(const sched_t *sched)
{
    assert(sched);
    return(PQIsEmpty(sched->scheduler));
}

/****************************************************************/

/*compare function*/
int IsBefore(void *data1, void *data2, void *param)
{
    UNUSED(param);
    if(TaskGetTimeToRun(data1) < TaskGetTimeToRun(data2))
    {
        return (1);
    }
    return (0);
}

/*compare function*/
int IsMatch(void *data, void* arg)
{
    return (UIDIsSame(TaskGetUID(data), *(UID_t*)arg));
}