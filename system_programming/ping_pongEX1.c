/****************************************************************
*                <<<<<<<< ping pong >>>>>>>>                    *                        *
*                                                               *
* Writer: Dani Benjamim                                         *   
* Reviewer: Tom Valershtein                                     *
* Last update: 07/07/19                                         *
****************************************************************/ 
#define _GNU_SOURCE

#include <stdio.h> /* printf */
#include <sys/types.h>
#include <signal.h> /* sigaction */
#include <unistd.h>

#include "dani_utilities.h"

enum FLAG {off, on};

sig_atomic_t flag = on;

static void PingParent(int sig_number)
{
    UNUSED(sig_number);
    sleep(1);
    flag = off;
}

static void PongChild(int sig_number)
{
    UNUSED(sig_number);
    sleep(1);
    flag = on;
}

int main()
{
    pid_t pid = 0;

    struct sigaction parent = {0};
    struct sigaction child = {0};

    sigemptyset(&parent.sa_mask);
    sigemptyset(&child.sa_mask);

    parent.sa_handler = PingParent;
    child.sa_handler = PongChild;

    parent.sa_flags = 0;
    child.sa_flags = 0;

    if (sigaction(SIGUSR1, &parent, NULL) == -1) 
    {
        return(1);
    }

    if (sigaction(SIGUSR2, &child, NULL) == -1) 
    {
        return(1);
    }

    pid = fork ();
    
    if (pid < 0)
    {
        printf("Can't create child process\n");
        return(1);
    }

    if(pid == 0)
    {
        while(1)
        {
            if(flag)
            {
            	printf("pong\n");
                flag = off;
                kill(getppid(), SIGUSR1);
            }
        }
        
    }
    else if(pid > 0)
    {
        while(1)
        {
            if(!flag)
            {
            	printf("ping\n");
                flag = 1;
                kill(pid, SIGUSR2);
            }
        }
    }
    return(0);
}