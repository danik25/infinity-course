#ifndef _TASK_H_
#define _TASK_H_

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

#include "uid.h" /* UID_t */
             

typedef struct task task_t;
typedef int (task_function_t)(void *param);


/* Description: creates a task.
 *
 * Params: 
 *         param - the parameter of the act_func decided by user.
 *         interval - task schduled frequency.
 *         act_func - user function to be executed. 
 *                                      returns: 0 - success (and run again)
 *                                               1 - end (don't run again)
 *                                              -1 - fail (and don't run again)
 * Return Value: pointer to the new task.
 *         
*/
task_t *TaskCreate(task_function_t act_func, void *param, size_t interval);
                                                        



/* Description: destroys the task. frees all allocated memory.
 *
 * Params: task - task to destroy.
 *        
 *         
*/
void TaskDestroy(task_t *task);


/* Description: execute a task.
 *
 * Params: task - task to execute.
 *        
 * Return Value: status of the function that was activated.
 *         
*/
int TaskRun(task_t *task);


/* Description: updates the time stamp of the task.
 *
 * Params: task - the task to update.
 *        
 *         
*/
void TaskTimeUpdate(task_t *task);


/* Description: gets the time stamp of the task.
 *
 * Params: task - the task to take the time from.
 *        
 * Return Value: the time stamp of the task.
 *         
*/
time_t TaskGetTimeToRun(task_t *task);



/* Description: gets the UID of the task.
 *
 * Params: task - the task to take the time from.
 *        
 * Return Value: the UID of the task.
 *         
*/
UID_t TaskGetUID(task_t *task);

#endif /* _TASK_H_ */