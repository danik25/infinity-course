#ifndef  _SCHEDULER_H_
#define  _SCHEDULER_H_


/****************************************************************
*                   Scheduler                                   *
* Related files: scheduler.c, scheduler_test.c scheduler.h      *
*                task.c, task.h uid.h, uid.c                    *
* #Version: V 1.3                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Moshe Greenberg                                     *
* Last update: 21/04/19                                         *
****************************************************************/
/* API DESCRIPTION
 *
 * Scheduler is a program that schedules tasks and executes them at a time set
 * by the user.
 *
 *
*/  

/* API Design:
 *          This product was designed to contain and execute multiple tasks, 
 *          timed by user specifications. the product creates, schedule, and
 *          executes tasks. 
 *
 *  */                

#include <stddef.h> /* size_t */

#include "uid.h" /* UID_t */
#include "task.h" /* task_t */


typedef struct sched sched_t;



/* Description: Creates a scheduler container.
 *
 *        
 * Return Value: 
 *         pointer to the created scheduler.
*/
sched_t *SCHCreate(void);


/* Description: Destroys a scheduler container.
 *
 * Params: sched - pointer to the to be destroyed scheduler.
 *           
 * Return Value: none.
 *         
*/
void SCHDestroy(sched_t *sched);


/* Description: add a new task to the scheduler (by it's time).
 *
 * Params: sched - scheduler to insert.
 *         act_func  - user function of the task.
 *         param - optional parameter for the user function.
 *         interval - the interval between two executions of the functions.
 *        
 * Return Value: the UID of the added task.
 *         
*/
UID_t SCHAdd(sched_t *sched, task_function_t act_func, void *param,
                                                          size_t interval);

/* Description: removes a specific task from the schduler by UID.
 *
 * Params: ched - scheduler to remove from.
 *         task_id - task to remove.
 *        
 * Return Value: status - 0 - success, 1 - fail.
 *         
*/
int SCHRemove(sched_t *sched, UID_t task_id);


/* Description: activate the scheduler (execute tasks).
 *
 * Params: sched - the scheduler to activate.
 *    
 * Return Value: status - 0: no tasks left in sheduler.
 *                        1: terminated by flag.
 *                       -1: Error in setup of the run.
*/
int SCHRun(sched_t *sched);


/* Description: raises the stop flag of the scheduler.
 *
 * Params: sched - the scheduler to stop.
 *                 
*/
void SCHStop(sched_t *sched);


/* Description: counts number of tasks in scheduler.
 *
 * Params: sched - the scheduler.
 *        
 * Return Value: number of tasks in scheduler.
 *         
*/
size_t SCHSize(const sched_t *sched);


/* Description: checks whether the scheduler is empty or not.
 *
 * Params:sched - the scheduler.
 *        
 * Return Value: Boolean
 *         
*/
int SCHIsEmpty(const sched_t *sched);


#endif /* _SCHEDULER_H */
