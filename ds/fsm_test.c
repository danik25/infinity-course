/******************************************************************************
 * File name  : fsm.h
 * Version    : 1.1
 * Developer  : Dani Benjamin
 * Reviewer   : Yuval Shapira
 * Date		  : 28.4.19
 ******************************************************************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include "fsm.h"

static void InitTest();
static void AllocTest();
static void FreeTest();
static void CountFreeTest();
static void suggestSizeTest();

#define GREEN(str) printf("\033[1;32m%s\033[0m\n", str)
#define RED(str) printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str) printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str) printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str) printf("\033[1;35m%s\033[0m\n", str)

int main()
{
	CYAN("\n\n\t\t\t~TEST FILE FSM~");
    CYAN("\t\t\t    Dani Benjamin\n\n");
    YELLOW("\n********init test********\n");
	InitTest();

	CYAN("\n\n\t\t\t~THE END~\n\n");
    return (0);
}

static void InitTest()
{
	void* fsm = malloc(248);
	void * freed = NULL;
	fsm_t *new_fsm = FSMInit(fsm, 248, 100);
	printf("%ld\n", FSMSuggestSize(2, 100));
	printf("%ld\n", FSMCountFree(new_fsm));
	freed = FSMAlloc(new_fsm);
	printf("%ld\n", FSMCountFree(new_fsm));
	FSMFree(freed);
	printf("%ld\n", FSMCountFree(new_fsm));
}