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
#include <stdlib.h> /* atoi */
#include <stdio.h> /* printf */

#include "dani_utilities.h"

enum FLAG {off, on};

sig_atomic_t flag = on;

static void Handle(int sig_number)
{
    UNUSED(sig_number);
    
	sleep(1);
    flag = on;
}


int main(int argc, char *argv[])
{
	struct sigaction sig_handle;
	pid_t pid = atoi(argv[1]);

	UNUSED(argc);

	sigemptyset(&sig_handle.sa_mask);
    sig_handle.sa_handler = Handle;
    sig_handle.sa_flags = 0;

    if (sigaction(SIGUSR1, &sig_handle, NULL) == -1) 
    {
        return(1);
    }

	while(1)
    {
        if(flag)
        {
        	printf("ping\n");
            flag = off;
            kill(pid, SIGUSR2);
        }
    }
	return(0);
}