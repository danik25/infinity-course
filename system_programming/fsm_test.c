/******************************************************************************
 * File name  : fsm.h
 * Version    : 1.2
 * Developer  : Dani Benjamin
 * Reviewer   : Ayala Rosel
 * Date       : 30.4.19
 ******************************************************************************/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include "fsm.h"

static void InitTest();
static void AllocTest();
static void FreeTest();
static void CountFreeTest();
static void SuggestSizeTest();

#define GREEN(str) printf("\033[1;32m%s\033[0m\n", str)
#define RED(str) printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str) printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str) printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str) printf("\033[1;35m%s\033[0m\n", str)

int main()
{
	CYAN("\n\n\t\t\t~TEST FILE FSM~");
    CYAN("\t\t\t Dani Benjamin\n\n");
    YELLOW("\n********init test********\n");
	InitTest();
	YELLOW("\n********alloc test********\n");
	AllocTest();
	YELLOW("\n********free test********\n");
	FreeTest();
	YELLOW("\n********count free test********\n");
	CountFreeTest();
	YELLOW("\n********suggest size test********\n");
	SuggestSizeTest();

	CYAN("\n\n\t\t\t   ~THE END~\n\n");
    return (0);
}

static void InitTest()
{
	void* fsm1 = (void*) malloc(248);
	void* fsm2 = (void*) malloc(4);
	void* fsm3 = (void*) malloc(357);

	size_t size = FSMSuggestSize(2, 100);

	fsm_t *new_fsm1 = FSMInit(fsm1, size, 100);
	fsm_t *new_fsm2 = FSMInit(fsm2, 4, 2);
	fsm_t *new_fsm3 = FSMInit(fsm3, 357, 100);

	PURPLE("1. init of small size:");
	(!new_fsm2) ? GREEN("success") : RED("fail");

	PURPLE("\n2. regular size");
	(FSMCountFree(new_fsm1) == 2) ? GREEN("success") : RED("fail");

	PURPLE("\n3. no padding on the last block");
	(FSMCountFree(new_fsm3) == 3) ? GREEN("success") : RED("fail");

	free(fsm1);
	free(fsm2);
	free(fsm3);
}

static void AllocTest()
{
	fsm_t *new_fsm1 = NULL;
	fsm_t *new_fsm2 = NULL;

	size_t size = FSMSuggestSize(1, 100);
	void* tmp = NULL;

	new_fsm2 = (fsm_t*) malloc(size);
	new_fsm2 = FSMInit(new_fsm2, size, 100);

	PURPLE("1. more allocs than existing blocks:");
	tmp = FSMAlloc(new_fsm2);
	tmp = FSMAlloc(new_fsm2);
	(!tmp) ? GREEN("success") : RED("fail");

	free(new_fsm1);
	free(new_fsm2);
}

static void FreeTest()
{
	size_t size = FSMSuggestSize(2, 100);
	void* fsm1 = (void*) malloc(size);
	void* tmp = NULL;
	int status = 0;
	fsm1 = FSMInit(fsm1, size, 100);

	tmp = FSMAlloc(fsm1);
	if(FSMCountFree(fsm1) != 1)
	{
		status = 1;
	}
	FSMFree(tmp);
	if(FSMCountFree(fsm1) != 2)
	{
		status = 1;
	}

	(!status) ? GREEN("success") : RED("fail");

	free(fsm1);
}

static void CountFreeTest()
{
	size_t size = FSMSuggestSize(3, 50);
	void* fsm1 = (void*) malloc(size);
	int status = 0;
	size_t i = 0;
	fsm1 = FSMInit(fsm1, size, 50);
	for(; i < 3; ++i)
	{
		if(FSMCountFree(fsm1) != 3 - i)
		{
			status = 1;
		}
		FSMAlloc(fsm1);
	}
	(!status) ? GREEN("success") : RED("fail");

	free(fsm1);
}

static void SuggestSizeTest()
{
	size_t exp[] = {24, 248, 88};
	size_t block_num_input[] = {0, 2, 1};
	size_t block_size_input[] = {5, 100, 50};

	size_t i = 0;
	int status = 0;
	for(; i < sizeof(exp) / sizeof(size_t); ++i)
	{
		if(exp[i] != FSMSuggestSize(block_num_input[i], block_size_input[i]))
		{
			status = 1;
		}
	}
	(!status) ? GREEN("success") : RED("fail");
}

