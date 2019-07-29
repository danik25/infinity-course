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

sig_atomic_t flag = on;

static void Handle(int sig_number)
{
    UNUSED(sig_number);

    sleep(1);
    flag = on;
}

int main()
{
    struct sigaction sig_handle;

    sigemptyset(&sig_handle.sa_mask);
    sig_handle.sa_handler = Handle;
    sig_handle.sa_flags = 0;

    if (sigaction(SIGUSR2, &sig_handle, NULL) == -1) 
    {
        return(1);
    }

    while(1)
    {
        if(flag)
        {
            printf("pong - EX3\n");
            flag = off;
            kill(getppid(), SIGUSR1);
        }
    }
    return(0);
}