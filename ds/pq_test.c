/****************************************************************
*                <<<<<<<< new pq >>>>>>>>              *
* Related files: Priority.c, Priority_test.c                    *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: MOshe Greenberg                                          *
* Last update: 17/04/19                                         *
****************************************************************/   

#include <stdio.h> /*printf*/

#include "colours.h"
#include "pq.h"

/*
Sort list tests:
1. CreateTest 
2. EnqueueTest
3. PQDequeue 
    3.1 PQDequeue empty list
4. PQPeek
    4.1 peek on empty list
    4.2 peek on full list
5. PQIsEmpty
    5.1 empty list
    5.2 full list
6. PQSize
    6.1 size on empty list
    6.2 size iteration on filling list
7. PQClear
8. PQRemove
    8.1 remove unexisting element
    8.2 existing element
*/

/*compare function*/
int QIsBefor(void *data1, void *data2, void* param);
/*find functions*/
int QIsMatchInt(void *data, void* param);

static void CreateTest();
static void EnqueueTest();
static void PQDequeueTest();
static void PQPeekTest();
static void PQIsEmptyTest();
static void PQSizeTest();
static void PQClearTest();
static void PQRemoveTest();

int main()
{
    CYAN("\n\n\t\t\t~TEST FILE FOR PRIORITY QUEUE~");
    CYAN("\t\t\t\tDani Benjamin\n\n");
    YELLOW("********Creation test********\n");
    CreateTest();
    YELLOW("********Enqueue test********\n");
    EnqueueTest();
    YELLOW("********Dequeue test********\n");
    PQDequeueTest();
    YELLOW("********Peek test********\n");
    PQPeekTest();
    YELLOW("********Is Empty test********\n");
    PQIsEmptyTest();
    YELLOW("********Size test********\n");
    PQSizeTest();
    YELLOW("********Clear test********\n");
    PQClearTest();
    YELLOW("********Remove test********\n");
    PQRemoveTest();
    CYAN("\n\n\t\t\t\t~THE END~\n\n");

    return(0);
}

static void CreateTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    (queue) ? GREEN("success") : RED("fail");
    printf("\n");
    PQDestroy(queue);
}

static void EnqueueTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {6, 5, 4, 3, 2, 1};
    int exp[] = {1, 2, 3, 4, 5, 6};
    size_t i = 0;
    size_t size = sizeof(data)/sizeof(int);
    int status = 0;

    for(i = 0; i < size && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
        if(*(int*)PQPeek(queue) != exp[size - i - 1])
        {
            status = 1;
        }
    }

    (!status) ? GREEN("success") : RED("fail");
    printf("\n");
    PQDestroy(queue);
}

static void PQDequeueTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    int exp[] = {1, 2, 3, 4, 5, 6, 6};
    size_t i = 0;
    int status = 0;
    PURPLE("1. dequeue empty list:");
    (!PQDequeue(queue)) ? GREEN("success") : RED("fail");

    /*filling the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
    }
    /*dequeueing the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        if(exp[i] != *(int*)PQDequeue(queue))
        {
            status = 1;
        }
    }
    PURPLE("\n2. dequeue on dequeueing list:");
    (!status) ? GREEN("success") : RED("fail");
    printf("\n");
    PQDestroy(queue);
}

static void PQPeekTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    size_t i = 0;
    int status = 0;

    PURPLE("1. peek on empty list:");
    (!PQPeek(queue)) ? GREEN("success") : RED("fail");

    PURPLE("\n2. peek on full list:");
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
    }

    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        if(*(int*)PQPeek(queue) != *(int*)PQDequeue(queue))
        {
            status = 1;
        }
    }
    (!status) ? GREEN("success") : RED("fail");
    printf("\n");
    PQDestroy(queue);
}

static void PQIsEmptyTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    size_t i = 0;
    int status = 0;

    PURPLE("1. is empty on empty list:");
    (PQIsEmpty(queue)) ? GREEN("success") : RED("fail");

    /*filling the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
    }

    PURPLE("\n2. is empty on full list:");
    (!PQIsEmpty(queue)) ? GREEN("success") : RED("fail");

    printf("\n");
    PQDestroy(queue);
}

static void PQSizeTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    size_t i = 0;
    int status = 0;

    PURPLE("1. size on empty list:");
    (!PQSize(queue)) ? GREEN("success") : RED("fail");

    /*filling the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
        if(PQSize(queue) != i + 1)
        {
            status = 1;
        }
    }
    PURPLE("\n2. size iteration on filling list:");
    (!status) ? GREEN("success") : RED("fail");

    printf("\n");
    PQDestroy(queue);
}

static void PQClearTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    size_t i = 0;
    int status = 0;

    /*filling the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
        if(PQSize(queue) != i + 1)
        {
            status = 1;
        }
    }
    (!PQIsEmpty(queue)) ? printf("not empty list:\n") : RED("fail\n");
    printf("after 'clear':");
    PQClear(queue);
    (PQIsEmpty(queue)) ? printf("empty\n") : RED("not empty\n");
    (PQIsEmpty(queue)) ? GREEN("success") : RED("fail");

    printf("\n");
    PQDestroy(queue);

}

static void PQRemoveTest()
{
    void* param = NULL;
    pqueue_t *queue = PQCreate(QIsBefor, param);
    int data[] = {2, 4, 6, 1, 5, 3, 6};
    int unexisting_data = 7;
    int exp[] = {1, 2, 3, 5, 6, 6};
    size_t i = 0;
    int status = 0;
    void * ans = NULL;

    /*filling the list*/
    for(i = 0; i < sizeof(data)/sizeof(int) && status == 0; ++i)
    {
        PQEnqueue(queue, &data[i]);
    }

    PURPLE("1. removing unexisting element:");
    ans = PQRemove(queue, QIsMatchInt, &unexisting_data);
    (!ans) ? GREEN("success") : RED("fail");

    PURPLE("\n2. removing existing element:");
    ans = PQRemove(queue, QIsMatchInt, &data[1]);
    /*dequeueing the list*/
    for(i = 0; i < sizeof(exp)/sizeof(int) && status == 0; ++i)
    {
        if(exp[i] != *(int*)PQPeek(queue))
        {
            status = 1;
        }
        printf("%d -> ",*(int*)PQDequeue(queue));
    }
    printf("\n");
    (ans && !status) ? GREEN("success") : RED("fail");
    printf("\n");
    PQDestroy(queue);
}

/************************user functions************************/
/*compare functions*/
int QIsBefor(void *data1, void *data2, void* param)
{
    /*UNUSED(param);*/
    if(*(int*)data1 < *(int*)data2)
    {
        return (1);
    }
    return (0);
}

/*find functions*/
int QIsMatchInt(void *data, void* param)
{
    /*UNUSED(param);*/
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
