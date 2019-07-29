/****************************************************************
*                <<<<<<<< ping pong >>>>>>>>                    *                        *
*                                                               *
* Writer: Dani Benjamim                                         *   
* Reviewer: Tom Valershtein                                     *
* Last update: 07/07/19                                         *
****************************************************************/
#define _GNU_SOURCE

#include <signal.h> /* sigaction */
#include <unistd.h> /* STDOUT_FILENO */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "dani_utilities.h"

enum FLAG {off, on};

sig_atomic_t flag = off;

int signal_pid = -1;

static void HandleSignal(int sig, siginfo_t *info, void *context)
{
    UNUSED(sig);
    UNUSED(context);

    sleep(1);
    signal_pid = info->si_pid;
    flag = on;
}

int main()
{
    struct sigaction signal_sender;

    signal_sender.sa_flags = SA_SIGINFO;
    signal_sender.sa_sigaction = HandleSignal;

    printf("pid: %d\n", getpid());

    if (sigaction(SIGUSR2, &signal_sender, NULL) == -1) 
    {
        return(1);
    }

	while(1)
    {
        if(flag)
        {
        	printf("pong\n");
            flag = off;
            kill(signal_pid, SIGUSR1);
        }
    }
	return(0);
}
