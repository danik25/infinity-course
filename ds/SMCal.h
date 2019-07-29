#ifndef  _SMCAL_H_
#define  _SMCAL_H_


/****************************************************************
*                         calculator- state machine
*                       ==============================
* File Name: SMCal.h
* Related files: SMCal.c, SMCal_test.c
* #Version: V 1.1
* Writer: Dani Benjamin                         
* Reviewer: Ofer Tauber 
* Last update: 23/05/19
****************************************************************/

/* API Design:
 * A calculator that allows the following operators: addition, subtraction, 
 * multiplication, division, when accepting the Mathematical expression as a string.
 * If an incorrect value is inserted, the calculator throws an error.
 * the calculator is designed as state machine, that is  is a mathematical 
 * model of computation, an abstract machine that can be in exactly one of a 
 * finite number of states at any given time.
 * 
 *
 */

typedef struct calculator
{
    char message[100];
    double answer;
}cal_t;



 /* 
 *
 * A calculator that accepts numbers and operators and returns their 
 * mathematical value. If another char is entered, the calculator throws an error. 
 * The calculator is capable of dealing with spaces.
 *
 *
 */

cal_t* SMCalculator(char * exp);





#endif /* _SMCAL_H_  */