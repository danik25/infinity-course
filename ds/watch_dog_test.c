/****************************************************************
*                <<<<<<<< watch_dog >>>>>>>>         
* Related files: watch_dog.h, watch_dog.c
* File Name: watch_dog_test.c                       
* #Version: V 1.1                                                 
* Writer: Dani Benjamin                                                      
* Reviewer: Moshe Greenberg                                                    
* Last update: 14/07/19                                         
****************************************************************/

#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "watch_dog.h"
#include "dani_utilities.h"

int main(int argc, char *argv[])
{
	int i = 0;
    UNUSED(argc);

    /* round 1 */
    KeepMeAlive(argv);
    GREEN("start cleint\n");
    while(i < 5)
    {
    	sleep(2);
        printf("client round number: %d\n", i);
        ++i;
    }
    i = 0;
    LetMeDie();

    /* round 2 */
    KeepMeAlive(argv);
    while(i < 5)
    {
        sleep(2);
        printf("client round number: %d\n", i);
        ++i;
    }
    LetMeDie();
    
    return(0);
}