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
#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "uid.h"   /* UID_t */
#include "task.h" /* task_t */


struct task {
    
    UID_t uid;    
    task_function_t *sched_user_func;
    void *param;
    time_t act_time;
	size_t interval; /* seconds */
};

task_t *TaskCreate(task_function_t act_func, void *param, size_t interval)
{
    task_t *task = (task_t *) malloc(sizeof(task_t));
    assert(act_func);
    if(NULL == task)
    {
        return (NULL);
    }
    task->uid = UIDCreate();
    task->sched_user_func = act_func;
    task->param = param;
    task->interval = interval;
    task->act_time = 0;
    return (task);
}

void TaskDestroy(task_t *task)
{
    assert(task);
    free(task);
    task = NULL;
}

int TaskRun(task_t *task)
{
    assert(task);
    return((*task->sched_user_func)(task->param));
}

void TaskTimeUpdate(task_t *task)
{
    assert(task);
    task->act_time = time(NULL) + task->interval;
}

time_t TaskGetTimeToRun(task_t *task)
{
    assert(task);
    return(task->act_time);
}

UID_t TaskGetUID(task_t *task)
{
    assert(task);
    return(task->uid);
}
