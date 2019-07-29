/****************************************************************
*                <<<<<<<< watch_dog >>>>>>>>         
* Related files: watch_dog.c, watch_dog_test.c
* File Name: watch_dog_proc.c                       
* #Version: V 1.1                                                 
* Writer: Dani Benjamin                                                      
* Reviewer: Moshe Greenberg                                                    
* Last update: 14/07/19                                         
****************************************************************/

#include <stdio.h> /* printf */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getpid */

#include "dani_utilities.h"

int LifeCheck(pid_t pid, char* name, char *const *args, int *status);

int main(int argc, char *argv[])
{
    int status = 0;
    UNUSED(argc);

    LifeCheck(getppid(), argv[0], argv, &status);
    return(0);
}