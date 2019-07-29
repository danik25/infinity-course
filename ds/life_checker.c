/****************************************************************
*                <<<<<<<< watch_dog >>>>>>>>         
* File Name: life_checker.c                       
*                                                 
* Writer: Dani Benjamin                                                      
* Reviewer: Moshe Greenberg                                                    
* Last update: 13/07/19                                         
****************************************************************/ 

#define _POSIX_SOURCE
#define _GNU_SOURCE

#include <sys/types.h> /* pid_t */
#include <unistd.h> /* kill */
#include <stdio.h> /* printf */
#include <stdlib.h> /* sleep */
#include <signal.h> /* sig_atomic_t */
#include <semaphore.h> /* semaphores */
#include <sys/stat.h> /* open */
#include <fcntl.h> /* open */
#include <string.h> /* strcmp */

#include "scheduler.h" /* scheduler */
#include "dani_utilities.h"

#define EXEC_NAME "./watch_dog_proc.out"
#define SEM_NAME1 "/wd_sem1"
#define SEM_NAME2 "/wd_sem2"
#define SEM_FAIL -1
#define SEM_PERMS 0666
#define INIT_VAL 0
#define SIG_ACTION_FAIL -1
#define TRUE 1

enum FLAG {OFF, ON};
int flag = ON;
sched_t *new_sched = NULL;

sig_atomic_t counter = 0;

typedef struct send_signal_params
{
    pid_t pid;
    char* name_of_signaled;
    char *const *args;
    sem_t *semaphore1;
    sem_t *semaphore2;
}signal_params_t;

/* tasks */
int SendSiganl(void *param);
int LivelinessCheck(void *param);

/* assistance functions */
static int SignalAssignment();
static void HandleAssignment(signal_params_t *handle, pid_t pid, char* name, 
                         char *const *args, sem_t *semaphore1, sem_t *semaphore2);
static int SyncProcNClient(sem_t *semaphore1, sem_t * semaphore2);
static int ReSyncProcs(char* other_proc_name, sem_t *semaphore1, sem_t * semaphore2);
static int SchedulerSetup(signal_params_t *handle, int *status);


/*================================= handlers =================================*/
static void HandleSig1(int sig_num)
{
    UNUSED(sig_num);
    
    counter = 0;    
}

static void HandleSig2(int sig_num)
{
    UNUSED(sig_num);
    YELLOW("watch dog stopped\n");
    flag = OFF;    
    SCHStop(new_sched);
}

/*============================== API functions ===============================*/

int LifeCheck(pid_t pid, char* name, char *const *args, int *status)
{
    signal_params_t handle;

    sem_t *semaphore1 = sem_open(SEM_NAME1, O_CREAT, SEM_PERMS, INIT_VAL);
    sem_t *semaphore2 = sem_open(SEM_NAME2, O_CREAT, SEM_PERMS, INIT_VAL);

    if (semaphore1 == SEM_FAILED || semaphore2 == SEM_FAILED) 
    {
        return(FAIL);
    }

    if(FAIL == SignalAssignment())
    {
        return(FAIL);
    }


    HandleAssignment(&handle, pid, name, args, semaphore1, semaphore2);

    if(FAIL == SchedulerSetup(&handle, status))
    {
    	return(FAIL);
    }

    if(FAIL == SyncProcNClient(semaphore1, semaphore2))
    {
    	return(FAIL);
    }

    CYAN("starting signaling\n");
    while(ON == flag)
    {
        SCHRun(new_sched);
    }

   	SCHDestroy(new_sched);
    flag = ON;
   	
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

/*****************************assignmant functions*****************************/

static int SchedulerSetup(signal_params_t *handle, int *status)
{
	int signal_interval = 2;
    int check_interval = 2;

	/* scheduler creation */
    new_sched = SCHCreate();

    /* if the creation of the schedular fails, the watch dog returns fail as well */
    if(NULL == new_sched)
    {
    	*status = FAIL;
    	return(FAIL);
    }
    if (TRUE == UIDIsBad(SCHAdd(new_sched, SendSiganl, handle, signal_interval)))
    {
    	return(FAIL);
    }
    if (TRUE == UIDIsBad(SCHAdd(new_sched, LivelinessCheck, handle, check_interval)))
    {
    	return(FAIL);
    }
}

static int SignalAssignment()
{
    struct sigaction signal_acceptance = {0};
    struct sigaction end_signal = {0};

    sigemptyset(&signal_acceptance.sa_mask);
    sigfillset(&end_signal.sa_mask);

    signal_acceptance.sa_handler = HandleSig1;
    end_signal.sa_handler = HandleSig2;

    signal_acceptance.sa_flags = 0;
    end_signal.sa_flags = 0;

    if (SIG_ACTION_FAIL == sigaction(SIGUSR1, &signal_acceptance, NULL)) 
    {
        return(FAIL);
    }

    if (SIG_ACTION_FAIL == sigaction(SIGUSR2, &end_signal, NULL)) 
    {
        return(FAIL);
    }

    return(SUCCESS);
}

static void HandleAssignment(signal_params_t *handle, pid_t pid, char* name, 
                        char *const *args, sem_t *semaphore1, sem_t *semaphore2)
{
    handle->pid = pid;
    handle->name_of_signaled = name;
    handle->args = args;
    handle->semaphore1 = semaphore1;
    handle->semaphore2 = semaphore2;
}

/******************************************************************************/
/*										tasks                             	  */
/******************************************************************************/

int SendSiganl(void *param)
{
    signal_params_t *handle = param;
    printf("i am: %d, sending siganl to: %s, to pid: %d\n",getpid(), 
                                handle->name_of_signaled, handle->pid);
    kill(handle->pid, SIGUSR1);
    
    return (0);
}

int LivelinessCheck(void *param)
{
    signal_params_t *handle = param;
    ++counter;
    pid_t pid = 0;

    if(counter > 4)
    {
        counter = 0;
        /* TODO: debugging */
        printf("%s is rebooting, pid: %d, from: %d\n", 
                            handle->name_of_signaled, handle->pid, getpid());

        pid = fork();

        if(pid < 0)
        {
            return(FAIL);
        }

        if(0 == pid)
        {
            execvp(handle->name_of_signaled, handle->args);
            return(FAIL);
        }
        handle->pid = pid;
        
        SCHStop(new_sched);
        
        if(FAIL == ReSyncProcs(handle->name_of_signaled, handle->semaphore1, 
        												handle->semaphore2))
        {
        	return(FAIL);
        }
    }

    return (SUCCESS);
}

/******************************************************************************/

static int SyncProcNClient(sem_t *semaphore1, sem_t *semaphore2)
{
	if(SEM_FAIL == sem_post(semaphore1))
    {
    	return (FAIL);
    }
    if(SEM_FAIL == sem_wait(semaphore2))
    {
    		return (FAIL);
    }

    return (SUCCESS);
    	
}
static int ReSyncProcs(char* other_proc_name, sem_t *semaphore1, sem_t * semaphore2)
{
	/* if the rebooting proc is the watch dog */
	if(0 == strcmp(EXEC_NAME, other_proc_name))
	{
		PURPLE("syncronizing the watch dog\n");
		if(SEM_FAIL == sem_wait(semaphore1))
	    {
	    	return (FAIL);
	    }
	    if(SEM_FAIL == sem_post(semaphore2))
	    {
	    	return (FAIL);
	    }
	}
	/* if the rebooting proc is the client */
	else
	{
		PURPLE("syncronizing the client\n");
		if(SEM_FAIL == sem_post(semaphore1))
	    {
	    	return (FAIL);
	    }
	    if(SEM_FAIL == sem_wait(semaphore2))
	    {
	    	return (FAIL);
	    }
	}

	return(SUCCESS);
}

