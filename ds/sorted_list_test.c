/****************************************************************
*                Data Structures - Sorted List                  *
* Related files:    sorted_list.c    dl_list.h                  *
*	            sorted_list.h    sorted_list_test.c	            *
* #Version: V 1.4                                               *
* Writer: Dani Benjamin                                	        *
* Reviewer: Tom Valershtein                                    	*
* Last update: 16.4.19                                          *
****************************************************************/
#include <stdio.h>
#include "sorted_list.h"

#define UNUSED(x) (void)(x)
#define DEADBEEF (void*)0xdeadbeefdeadbeef

/*
Sort list tests:
1. SortCreate 
2. SortIsEmpty 
    2.1 empty list 
    2.2 fill list 
3. SortSize
    3.1 empty list 
    3.2 full list 
4. SortEnd & SortBegin 
    4.1 empty list 
    4.2 full list 
5. SortNext & SortPrev 
    5.1 prev on first element 
    5.2 next on last element 
6. SortGetData 
    6.1 empty list 
    6.2 last element 
7. SortIsSameIter 
    7.1 same data number 
8. SortErase
    8.1 erasing from empty list
    8.3 erasing last element
9. SortInsert
10. SortPopFront & SortPopBack 
    10.1 regular 
    10.2 pop on empty list 
11. SortForEach 
    11.1 adding 1 
    11.2 printing 
12. SortFind ?
    12.1 not existing data ?
    12.2 exisiting data ?
13. SortMerge 
    13.1 regular case
    13.2 the 'from' ends before the 'to' 
    13.3 empty 'from'
    13.4 empty 'to'
*/

/*compare function*/
int Compare(void *data1, void *data2, void* param);
/*for each function*/
int SortPrintInt(void *data, void* param);
/*find functions*/
int SortIsMatchInt(void *data, void* param);

/*checking function*/
void Check(sorted_list_t *s_list, int exp[], size_t size);

/*test functions*/
static void CreateTest();
static void TestIsEmpty();
static void TestSize();
static void TestBeginNEnd();
static void TestNextNPrev();
static void TestGetData();
static void TestSameIter();
static void InsertTest();
static void TestPopFrontNBack();
static void TestForEach();
static void EraseTest();
static void TestFind();
static void MergeTest();
static void MergeTestSrcSmaller();
static void MergeTestEmpytFrom();
static void MergeTestEmpytTo();

int main()
{
    printf("\n\033[01;33m********create test******** \033[0m\n\n");
    CreateTest();
    printf("\n\033[01;33m********is empty test******** \033[0m\n\n");
    TestIsEmpty();
    printf("\n\033[01;33m********count test******** \033[0m\n\n");
    TestSize();
    printf("\n\033[01;33m********begin and end test******** \033[0m\n\n");
    TestBeginNEnd();
    printf("\n\033[01;33m********next and prev test******** \033[0m\n\n");
    TestNextNPrev();
    printf("\n\033[01;33m********get data test******** \033[0m\n\n");
    TestGetData();
    printf("\n\033[01;33m********same iter test******** \033[0m\n\n");
    TestSameIter();
    printf("\033[01;33m********insert test******** \033[0m\n\n");
    InsertTest();
    printf("\033[01;33m********pop front and back test******** \033[0m\n\n");
    TestPopFrontNBack();
    printf("\033[01;33m********for each test******** \033[0m\n\n");
    TestForEach();
    printf("\033[01;33m********erase test******** \033[0m\n\n");
    EraseTest();
    printf("\033[01;33m********find test******** \033[0m\n\n");
    TestFind();
    printf("\033[01;33m********merge test******** \033[0m\n\n");
    MergeTest();
    MergeTestSrcSmaller();
    MergeTestEmpytFrom();
    MergeTestEmpytTo();
    printf("\t\t\t\033[1;36m ~ THE END ~ \033[0m\n\n");
    return (0);
}


static void CreateTest()
{
    sorted_list_t *s_list = SortCreate(Compare, NULL);
    (s_list) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void TestIsEmpty()
{
	int data1 = 1;
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	printf("1. empty list:\n");
	SortIsEmpty(s_list) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	printf("\n");
	SortInsert(s_list, &data1);
	printf("2. full list:\n");
	(!SortIsEmpty(s_list)) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void TestSize()
{
    int data[] = {1, 2, 3, 4};
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	size_t i = 0;
	
	printf("1. count empty list:\n");
	(0 == SortSize(s_list)) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	printf("\n2. count full list:\n");
	(sizeof(data)/sizeof(int) == SortSize(s_list)) ? 
	                        printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void TestBeginNEnd()
{
    int data[] = {1, 2, 3, 4};
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	sorted_iter_t node = SortBegin(s_list);
	size_t i = 0;
	printf("1. empty list:\n");
	(node == SortEnd(s_list)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	printf("\n2. begin in full list\n");
	node = SortBegin(s_list);
	(*(int*)SortGetData(node) == data[0]) ? 
	                printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
    SortDestroy(s_list);
	printf("\n");
}

static void TestNextNPrev()
{
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	printf("1. prev on the first element\n");
	(SortPrev(SortPrev(SortBegin(s_list))) == NULL) ? 
	                printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("\n2. next on last element\n");
	(SortNext(SortEnd(s_list)) == NULL) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void TestGetData()
{
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	sorted_iter_t node = SortBegin(s_list);
	printf("1. empty list:\n");
	(DEADBEEF == SortGetData(node)) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("\n2. end of list:\n");
	(DEADBEEF == SortGetData(SortEnd(s_list))) ?
	                printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void TestSameIter()
{
    int data[] = {1, 1, 1, 1};
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	sorted_iter_t node = NULL;
	size_t i = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	node = SortBegin(s_list);
	printf("1. same number\n");
	(!SortIsSameIter(node, SortNext(node))) ? 
	            printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	SortDestroy(s_list);
	printf("\n");
}

static void InsertTest()
{
    int data[] = {1, 6, 1, 8, -7};
    int exp[] = {-7, 1, 1, 6, 8};
    int status = 0;
    sorted_list_t *s_list = SortCreate(Compare, NULL);
    sorted_iter_t node = NULL;
    size_t i = 0;
    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	for(i = 0, node = SortBegin(s_list); i < sizeof(exp)/sizeof(int); ++i, 
	                                        node = SortNext(node))
	
	{
		if(*(int*)SortGetData(node) != exp[i])
		{
		    status = 1;
		}
	}
	(!status) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	
	SortDestroy(s_list);
	printf("\n\n");   
}

static void EraseTest()
{
    int data[] = {1, 6, 1, 8, -7};
    int exp[] = {-7, 1, 1, 6};
    sorted_list_t *s_list = SortCreate(Compare, NULL);
    size_t i = 0;
    printf("\033[1;35m1. erasing first element in empty list: \033[0m\n");
    (NULL == SortErase(SortBegin(s_list))) ? 
                        printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n\n");
	                                
    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	printf("\033[1;35m\n1. erasing last element: \033[0m\n");
	printf("original list:\n");
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n\n");
	printf("erasing last element:\n");
	SortErase(SortPrev(SortEnd(s_list)));
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
    printf("\n");
	Check(s_list, exp, sizeof(exp)/sizeof(int));
	
	SortDestroy(s_list);
	printf("\n\n");
}

static void TestPopFrontNBack()
{
    int data[] = {1, 3};
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	size_t i = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	printf("original list:\n");
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	printf("poping the first element:\n");
	SortPopFront(s_list);
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	printf("poping the last element:\n");
	SortPopBack(s_list);
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	
	printf("poping empty list:\n");
	SortPopBack(s_list);
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	
	SortDestroy(s_list);
	printf("\n\n");
}

static void TestForEach()
{
    int data[] = {1, 4, 3, 2};
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	size_t i = 0;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	
	printf("printing with 'for each':\n");
	SortForEach(SortBegin(s_list), SortEnd(s_list), SortPrintInt, NULL);
	printf("\n");
	
	SortDestroy(s_list);
	printf("\n\n");
}

static void TestFind()
{
    int data[] = {1, 2, 3, 4};
    int number = 5;
	sorted_list_t *s_list = SortCreate(Compare, NULL);
	sorted_iter_t first = NULL;
	sorted_iter_t last = NULL;
	size_t i = 0;
	sorted_iter_t result = NULL;
	
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		SortInsert(s_list, &data[i]);
	}
	
	first = SortBegin(s_list);
	last = SortEnd(s_list);
	
	printf("1. not existing\n");
	result = SortFind(s_list, first, last, SortIsMatchInt, &number);
	
	(result == last) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	printf("\n2. existing\n");
	result = SortFind(s_list, first, last, SortIsMatchInt, &data[0]);
	(result != last) ? printf("\033[0;32msuccess\033[0m\n") : 
	                                printf("\033[1;31mfail\033[0m\n");
	
	SortDestroy(s_list);
	printf("\n\n");
}

static void MergeTest()
{
    int data1[] = {9, 11, 5, 2};
    int data2[] = {1, 10, 6, 7, 4, 0, 3, 8};
    int exp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int status = 0;
    sorted_list_t *to = SortCreate(Compare, NULL);
    sorted_list_t *from = SortCreate(Compare, NULL);
    sorted_iter_t node = NULL;
    size_t i = 0;
    printf("\033[1;35m1. regular case: \033[0m\n");
    /*filling the 'to' list*/
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		SortInsert(to, &data1[i]);
	}
	/*filling the 'from' list*/
    for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		SortInsert(from, &data2[i]);
	}
	printf("'to' list:\n");
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	printf("'from' list:\n");
	SortForEach(SortBegin(from), SortEnd(from), SortPrintInt, NULL);
	printf("\n");
	printf("merging:\n");
	SortMerge(to, from);
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	for(i = 0, node = SortBegin(to); i < sizeof(exp)/sizeof(int); ++i, 
	                                        node = SortNext(node))
	
	{
		if(*(int*)SortGetData(node) != exp[i])
		{
		    status = 1;
		}
	}
	(!status) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
	SortDestroy(to);
	printf("\n");
}

static void MergeTestSrcSmaller()
{
    int data1[] = {3, 1, 9, 5, 17};
    int data2[] = {4, 6, 2, 8, 7, 10};
    int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 17};
    sorted_list_t *to = SortCreate(Compare, NULL);
    sorted_list_t *from = SortCreate(Compare, NULL);
    size_t i = 0;
    printf("\033[1;35m2. the 'from' ends before the 'to' \033[0m\n");
    /*filling the 'to' list*/
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		SortInsert(to, &data1[i]);
	}
	/*filling the 'from' list*/
    for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		SortInsert(from, &data2[i]);
	}
	printf("'to' list:\n");
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	printf("'from' list:\n");
	SortForEach(SortBegin(from), SortEnd(from), SortPrintInt, NULL);
	printf("\n");
	printf("merging:\n");
	SortMerge(to, from);
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	Check(to, exp, sizeof(exp)/sizeof(int));
	SortDestroy(to);
	printf("\n");
}

static void MergeTestEmpytFrom()
{
    int data1[] = {3, 1, 9, 5, 17};
    int exp[] = {1, 3, 5, 9, 17};
    sorted_list_t *to = SortCreate(Compare, NULL);
    sorted_list_t *from = SortCreate(Compare, NULL);
    size_t i = 0;
    printf("\033[1;35m3. empty 'from':\033[0m\n");
    /*filling the 'to' list*/
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		SortInsert(to, &data1[i]);
	}

	printf("'to' list:\n");
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	printf("'from' list:\n");
	SortForEach(SortBegin(from), SortEnd(from), SortPrintInt, NULL);
	printf("\n");
	printf("merging:\n");
	SortMerge(to, from);
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	Check(to, exp, sizeof(exp)/sizeof(int));
	SortDestroy(to);
	printf("\n");
}

static void MergeTestEmpytTo()
{
    int data2[] = {4, 6, 2, 8, 7, 10};
    int exp[] = {2, 4, 6, 7, 8, 10};
    sorted_list_t *to = SortCreate(Compare, NULL);
    sorted_list_t *from = SortCreate(Compare, NULL);
    size_t i = 0;
    printf("\033[1;35m4. empty 'to':\033[0m\n");

	/*filling the 'from' list*/
    for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		SortInsert(from, &data2[i]);
	}
	printf("'to' list:\n");
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	printf("'from' list:\n");
	SortForEach(SortBegin(from), SortEnd(from), SortPrintInt, NULL);
	printf("\n");
	printf("merging:\n");
	SortMerge(to, from);
	SortForEach(SortBegin(to), SortEnd(to), SortPrintInt, NULL);
	printf("\n");
	Check(to, exp, sizeof(exp)/sizeof(int));
	SortDestroy(to);
	printf("\n");
}

/*compare function*/
int Compare(void *data1, void *data2, void* param)
{
    UNUSED(param);
    if(*(int*)data1 < *(int*)data2)
    {
        return (1);
    }
    return (0);
}

/*for each function*/
int SortPrintInt(void *data, void* param)
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
int SortIsMatchInt(void *data, void* param)
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

/*checking function*/
void Check(sorted_list_t *s_list, int exp[], size_t size)
{
    int status = 0;
    size_t i = 0; 
    sorted_iter_t node = NULL;
    for(i = 0, node = SortBegin(s_list); i < size; ++i, 
	                                        node = SortNext(node))
	
	{
		if(*(int*)SortGetData(node) != exp[i])
		{
		    status = 1;
		}
	}
	(!status) ? printf("\033[0;32msuccess \033[0m\n") : 
	                                printf("\033[1;31mfail \033[0m\n");
}






