/****************************************************************
*                         calculator- state machine
*                       ==============================
* File Name: SMCal.c
* Related files: SMCal.h, SMCal_test.c
* #Version: V 1.1
* Writer: Dani Benjamin                         
* Reviewer: Ofer Tauber 
* Last update: 23/05/19
****************************************************************/

#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <ctype.h> /* isspace */ 
#include <math.h> /* pow */ 
#include "SMCal.h"
#include "stack.h"

#define STOP 4
#define UNUSED(x) (void)(x)

/*
START- begining
PN- proccess number
PO- proccess operand
WS- white space
*/

enum states {START, PN, PO, WS, STATES_SIZE};
enum events {END, OPERAND, DIGIT, SPACE, OTHER, EVENTS_SIZE};

typedef int (*action_func)(stack_t * stack_num, 
                        stack_t * stack_op,
                        cal_t * ans_handle,
                        const char input,
                        int state);

/* assisting functions */
static int IsOperation(char ch);
static int IsNumber(char ch);
static int Priority(char ch);
static double CurrentCalculation(double num1, double num2, char op);

/* events */
static int ConverToDigit(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state);
static int OperatorProc(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state);
static int Calculate(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state);
static int ErrorMessage(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state);
static int WSProc(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state);

cal_t* SMCalculator(char * exp)
{
    static cal_t ans_handle = {"", 0};
    int state = 0;
    int LUT[256] = {0};
    int i = 0;

    /* stacks */
    stack_t *stack_num = NULL;
    stack_t *stack_op = NULL;

    /*
        _|______|_______0_____|_______1_______|_______2_____|_______3_____|_______4_____  
         |      |  END('\0')  |   OPERAND     |    DIGIT    | SPACE (' ') |     OTHER
      ___|_____ |_____________|_______________|_____________|_____________|_____________
       0 |START | calculate   | ErrorMessage  |ConverToDigit| WSProc      |ErrorMessage
         |      | s->finish   |               | s->PN       |s->start     |
      ___|______|_____________|_______________|_____________|_____________|_____________
       1 | PN   | calculate   | OperatorProc  |ConverToDigit| WSProc      |ErrorMessage
         |      | s->finish   | s->PO         | s->PN       |s->WS        |
      ___|______|_____________|_______________|_____________|_____________|_____________
       2 | PO   | ErrorMessage| ErrorMessage  |ConverToDigit| WSProc      |ErrorMessage
         |      |             |               |s->PN        | s->PO       |
      ___|______|_____________|_______________|_____________|_____________|_____________
       3 | WS   | calculate   | OperatorProc  |ErrorMessage | WSProc      |ErrorMessage
         |      | s->finish   | s->PO         |             | s->WS       |

    */

    action_func array[STATES_SIZE][EVENTS_SIZE] = 
    {
        {Calculate, ErrorMessage, ConverToDigit, WSProc, ErrorMessage},
        {Calculate, OperatorProc, ConverToDigit, WSProc, ErrorMessage},
        {ErrorMessage, ErrorMessage, ConverToDigit, WSProc, ErrorMessage},
        {Calculate, OperatorProc, ErrorMessage, WSProc, ErrorMessage}
    };

    assert(exp);

    /* stacks */
    stack_num = StackCreate(sizeof(double), strlen(exp));
    stack_op = StackCreate(sizeof(char), strlen(exp));

    /* struct initialization */
    ans_handle.answer = 0;
    sprintf(ans_handle.message, "empty");

    /* creating lut */
    for (i = 0; i < 256; ++i)
    {
        /* 0 - 9 */
        if(IsNumber(i))
        {
            LUT[i] = DIGIT;
        }
        /* operators */
        else if(IsOperation((char)i))
        {
            LUT[i] = OPERAND;
        }
        /* '\0' */
        else if(i == END)
        {
            LUT[i] = END;
        }

        /* white spaces */
        else if(isspace(i))
        {
            LUT[i] = SPACE;
        }
        else
        {
            LUT[i] = OTHER;
        }
    }

    while(state != STOP)
    {
        state = (*array[state][LUT[(int)*exp]])(stack_num, 
                                           stack_op,
                                           &ans_handle,
                                           *exp,
                                           state);
        ++exp;
    }

    StackDestroy(stack_num);
    StackDestroy(stack_op);

    return(&ans_handle);
}

/************************* static functions ******************************/

static int ConverToDigit(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state)
{
    double num = 0;

    UNUSED(stack_num);
    UNUSED(stack_op);
    UNUSED(ans_handle);

    /* new digit to an exsisting number*/
    if(0 != StackSize(stack_num) && state == PN)
    {
        num = *(double*)StackPeek(stack_num);
        StackPop(stack_num);
    }

    num = num * 10 + (input - '0');
    StackPush(stack_num, &num);

    return (PN);
}

static int OperatorProc(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state)
{
    double num1 = 0;
    double num2 = 0;
    char sign = '0';

    UNUSED(stack_num);
    UNUSED(ans_handle);
    UNUSED(state);

    assert(stack_op);

    while( 0 != StackSize(stack_op) && 
                Priority(input) <= Priority(*(char*)StackPeek(stack_op))) 
                                            
    {
        num1 = *(double*)StackPeek(stack_num);
        StackPop(stack_num);
        num2 = *(double*)StackPeek(stack_num);
        StackPop(stack_num);
        sign = *(char*)StackPeek(stack_op);
        StackPop(stack_op);

        num1 = CurrentCalculation(num2, num1, sign);
        StackPush(stack_num, &num1);
    }

    StackPush(stack_op, &input); 
    return (PO); 
}

static int Calculate(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state)
{
    double num = 0;

    UNUSED(input);
    UNUSED(state);

    assert(stack_num);
    assert(stack_op);
    assert(ans_handle);

    if(state != START)
    {
        num = *(double*)StackPeek(stack_num);
        StackPop(stack_num);

        while(0 != StackSize(stack_num))
        {
            num = CurrentCalculation(*(double*)StackPeek(stack_num), num, 
                                            *(char*)StackPeek(stack_op));
            StackPop(stack_num);
            StackPop(stack_op);
        }    
    }

    ans_handle->answer = num;

    return (STOP);
}

static int ErrorMessage(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state)
{
    UNUSED(stack_num);
    UNUSED(stack_op);
    UNUSED(ans_handle);
    UNUSED(input);

    if(state == PO || state == PN)
    {
        sprintf(ans_handle->message, 
            "error. number expected, problematic entery: '%c'", input);
    }
    if (state == WS)
    {
        sprintf(ans_handle->message, 
            "error. operand or NULL expected, problematic entery: '%c'", input);
    }
    ans_handle->answer = 0;

    return (STOP);
}

static int WSProc(stack_t * stack_num, 
                stack_t * stack_op,
                cal_t * ans_handle,
                const char input,
                int state)
{
    UNUSED(stack_num);
    UNUSED(stack_op);
    UNUSED(ans_handle);
    UNUSED(input);

    switch(state)
    {
        case START :
            return(START);
        case PN :
            return(WS);
        case WS :
            return(WS);
        case PO :
            return(PO);
        default :
            return (STOP);
    }
}

/*===================assistance functions ===================*/

static int IsOperation(char ch)
{
    if(ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '^')
    {
        return(1);
    }

    return(0);
}

static int IsNumber(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return (1);
    }

    return(0);
}

static int Priority(char ch)
{
    switch(ch)
    {
        case '+' :
            return(0);
        case '-' :
            return(0);
        case '*' :
            return(1);
        case '/' :
            return(1);
        case '^' :
            return(2);
        default :
            return (0);
    }
}

static double CurrentCalculation(double num1, double num2, char op)
{
    switch(op)
    {
        case '+' :
            return(num1 + num2);
        case '-' :
            return(num1 - num2);
        case '*' :
            return(num1 * num2);
        case '/' :
            return(num1 / num2);
        case '^' :
            return(pow(num1, num2));
        default :
            return (0);
    }
}