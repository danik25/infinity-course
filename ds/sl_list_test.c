/****************************************************************
*                Data Structures - Singly Linked List           *
* Related files:                                                *
* #Version: V 1                                                 *
* writer: Dani Benjamin                                         *
* reviewer: Oded Bryt                                           *
* last update: 10.4.19                                          *
****************************************************************/ 

#include <stdio.h> /*printf*/
#include <stdlib.h> /*exit */
#include "sl_list.h"
#define UNUSED(x) (void)(x)

/*
1. TestCreate()
2. TestInsert()
3. TestInsertAfter()
4. RemoveTest()
	4.1 remove last element - ERROR expected
	4.2 remove the first element
	4.3 remove the only element 
5. RemoveAfterTest()
	5.1 remove after the first element
	5.2 remove after the last element - ERROR expected
6. ForEachTest()
7. SLLFindTest()
    7.1 not existing
    7.2 existing
8. CountTest()
	8.1 counts element for an empty list
	8.2 counts a list with one element
9. FlipTest()
10. FindIntersectionTest()
	10.1 for list that end at the same node
	10.2 not interacting lists
	10.3 same list
11. HasLoopTest()
12. integretion test
*/

static void TestCreate();
static void TestInsert();
static void TestInsertAfter();
static void RemoveTest();
static void RemoveAfterTest();
static void ForEachTest();
static void SLLFindTest();
static void CountTest();
static void FlipTest();
static void FindIntersectionTest();
static void HasLoopTest();

/*static void TestCreateStruct();*/
static void TestIntegration();


/*assistance function*/
static void PrintNodeInt(sl_node_t *node);

/* functions for "for each" */
int Add(void *data, void* param);
int PrintInt(void *data, void* param);
int PrintChar(void *data, void* param);
/*int PrintStruct(void *data, void* param);*/

/* functions for "is a match" */
int IsMatchInt(void *data, void* param);
int IsMatchChar(void *data, void* param);

int main()
{
	printf("--------Creation Test--------\n\n");
	TestCreate();
    printf("--------Insert After Test--------\n\n");
    TestInsertAfter();
    printf("--------Insert Befor Test--------\n\n");
    TestInsert();
    printf("--------Remove Test--------\n\n");
    RemoveTest();
    printf("--------Remove After Test--------\n\n");
    RemoveAfterTest();
    printf("--------For Each Test--------\n\n");
    ForEachTest();
    printf("--------Find Test--------\n\n");
    SLLFindTest();
    printf("--------Counting Test--------\n\n");
    CountTest();
    printf("--------Flip Test--------\n\n");
    FlipTest();
    printf("--------Intersection Test--------\n\n");
    FindIntersectionTest();
    printf("--------Has Loop Test--------\n\n");
    HasLoopTest();
    
    printf("================integrtion test================\n\n");
    TestIntegration();
    
    return 0;
}

static void TestIntegration()
{
	char array1[] = {'e', 'c', 'a'};
    char array2[] = {'d', 'b'};
    char array3[] = {'g', 'n', 'u'};
    int capitalized = -32;
    char letter = 'E';
    sl_node_t *ans = NULL;
    size_t i = 0;
    sl_node_t *end = NULL;
    sl_node_t *node1 = NULL;
    sl_node_t *node2 = NULL;
    node1 = SLLCreate(&array1[i], NULL);
  
    for(i = 1; i < sizeof(array1)/sizeof(char); ++i)
    {
        node1 = SLLCreate(&array1[i], node1);
    }
    
    printf("the original linked list, (printed with 'For Each' function): \n");
    SLLForEach(node1, PrintChar, NULL);
    printf("\n");
    printf("number of elements: %ld\n", SLLCount(node1));
    printf("\n");
    
    node2 = SLLCreate(&array2[1], NULL);
    printf("inserting '%c' AFTER '%c' \n", array2[1], array1[2]);
    node2 = SLLInsertAfter(node2, node1);
    SLLForEach(node1, PrintChar, NULL);
    printf("\n");
    printf("number of elements: %ld\n", SLLCount(node1));
    printf("\n");
    
    node2 = SLLCreate(&array2[0], NULL);
    printf("inserting '%c' BEFOR '%c' \n", array2[0], array1[0]);
    node2 = SLLInsert(node2, node1->next->next->next);
    SLLForEach(node1, PrintChar, NULL);
    printf("\n");
    printf("number of elements: %ld\n", SLLCount(node1));
    printf("\n");
    
    printf("capitalize all the letters with 'For Each' function: \n");
	SLLForEach(node1, Add, &capitalized);
	SLLForEach(node1, PrintChar, NULL);
    printf("\n\n");
    
    printf("flipping the list: \n");
    node1 = SLLFlip(node1);
    SLLForEach(node1, PrintChar, NULL);
    printf("\n\n");
    
    printf("finding '%c': \n", letter);
    if(SLLFind(node1, IsMatchChar, &letter))
    {
        printf("\033[0;32m");
        printf("exists!, success \n\n");
        printf("\033[0m");
    }
    else
    {
         printf("\033[1;31m");
         printf("fail\n");
         printf("\033[0m");
    }
    
    printf("removing first letter, with 'Remove' function\n");
    node2 = SLLRemove(node1);
    
    SLLDestroy(node2);
    node2 = NULL;
    
    SLLForEach(node1, PrintChar, NULL);
    printf("\n");
    printf("finding '%c': \n", letter);
    if(!SLLFind(node1, IsMatchChar, &letter))
    {
        printf("\033[0;32m");
        printf("doesn't exist!, success \n\n");
        printf("\033[0m");
    }
    else
    {
         printf("\033[1;31m");
         printf("fail\n");
         printf("\033[0m");
    }    
    
    printf("removing the letter after '%c', with 'RemoveAfetr' function\n", 
    													*(char*)node1->data);
    node2 = SLLRemoveAfter(node1);
    
    SLLDestroy(node2);
    node2 = NULL;
    
    SLLForEach(node1, PrintChar, NULL);
    printf("\n");
    printf("number of elements: %ld\n", SLLCount(node1));
    printf("\n");
    
    printf("creating another list ending with the same node\n");
    i = 0;
    
    node2 = SLLCreate(&array3[i], node1->next->next);
    end = node2;
    for(i = 1; i < sizeof(array3)/sizeof(char); ++i)
    {
        node2 = SLLCreate(&array3[i], node2);
    }
    SLLForEach(node2, PrintChar, NULL);
    printf("\n");
    printf("checking for an intersection:\n");
    ans = SLLFindIntersection(node1, node2);
    if(ans)
    {
        printf("\033[0;32m");
        printf("intersection!, success\n\n");
        printf("\033[0m");
    }
    else
    {
         printf("\033[1;31m");
         printf("fail\n");
         printf("\033[0m");
    }
    end->next = NULL;
    printf("attaching last node to the second one:\n");
    node1->next->next->next = node1->next;
    SLLHasLoop(node1) ? printf("\033[0;32mloop!!\033[0m\n") : 
                                    printf("\033[1;31mfail\n\033[0m");
    
    printf("after detaching:\n");
    node1->next->next->next = NULL;
    (!SLLHasLoop(node1)) ? printf("\033[0;32mno loop!!\033[0m\n") :
                                     printf("\033[1;31mfail\n\033[0m\n");
    printf("\n");
    
    printf("\n\t\t\t\033[1;36m~THE END~\033[0m\n\n\n");
    
    SLLDestroy(node2);
    SLLDestroy(node1);
    
}

/****************************************************************/

static void TestCreate()
{
	int data1 = 5;
	sl_node_t *first = SLLCreate(&data1, NULL);
	(first) ? printf("\033[0;32msuccessful creation\033[0m\n") : 
	                        printf("\033[1;31mfail\n\033[0m");
	printf("\n");
	SLLDestroy(first);
}

/****************************************************************/

static void TestInsert()
{
    int data1[] = {5, 3, 1};
    int data2[] = {2, 4};
    sl_node_t *start = NULL;
    size_t i = 0;
    sl_node_t *first1 = NULL;
    sl_node_t *last1 = SLLCreate(&data1[i], NULL);
    sl_node_t *last2 = NULL;
    
    for(i = 1; i < sizeof(data1)/sizeof(int); ++i)
    {
        first1 = SLLCreate(&data1[i], last1);
        last1 = first1;
    }
    printf("the original linked list: \n");
    PrintNodeInt(last1);
    start = last1;
    for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
    {
    	last1 = last1->next;
        last2 = SLLCreate(&data2[i], NULL);
        last1 = SLLInsert(last2, last1);
        
        last1 = last1->next;
        
    }
    printf("after the insertion: \n");
    PrintNodeInt(start);
    SLLDestroy(start);
    printf("\n");
}

static void TestInsertAfter()
{
    int data1[] = {5, 4, 3, 2, 1};
    int data2[] = {10, 9, 8, 7, 6};
    sl_node_t *start = NULL;
    size_t i = 0;
    sl_node_t *first1 = NULL;
    sl_node_t *last1 = SLLCreate(&data1[i], NULL);
    sl_node_t *last2 = NULL;
    
    for(i = 1; i < sizeof(data1)/sizeof(int); ++i)
    {
        first1 = SLLCreate(&data1[i], last1);
        last1 = first1;
    }
    printf("the original linked list: \n");
    PrintNodeInt(last1);
    start = last1;
    for(i = 1; i < sizeof(data1)/sizeof(int); ++i)
    {
        last2 = SLLCreate(&data2[i], NULL);
        last1 = SLLInsertAfter(last2, last1);
        last1 = last1->next;
    }
    printf("after the insertion: \n");
    PrintNodeInt(start);
    SLLDestroy(start);
    printf("\n");
}

/****************************************************************/

static void RemoveTest()
{
	/*creation of a new linked list*/
    int data1[] = {7, 6, 5, 4, 3};
    size_t i = 0;
    sl_node_t *first1 = NULL;
    sl_node_t *last1 = NULL;
    sl_node_t *removed = NULL;
    last1 = SLLCreate(&data1[i], NULL);
    printf("1. trying to remove the last element:\n");
    if(!SLLRemove(last1))
    {
    	printf("cant remove last element\n");
    	printf("\033[0;32msuccess\033[0m\n\n");   	
    }
    else
    {
    	printf("\033[1;31mfail\033[0m\n\n");
    }
    for(i = 1; i < sizeof(data1)/sizeof(int); ++i)
    {
        first1 = SLLCreate(&data1[i], last1);
        last1 = first1;
    }
    printf("2. trying to remove the second element:\n");
    printf("the original linked list: \n");
    PrintNodeInt(last1);
    printf("after removing the second element \n");
    removed = SLLRemove(last1->next);
    PrintNodeInt(last1);
    printf("\n");
    printf("removed: \n");
    PrintNodeInt(removed);
    printf("\n\n");
    SLLDestroy(removed);
    SLLDestroy(last1);
}

static void RemoveAfterTest()
{
    /*creation of a new linked list*/
    int data1[] = {5, 4, 3, 2, 1};
    size_t i = 0;
    sl_node_t *node = NULL;
    sl_node_t *start = NULL;
    sl_node_t *removed = NULL;
    node = SLLCreate(&data1[i], NULL);
	for(i = 1; i < sizeof(data1)/sizeof(int); ++i)
	{
		node = SLLCreate(&data1[i], node);
	}
    printf("1. trying to remove the second element:\n");
    printf("the original linked list: \n");
    PrintNodeInt(node);
    printf("after removing the second element \n");
    removed = SLLRemoveAfter(node);
    PrintNodeInt(node);
    printf("removed: \n");
    PrintNodeInt(removed);
    printf("\n");
    free(removed);
	start = node;
	while(node->next !=NULL)
	{
		node = node->next;
	}  
	printf("\n");
	printf("2. trying to remove the element after the last one:\n");
    removed = SLLRemoveAfter(node); 
    if(NULL == removed)
    {
        printf("no data\n");
    	printf("\033[0;32msuccess\033[0m\n\n");
    } 
    else
    {
        printf("\033[1;31mfail\033[0m\n\n");
    }
    printf("\n\n");
    SLLDestroy(start);
}

/****************************************************************/

static void ForEachTest()
{
    int array[] = {1, 1, 1, 1};
    int number = 1;
	sl_node_t *node = NULL;
	size_t i = 0;
	printf("For Each\n");
	node = SLLCreate(&array[i], NULL);
	for(i = 1; i < sizeof(array)/sizeof(int); ++i)
	{
		node = SLLCreate(&array[i], node);
	}
	printf("before\n");
	SLLForEach(node, PrintInt, NULL);
	printf("\n");
	printf("after adding '%d'\n", number);
	SLLForEach(node, Add, &number);
	SLLForEach(node, PrintInt, NULL);
	SLLDestroy(node);
	printf("\n\n");
}

/****************************************************************/

static void SLLFindTest()
{
    int array[] = {1, 1, 1, 1};
    int number1 = 2;
    int number2 = 1;
	sl_node_t *node = NULL;
	sl_node_t *result = NULL;
	size_t i = 0;
	node = SLLCreate(&array[i], NULL);
	for(i = 1; i < sizeof(array)/sizeof(int); ++i)
	{
		node = SLLCreate(&array[i], node);
	}
	printf("Find\n");
	printf("1. not existing test\n");
	result = SLLFind(node, IsMatchInt, &number1);
	if(!result)
    {
        PrintNodeInt(result);
    	printf("\033[0;32msuccess\033[0m\n\n");
    } 
    else
    {
        printf("\033[1;31mfail\033[0m\n\n");
    }
    
	printf("2. existing test\n");
	result = SLLFind(node, IsMatchInt, &number2);
	if(result)
    {
        PrintNodeInt(result);
    	printf("\033[0;32msuccess\033[0m\n\n");
    } 
    else
    {
        printf("\033[1;31mfail\033[0m\n\n");
    }
	SLLDestroy(node);
	printf("\n");
}

/****************************************************************/

static void CountTest()
{
	sl_node_t *first1 = NULL;
	size_t cnt = 0;
	int data1 = 5;
	printf("1. count empty list\n");
	cnt = SLLCount(first1);
	if(!cnt)
	{
		printf("empty\n");
		printf("\033[0;32msuccess\033[0m\n\n");
	}
	else
	{
		printf("amount of elements: %ld\n", cnt);
		printf("\033[1;31mfail\033[0m\n\n");
	}
	printf("2. count 1 element list\n");
	first1 = SLLCreate(&data1, NULL);
	cnt = SLLCount(first1);
	printf("amount of elements: %ld\n", cnt);
	if(1 == cnt)
	{
		printf("\033[0;32msuccess\033[0m\n\n");
	}
	else
	{
		printf("amount of elements: %ld\n", cnt);
		printf("\033[1;31mfail\033[0m\n\n");
	}
	printf("\n");
	SLLDestroy(first1);
}

/****************************************************************/

static void FlipTest()
{
	int array[] = {10, 11, 12, 13};
	sl_node_t *node = NULL;
	size_t i = 0;
	sl_node_t *ans_node = NULL;
	printf("Flipping\n");
	node = SLLCreate(&array[i], NULL);
	
	printf("1. flipping one node list\n");
	printf("original:\n");
	PrintNodeInt(node);
	ans_node = SLLFlip(node);
	printf("flipped:\n");
	PrintNodeInt(ans_node);
	printf("\n");
	printf("2. flipping multiple nodes list\n");
	for(i = 1; i < sizeof(array)/sizeof(int); ++i)
	{
		node = SLLCreate(&array[i], node);
	}
	printf("original:\n");
	PrintNodeInt(node);
	ans_node = SLLFlip(node);
	printf("flipped:\n");
	PrintNodeInt(ans_node);
	SLLDestroy(ans_node);
	printf("\n");
}

/****************************************************************/

static void FindIntersectionTest()
{
	size_t i = 0;
	sl_node_t *end = NULL;
	
	sl_node_t *answer = NULL;

	sl_node_t *last1 = NULL;
	sl_node_t *last2 = NULL;
	sl_node_t *last3 = NULL;
	
	int array1[] = {1, 2, 3};
	int array2[] = {7, 8, 9, 10};
	int array3[] = {17, 2};
	
	last1 = SLLCreate(&array1[i], NULL);
	last2 = SLLCreate(&array2[i], last1);
	end = last2;
	
	/*creation of a seperate linked list*/
	last3 = SLLCreate(&array3[0], NULL);
	last3 = SLLCreate(&array3[1], last3);
	
	
	for(i = 1; i < sizeof(array1)/sizeof(int); ++i)
    {
        last1 = SLLCreate(&array1[i], last1);
    }
    for(i = 1; i < sizeof(array2)/sizeof(int); ++i)
    {
        last2 = SLLCreate(&array2[i], last2);
    }
    /*case 1*/
    printf("1.lists that end at the same node\n");
    printf("first list: \n");
    PrintNodeInt(last1);
    printf("second list: \n");
    PrintNodeInt(last2);
    answer = SLLFindIntersection(last1, last2);
    end->next = NULL;
    printf("the shared node: \n");
    if(answer)
    {
    	PrintNodeInt(answer);
    	printf("\033[0;32msuccess\033[0m\n\n");
    }
    else
    {
    	printf("none \n");
    	printf("\033[1;31mfail\033[0m\n\n");
    }
    printf("\n");
    
    /*case 2*/
    printf("2. seperate lists\n");
    printf("first list: \n");
    PrintNodeInt(last1);
    printf("second list: \n");
    PrintNodeInt(last3);
    answer = SLLFindIntersection(last1, last3);
    printf("the shared node: \n");
    if(!answer)
    {
        printf("none \n");
        printf("\033[0;32msuccess\033[0m\n\n");
    }
    else
    {
    	PrintNodeInt(answer);
    	printf("\033[1;31mfail\033[0m\n\n");
    }
    printf("\n");
    
    /*case 3*/
    printf("3. same list\n");
    printf("first list: \n");
    PrintNodeInt(last1);
    printf("second list: \n");
    PrintNodeInt(last1);
    answer = SLLFindIntersection(last1, last1);
    printf("the list starts with the shared node: \n");
    if(answer)
    {
    	PrintNodeInt(answer);
    	printf("\033[0;32msuccess\033[0m\n\n");
    }
    else
    {
    	printf("none \n");
    	printf("\033[1;31mfail\033[0m\n\n");
    }
    SLLDestroy(last1);
    SLLDestroy(last2);
    SLLDestroy(last3);
}

/****************************************************************/

static void HasLoopTest()
{
	int array[] = {1, 2, 3, 4};
	int number = 7;
	sl_node_t *node = NULL;
	sl_node_t *node_loop = NULL;
	size_t i = 0;
	int answer = 0;
	printf("1. checking for a one node list\n");
	node_loop = SLLCreate(&number, NULL);
	node = SLLCreate(&array[0], node_loop);
	
	answer = SLLHasLoop(node);
	if(!answer)
	{
		printf("no loop\n");
		printf("\033[0;32msuccess\033[0m\n\n");
	}
	else
	{
		printf("loop \n");
		printf("\033[1;31mfail\033[0m\n\n");
	}
	
	printf("2. checking for a loop\n");
	for(i = 1; i < sizeof(array)/sizeof(int); ++i)
	{
		node = SLLCreate(&array[i], node);
	}
	node_loop->next = node->next;
	answer = SLLHasLoop(node);

	if(answer)
	{
		printf("has a loop\n");
		printf("\033[0;32msuccess\033[0m\n\n");
	}
	else
	{
		printf("no loop \n");
		printf("\033[1;31mfail\033[0m\n\n");
	}
	node_loop->next = NULL;
    printf("\n");
	SLLDestroy(node);
}

/*assistance function*/
static void PrintNodeInt(sl_node_t *node)
{
    if(node == NULL)
    {
        printf("none");
    }
    while(node != NULL)
    {
        printf("%d ",*(int*)node->data);
        node = node->next;
    }
    printf("\n");
}

/*for each functions*/
int Add(void *data, void* param)
{
    if(NULL == data && NULL == param)
    {
        return 1;
    }
    *(int*)data = *(int*)data + *(int*)param;
    return 0;
}

int PrintInt(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data)
    {
        return 1;
    }
    printf("%d -> ",*(int*)data);
    return 0;
}

int PrintChar(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data)
    {
        return 1;
    }
    printf("%c -> ",*(char*)data);
    return 0;
}

/*find functions*/
int IsMatchInt(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data && NULL == param)
    {
        return 0;
    }
    if(*(int*)data == *(int*)param)
    {
        return 1; /*equal*/
    }
    return 0;
}

int IsMatchChar(void *data, void* param)
{
    UNUSED(param);
    if(NULL == data && NULL == param)
    {
        return 0;
    }
    if(*(char*)data == *(char*)param)
    {
        return 1; /*equal*/
    }
    return 0;
}




