/****************************************************************
*                Data Structures - Double Linked List           *
* Related files: dl_list.c 	dl_list.h	dl_list_test.c	        *
* #Version: V 1.7                                               *
* writer: Dani Benjamin                                 		*
* reviewer: Amir Tzin                               			*
* last update: 14.4.19                                          *
****************************************************************/

#include <stdio.h> /*printf*/
#include "dl_list.h"

#define UNUSED(x) (void)(x)
#define DEADBEEF (void*)0xdeadbeefdeadbeef

/*
tests:
1. DLCreate 
2. DLIsEmpty
    2.1 empty list
    2.2 fill list
3. DLCount
    3.1 empty list
    3.2 full list
4. DLEnd & DLBegin
    4.1 empty list
    4.2 full list
5. DLNext & DLPrev
    5.1 prev on first element
    5.2 next on last element
6. DLGetData 
    6.1 empty list
    6.2 last element
7. DLSameIter 
    7.1 same data number
8. DLInsert
9. DLErase
    9.1 erasing from empty list
    9.2 earasing first element
    9.3 erasing last element
10. DLPushFront & DLPushBack
11. DLPopFront & DLPopBack
    11.1 regular
    11.2 pop on empty list
12. DLForEach 
    12.1 adding 1
    12.2 printing
13. DLFind 
    13.1 not existing data
    13.2 exisiting data 
14. DLSplice 
    14.1 empty source case
    14.2 regular case
    14.3 part of the source case
    14.3 empty dest case
*/

static void PrintListInt(dll_t *dl_list);

static void TestCreate();
static void TestIsEmpty();
static void TestCount();
static void TestBeginNEnd();
static void TestNextNPrev();
static void TestGetData();
static void TestSameIter();
static void TestInsert();
static void TestErase();
static void TestPushBackNFront();
static void TestPopFrontNBack();
static void TestForEach();
static void TestFind();
static void TestSpliceRegular();
static void TestSpliceMiddleSource();
static void TestSpliceEmptyDest();

/*for each functions*/
int Add(void *data, void* param);
int PrintInt(void *data, void* param);

/*find functions*/
int IsMatchInt(void *data, void* param);

int main()
{
	printf("\n********create test********\n\n");
	TestCreate();
	printf("********is empty test********\n\n");
	TestIsEmpty();
	printf("********count test********\n\n");
	TestCount();
	printf("********begin and end test********\n\n");
	TestBeginNEnd();
	printf("********next and prev test********\n\n");
	TestNextNPrev();
	printf("********get data test********\n\n");
	TestGetData();
	printf("********same iter test********\n\n");
	TestSameIter();
	printf("********insert test********\n\n");
	TestInsert();
	printf("********erase test********\n\n");
	TestErase();
	printf("********push back and front test********\n\n");
	TestPushBackNFront();
	printf("********pop front and back test********\n\n");
	TestPopFrontNBack();
	printf("********for each test********\n\n");
	TestForEach();
	printf("********find test********\n\n");
	TestFind();
	printf("********splice test********\n\n");
	TestSpliceRegular();
	TestSpliceMiddleSource();
	TestSpliceEmptyDest();

	return (0);
}

static void TestCreate()
{
	dll_t *dll = DLCreate();
	(dll) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestIsEmpty()
{
	int data1 = 1;
	dll_t *dll = DLCreate();
	printf("1. empty list:\n");
	DLIsEmpty(dll) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("\n");
	DLPushFront(dll, &data1);
	printf("2. full list:\n");
	(!DLIsEmpty(dll)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestCount()
{
    int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	
	printf("1. count empty list:\n");
	(0 == DLCount(dll)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	printf("\n2. count full list:\n");
	(sizeof(data)/sizeof(int) == DLCount(dll)) ? 
	                        printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestBeginNEnd()
{
    int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	printf("1. empty list:\n");
	(node == DLEnd(dll)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	printf("2. begin in full list\n");
	node = DLBegin(dll);
	(*(int*)DLGetData(node) == data[3]) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
    DLDestroy(dll);
	printf("\n");
}

static void TestNextNPrev()
{
	dll_t *dll = DLCreate();
	printf("1. prev on the first element\n");
	(DLPrev(DLPrev(DLBegin(dll))) == NULL) ? 
	                printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("2. next on last element\n");
	(DLNext(DLEnd(dll)) == NULL) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestGetData()
{
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	printf("1. empty list:\n");
	(DEADBEEF == DLGetData(node)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("2. end of list:\n");
	(DEADBEEF == DLGetData(DLEnd(dll))) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestSameIter()
{
    int data[] = {1, 1, 1, 1};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	node = DLBegin(dll);
	printf("1. same number\n");
	(!DLSameIter(node, DLNext(node))) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestInsert()
{
	int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	int status = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	
	i -= 1;
	
	for(node = DLBegin(dll); node != DLEnd(dll); node = DLNext(node), --i)
	{
	    if(*(int*)DLGetData(node) != data[i])
	    {
	        status = 1;
	    }
	}
	
	(!status) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	
	PrintListInt(dll);
	DLDestroy(dll);
	printf("\n");
}

static void TestErase()
{
    int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	
	printf("1. erasing element from empty list:\n");
	(DLErase(DLBegin(dll)) == NULL) ? 
	                    printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	printf("\n");
	printf("the original list:\n");
	PrintListInt(dll);
	printf("\n");
	printf("2. erasing the first element:\n");
	(DLNext(DLBegin(dll) )== DLErase(DLBegin(dll))) ? 
	                        printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	PrintListInt(dll);
	printf("\n");
	printf("3. erasing the last element:\n");
	(DLErase(DLEnd(dll)) == NULL) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	PrintListInt(dll);
	
	DLDestroy(dll);
	printf("\n");
}

static void TestPushBackNFront()
{
    int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	size_t status = 0;
	
	DLPushFront(dll, &data[1]);
	DLPushBack(dll, &data[2]);
	
	DLPushFront(dll, &data[0]);
	DLPushBack(dll, &data[3]);
	
	for(i = 0, node = DLBegin(dll); node != DLEnd(dll); 
	                                        ++i, node = DLNext(node))
	{
	    if(*(int*)DLGetData(node) != data[i])
	    {
	        status = 1;
	    }
	}
	PrintListInt(dll);
	(!status) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                        printf("\033[1;31mfail\033[0m\n");
	DLDestroy(dll);
	printf("\n");
}

static void TestPopFrontNBack()
{
    int data[] = {1, 3};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	size_t i = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	printf("original list:\n");
	PrintListInt(dll);
	printf("poping the first element:\n");
	DLPopFront(dll);
	PrintListInt(dll);
	printf("poping the last element:\n");
	DLPopBack(dll);
	PrintListInt(dll);
	
	printf("poping empty list:\n");
	DLPopBack(dll);
	PrintListInt(dll);
	
	DLDestroy(dll);
	printf("\n");
}

static void TestForEach()
{
    int data[] = {1, 2, 3, 4};
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	dl_iter_t first = NULL;
	dl_iter_t last = NULL;
	size_t i = 0;
	int number = 1;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	first = DLBegin(dll);
	last = DLEnd(dll);
	printf("original list:\n");
	PrintListInt(dll);
	printf("after adding '%d'\n", number);
	DLForEach(first, last, Add, &number);
	PrintListInt(dll);
	
	printf("printing with 'for each':\n");
	DLForEach(first, last, PrintInt, NULL);
	
	DLDestroy(dll);
	printf("\n\n");
}

static void TestFind()
{
    int data[] = {1, 2, 3, 4};
    int number = 5;
	dll_t *dll = DLCreate();
	dl_iter_t node = DLBegin(dll);
	dl_iter_t first = NULL;
	dl_iter_t last = NULL;
	size_t i = 0;
	dl_iter_t result = NULL;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		node = DLInsert(dll, node, &data[i]);
	}
	
	first = DLBegin(dll);
	last = DLEnd(dll);
	
	printf("1. not existing\n");
	result = DLFind(dll, first, last, IsMatchInt, &number);
	
	(result == last) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("2. existing\n");
	result = DLFind(dll, first, last, IsMatchInt, &data[0]);
	(result != last) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	
	DLDestroy(dll);
	printf("\n\n");
}

static void TestSpliceRegular()
{
    int data1[] = {1, 2, 3, 4};
    int data2[] = {7, 8, 9};
    size_t i = 0;
    dll_t *dll1 = DLCreate();
    dll_t *dll2 = DLCreate();
    dl_iter_t node1 = DLBegin(dll1);
    dl_iter_t node2 = DLBegin(dll2);
    printf("1. empty list source case\n\n");
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		node1 = DLInsert(dll1, node1, &data1[i]);
	}

	printf("first list:\n");
	PrintListInt(dll1);
	printf("\nsecond list:\n");
	PrintListInt(dll2);
	printf("\nsplicing\n");
	DLSplice(dll2, DLBegin(dll2), DLEnd(dll2), node1);
	PrintListInt(dll1);
	printf("\nsecond list remains\n");
	PrintListInt(dll2);
	
	for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		node2 = DLInsert(dll2, node2, &data2[i]);
	}
    printf("\n2. regular case\n\n");
    
	printf("first list:\n");
	PrintListInt(dll1);
	printf("\nsecond list:\n");
	PrintListInt(dll2);
	printf("\ninserting in the middle\n");
	node1 = DLNext(DLNext(node1));
	DLSplice(dll2, DLBegin(dll2), DLEnd(dll2), node1);
	PrintListInt(dll1);
	printf("\nsecond list remains\n");
	PrintListInt(dll2);
	
	DLDestroy(dll1);
	DLDestroy(dll2);
	printf("\n\n");
}

static void TestSpliceMiddleSource()
{
    int data1[] = {1, 2, 3, 4};
    int data2[] = {7, 8, 9};
    size_t i = 0;
    dll_t *dll1 = DLCreate();
    dll_t *dll2 = DLCreate();
    dl_iter_t node1 = DLBegin(dll1);
    dl_iter_t node2 = DLBegin(dll2);
    
    dl_iter_t first  = NULL;
    dl_iter_t last  = NULL;
    
    printf("2. part of the source case\n\n");
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		node1 = DLInsert(dll1, node1, &data1[i]);
	}
	
	for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		node2 = DLInsert(dll2, node2, &data2[i]);
	}
	
	first = DLBegin(dll2);
	last = DLEnd(dll2);
	
	printf("first list:\n");
	PrintListInt(dll1);
	printf("\nsecond list:\n");
	PrintListInt(dll2);
	printf("\ninserting in the middle\n");
	node1 = DLNext(DLNext(node1));
	DLSplice(dll2, DLNext(first), DLPrev(last), node1);
	PrintListInt(dll1);
	printf("\nsecond list remains\n");
	PrintListInt(dll2);
	
	DLDestroy(dll1);
	DLDestroy(dll2);
	printf("\n\n");
}

static void TestSpliceEmptyDest()
{
    int data2[] = {7, 8, 9};
    size_t i = 0;
    dll_t *dll1 = DLCreate();
    dll_t *dll2 = DLCreate();

    dl_iter_t node2 = DLBegin(dll2);
    
    dl_iter_t first  = NULL;
    dl_iter_t last  = NULL;
    
    printf("4. empty dest case\n\n");
	
	for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		node2 = DLInsert(dll2, node2, &data2[i]);
	}
	
	first = DLBegin(dll2);
	last = DLEnd(dll2);
	
	printf("first list:\n");
	PrintListInt(dll1);
	printf("\nsecond list:\n");
	PrintListInt(dll2);
	
	printf("\nsplicing\n");
	DLSplice(dll2, first, last, DLBegin(dll1));
	PrintListInt(dll1);
	printf("\nsecond list remains\n");
	PrintListInt(dll2);
	
	DLDestroy(dll1);
	DLDestroy(dll2);
	printf("\n\n");
}

/*assistance function*/
static void PrintListInt(dll_t *dl_list)
{
	dl_iter_t i = NULL;
	printf("DEADBEEF <=> ");
	for(i = DLBegin(dl_list); i != DLEnd(dl_list); i = DLNext(i))
	{
		printf("%d <=> ",*(int*)DLGetData(i));
	}
	printf("DEADBEEF \n");
}

/*for each functions*/
int Add(void *data, void* param)
{
    if(NULL == data && NULL == param)
    {
        return (1);
    }
    *(int*)data = *(int*)data + *(int*)param;
    return (0);
}
int PrintInt(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data)
    {
        return (1);
    }
	printf("%d <=> ",*(int*)data);
	return (0);
}

/*find functions*/
int IsMatchInt(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data && NULL == param)
    {
        return (0);
    }
    if(*(int*)data == *(int*)param)
    {
        return (1); /*equal*/
    }
    return (0);
}











