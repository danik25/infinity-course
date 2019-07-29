/****************************************************************
*                <<<<<<<< watch_dog >>>>>>>>         
* Related files: watch_dog.h, watch_dog_test.c
* File Name: watch_dog.c                       
* #Version: V 1.1                                                 
* Writer: Dani Benjamin                                                      
* Reviewer: Moshe Greenberg                                                    
* Last update: 14/07/19                                         
****************************************************************/

#define _DEFAULT_SOURCE
#include <stdlib.h> /* getenv, setenv */
#include <unistd.h> /* execvp, sleep */
#include <pthread.h> /* pthread_create */
#include <stdio.h> /* printf */
#include <sys/types.h> /* pid_t */
#include <semaphore.h> /* semaphores */
#include <sys/stat.h> /* sem_wait */
#include <fcntl.h> /* sem_open */
#include <signal.h> /* SIGUSR2 */

#include "watch_dog.h"
#include "dani_utilities.h" 

#define ENV_VAR "watch_dog_env"
#define EXEC_NAME "./watch_dog_proc.out"

#define SEM_NAME1 "/wd_sem1"
#define SEM_NAME2 "/wd_sem2"
#define SEM_PERMS 0666
#define INIT_VAL 0
#define SEM_FAIL -1

int LifeCheck(pid_t pid, char* name, char *const *args, int *status);
static void* life_check_wrapper(void * param);
static int Sync(sem_t *semaphore1, sem_t * semaphore2);
static void HandleAssignment(pid_t pid, char *const *client_args, int *staus);

typedef struct life_checker_vars
{
    pid_t pid;
    char *const *args;
    char *other_proc_name;
    int *status;
}life_checker_vars_t;

/* global variables */
life_checker_vars_t handle = {0};
pthread_t life_check_thread;

int KeepMeAlive(char *const client_args[])
{
    pid_t pid = 0;
    int status = SUCCESS;

    sem_t *semaphore1 = sem_open(SEM_NAME1, O_CREAT, SEM_PERMS, INIT_VAL);
    sem_t *semaphore2 = sem_open(SEM_NAME2, O_CREAT, SEM_PERMS, INIT_VAL);

    if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED) 
    {
        return(FAIL);
    }

    /* when the watchdog is created for the first time, an envronment variable is created, so if it isn't NULL,
    				the "fork" is not necessary */ 
    if(NULL == getenv(ENV_VAR))
    {
        pid = fork();
        setenv(ENV_VAR, "1", 1);

        if(pid < 0)
        {
            return(FAIL);
        }

        if(0 == pid)
        {
            execvp(EXEC_NAME, client_args);
            return(FAIL);
        }
    }
    else
    {
        pid = getppid();
    }

    /* handle assignment */
    HandleAssignment(pid, client_args, &status);

    while(SUCCESS != pthread_create (&life_check_thread, NULL, life_check_wrapper, &handle))

    /* "status" is an argument sent to the "life checker", 
    		to determine if the creation of the sceduler succeeded */
    if(FAIL == Sync(semaphore1, semaphore2) || FAIL == status)
    {
    	return(FAIL);
    }

    if (SUCCESS != sem_close(semaphore1))
    {
    	return(FAIL);
    }
    
    if (SUCCESS != sem_close(semaphore2))
    {
    	return(FAIL);
    }

    return(SUCCESS);
}

void LetMeDie()
{
    /* update the counter for ensuring that the process will not try to 
                                                        revive the other one */
    raise(SIGUSR1);

	kill(handle.pid, SIGUSR2);
	raise(SIGUSR2);

    pthread_join(life_check_thread, NULL);
    unsetenv(ENV_VAR);
}

/*====================================================================================*/

static void* life_check_wrapper(void * param)
{
    life_checker_vars_t *handle = param;
    LifeCheck(handle->pid, handle->other_proc_name, 
                            handle->args, handle->status);
    
    return(NULL);
}

static int Sync(sem_t *semaphore1, sem_t * semaphore2)
{
	if(SEM_FAIL == sem_wait(semaphore1))
    {
    	return (FAIL);
    }
    if(SEM_FAIL == sem_wait(semaphore1))
    {
    	return (FAIL);
    }
    if(SEM_FAIL == sem_post(semaphore2))
    {
    	return (FAIL);
    }

    if(SEM_FAIL == sem_post(semaphore2))
    {
    	return (FAIL);
    }

    PURPLE("client passed two sem_wait, and is ready\n");

    return(SUCCESS);
}

static void HandleAssignment(pid_t pid, char *const *client_args, int *status)
{
	handle.pid = pid;
    handle.args = client_args;
    handle.other_proc_name = EXEC_NAME;
    handle.status = status;
}