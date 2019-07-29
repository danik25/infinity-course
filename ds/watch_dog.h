#ifndef __WATCH_DOG_H__                                                                                                                                                        
#define __WATCH_DOG_H__   


/****************************************************************
*                <<<<<<<< watch_dog >>>>>>>>         
* Related files: watch_dog.c, watch_dog_test.c
* File Name: watch_dog.h                       
* #Version: V 1.1                                                 
* Writer: Dani Benjamin                                                      
* Reviewer: Moshe Greenberg                                                    
* Last update: 14/07/19                                         
****************************************************************/ 
/* API DESCRIPTION:
 *                   
 *  This program is designed to initiate a watchdog, at a client's
 *  program request. once watchdog is initiated, it will restart
 *  client's program upon crashing.
 *  this guard will be up from KeepMeAlive call to LetMeDie, which
 *  will terminate the watchdog.
 *               
 *
 *
 *
 *
 *
 *
*/  



/* Description: Initiate watchdog to gard a critical section.
 *
 * Params: client_args - command line arguments, for restarting client program.
 *        
 * Return Value:  exit status - SUCCESS (0) or FAIL (1)
 *         
*/
int KeepMeAlive(char *const client_args[]);


/* Description: Destroy watchdog and release resources.
 *
*/
void LetMeDie(void);


#endif /* _watch_dog_H_ */
