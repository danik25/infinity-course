/****************************************************************
*                Data Structures - Queue                        *
* Related files: queue.c, queue_test.c                          *
* #Version: V 1.2                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Lev Shubert                                         *
* Last update: 10/04/19                                         *
****************************************************************/

#include <stdio.h>
#include "queue.h" 
#include "sl_list.h"

/*
1. creation test
2. Enqueue test
3. Dequeue test
    3.1 Denqueue all the element
    3.2 Denqueue empty queue
4. Peek test
    4.1 peeking at an empty queue
    4.2 peeking at a full queue
5. Size test
6. Is Empty test
    6.1 empty queue
    6.2 full queue
7. Append test
    7.1 appending two empty queues
    7.2 appending empty queue to full one
    7.3 appending full queue to an empty one
    7.4 appending two full queues
    
8. integration test
*/

static void QCreateTest();
static void QEnqueueTest();
static void QDequeueTest();
static void QPeekTest();
static void QSizeTest();
static void QIsEmptyTest();
static void QAppendTest();

static void IntegrationTest();

static void PrintQueueInt(queue_t *queue);
int main()
{
    printf("\n********creation test********\n\n");
    QCreateTest();
    printf("********enqueue test********\n\n");
    QEnqueueTest();
    printf("********Dequeue test********\n\n");
    QDequeueTest();
    printf("********Peek test********\n\n");
    QPeekTest();
    printf("********Size test********\n\n");
    QSizeTest();
    printf("********Is Empty test********\n\n");
    QIsEmptyTest();
    printf("********Append test********\n\n");
    QAppendTest();
    
    printf("=============Integration test=============\n\n");
    IntegrationTest();
    return 0;
}

static void QCreateTest()
{
    queue_t *queue = QCreate();
    (queue) ? printf("\033[0;32msuccessfull creation\033[0m\n\n") : 
                            printf("\033[1;31mfail to create\033[0m\n\n");
    QDestroy(queue);
}

static void QEnqueueTest()
{
    int data[] = {1, 2, 3, 4};
    size_t i = 0;
    size_t size = 0;
    queue_t *queue = QCreate();
    /* filling queue */
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		QEnqueue(queue, &data[i]);
	}
	size = QSize(queue);
	
	(size == sizeof(data)/sizeof(int)) ? 
	        printf("\033[0;32msuccessfull Enqueue\033[0m\n\n") : 
	            printf("\033[1;31mfailed Enqueue\033[0m\n\n");
	            
	PrintQueueInt(queue);
	QDestroy(queue);
}

static void QDequeueTest()
{
    int data[] = {1, 2, 3, 4};
    int status = 0;
    size_t i = 0;
    size_t size = 0;
    queue_t *queue = QCreate();
    size = sizeof(data)/sizeof(int);
    
    /* filling queue */
	for(i = 0; i < size; ++i)
	{
		QEnqueue(queue, &data[i]);
	}
	
	i = 0;
	printf("1. Denqueue all the element: \n");
	while(0 == status && size > 0)
    {
	   if(!(*(int*)QDequeue(queue) == data[i] && QSize(queue) + 1 == size))
	   {
	        printf("\033[1;31mfailed Denqueue\033[0m\n\n");
	        status = 1;
	   }
	   ++i, --size;
	}
	if (0 == status)
	{ 
	    printf("\033[0;32msuccessfull Denqueue\033[0m\n\n");
	}
	
	printf("2. Denqueue empty queue: \n");
	(NULL == QDequeue(queue)) ? 
	        printf("\033[0;32mempty, success\033[0m\n\n") : 
	                printf("\033[1;31mfail\033[0m\n\n");
	QDestroy(queue);
}

static void QPeekTest()
{
    int data[] = {1, 2, 3, 4};
    int status = 0;
    size_t i = 0;
    queue_t *queue = QCreate();
    printf("1. peeking at an empty queue \n");
    (!QPeek(queue)) ? printf("\033[0;32mempty, success\033[0m\n\n") : 
                                        printf("\033[1;31mfail\033[0m\n\n");
    /* filling queue */
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		QEnqueue(queue, &data[i]);
	}
	printf("2. peeking at a full queue \n");
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
	    if(QPeek(queue) != QDequeue(queue))
	    {
	        status = 1;
	    }
	}
	(status) ? printf("\033[1;31mfailed Peek\033[0m\n\n") : 
	                        printf("\033[0;32msuccessfull Peek\033[0m\n\n");
	
	QDestroy(queue);
}

static void QSizeTest()
{
    int data[] = {1, 2, 3, 4};
    int status = 0;
    size_t i = 0;
    queue_t *queue = QCreate();
 
    if(QSize(queue) != i)
    {
        status = 1;
    }
    /* filling queue */
	for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		QEnqueue(queue, &data[i]);
		if(QSize(queue) != i + 1)
        {
            status = 1;
        }
	}
	/* emptying queue */
	for(; i > 0; --i)
	{
		QDequeue(queue);
		if(QSize(queue) != i - 1)
        {
            status = 1;
        }
	}
	(status) ? printf("\033[1;31mfailed Size\033[0m\n\n") : 
	                        printf("\033[0;32msuccessfull Size\033[0m\n\n");
	QDestroy(queue);
}

static void QIsEmptyTest()
{
    int data[] = {1, 2, 3, 4};
    size_t i = 0;
    queue_t *queue = QCreate();
    
    printf("cheking empty queue: \n");
    QIsEmpty(queue) ? printf("\033[0;32msuccess\033[0m\n\n") : 
                                printf("\033[1;31mfail\033[0m\n\n");
    
    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
	{
		QEnqueue(queue, &data[i]);
	}
	
	printf("cheking full queue: \n");
    (!QIsEmpty(queue)) ? printf("\033[0;32msuccess\033[0m\n\n") : 
                                    printf("\033[1;31mfail\033[0m\n\n");
    
    QDestroy(queue);
}

static void QAppendTest()
{
    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8, 9};
    
    size_t size1 = 0;
    
    size_t i = 0;
    
    queue_t *queue1 = QCreate();
    queue_t *queue2 = QCreate();
    queue_t *queue3 = QCreate();
    queue_t *queue4 = QCreate();
    
    /* case 1 */
    printf("1. appending two empty queues\n");
    queue1 = QAppend(queue1, queue2);
    QIsEmpty(queue1) ? printf("\033[0;32msuccess\033[0m\n\n") : 
                                printf("\033[1;31mfail\033[0m\n\n");
    
    /* case 2 */
    queue2 = QCreate();
    printf("2. appending empty queue to full one\n");
    for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		QEnqueue(queue1, &data1[i]);
	}
	size1 = QSize(queue1);
	queue1 = QAppend(queue1, queue2);
	(size1 = QSize(queue1)) ? printf("\033[0;32msuccess\033[0m\n\n") : 
	                            printf("\033[1;31mfail\033[0m\n\n");
	
	/* case 3 */
	printf("3. appending full queue to an empty one\n");
	size1 = QSize(queue1);
	queue4 = QAppend(queue4, queue1);
	(size1 = QSize(queue4)) ? printf("\033[0;32msuccess\033[0m\n\n") : 
	                                printf("\033[1;31mfail\033[0m\n\n");
	
	/* case 4 */
	printf("4. appending two full queues\n");
	for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		QEnqueue(queue3, &data2[i]);
	}
	size1 = QSize(queue3) + QSize(queue4);
	queue3 = QAppend(queue3, queue4);
	(size1 = QSize(queue3)) ? printf("\033[0;32msuccess\033[0m\n\n") : 
	                                printf("\033[1;31mfail\033[0m\n\n");
	
	QDestroy(queue3);
}

static void IntegrationTest()
{
    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};
    size_t i = 0;
    queue_t *queue1 = QCreate();
    queue_t *queue2 = QCreate();
    int status = 0;
    void *removed = NULL;
    void *peeked = NULL;
    (queue1) ? printf("\033[0;32msuccessfull creation\033[0m\n") : 
                            printf("\033[1;31mfail to create\033[0m\n");
    /*trying to remove from empty queue*/
    if(!QDequeue(queue1))
    {
    	printf("\033[0;32msuccess, queue empty\033[0m\n");
    }
    else
    {
    	printf("\033[1;31mfail\033[0m\n");
    }
    
    status = QEnqueue(queue1, &data1[i]);
    (!status) ? printf("\033[0;32msuccessfull push\033[0m\n") : 
                            printf("\033[1;31mfail to push\033[0m\n");
    peeked = QPeek(queue1);
    
    (peeked) ? printf("\033[0;32mpeeked: %d\033[0m\n", *(int*)peeked) :     
                             printf("\033[1;31mfail too peek\033[0m\n");
    removed = (int*)QDequeue(queue1);
    if(*(int*)removed)
    {
    	printf("\033[0;32msuccess, removed item: %d\033[0m\n", 
    	                            *(int*)removed);
    }
	printf("filling the queue\n");
	/* filling queue number 1 */
	for(i = 0; i < sizeof(data1)/sizeof(int); ++i)
	{
		QEnqueue(queue1, &data1[i]);
	}
	/* filling queue number 2 */
	for(i = 0; i < sizeof(data2)/sizeof(int); ++i)
	{
		QEnqueue(queue2, &data2[i]);
	}
	
	queue1 = QAppend(queue1, queue2);
	
	printf("queue:\n");
	PrintQueueInt(queue1);
	
    QDestroy(queue1);
}

static void PrintQueueInt(queue_t *queue)
{
	queue_t *queue_copy = NULL;
	size_t size = 0;
	queue_copy = queue;
	size = QSize(queue_copy);
    while(size > 0)
    {
        printf("%d <-",*(int*)QPeek(queue_copy));
        QDequeue(queue_copy); 
        --size;
    }
    printf("DEADBEEF\n\n");
}


