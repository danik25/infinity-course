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

sig_atomic_t flag = off;

static void Handle(int sig_number)
{
    UNUSED(sig_number);

    sleep(1);
    flag = on;
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    struct sigaction sig_handle;

    sigemptyset(&sig_handle.sa_mask);
    sig_handle.sa_handler = Handle;
    sig_handle.sa_flags = 0;

    UNUSED(argc);

    if (sigaction(SIGUSR1, &sig_handle, NULL) == -1) 
    {
        return(1);
    }

    pid = fork();

    if (pid == 0) 
    {
        execvp(argv[1], &argv[1]);
    }
    else
    {
        while(1)
        {
            if(flag)
            {
                printf("ping - EX3\n");
                flag = off;
                kill(pid, SIGUSR2);
            }
        }
    }
    
    return(0);
}