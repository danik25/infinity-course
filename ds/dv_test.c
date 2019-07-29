#include <stdio.h> /* size_t */
#include <assert.h> /* assert */

#include "dv.h"

static void VectorTest();
/****Create tests****/
static void TestCreate(dv_t *vector);
/****Push tests****/
static void TestPushInt();
/****Peek tests****/
static void TestPeekInt();
/****Pop tests****/
static void TestPop();
/****Get Item Address tests****/
static void TestGetItemAddressInt();
/****Reserve tests****/
static void TestReserveSmall();
static void TestReserveBigger();
/****Destroy tests****/
static void TestDestroy(dv_t *vector);
/****Capacity tests****/
static void TestCapacity();
/****Size tests****/
static void TestEmptySize();

int main()
{
    VectorTest();
    return 0;
}

static void VectorTest()
{
    size_t size = 4;
    size_t amount = 1;
    
    dv_t *my_vector = NULL;

    my_vector = DVCreate(amount, size);
    TestCreate(my_vector);
    
    printf("capcity: %ld\n\n", DVCapacity(my_vector));
    
    TestPushInt();
  
    TestPeekInt();
    
    TestGetItemAddressInt();
    
    printf("\n");
   
    TestPop();
    TestReserveSmall();
    TestReserveBigger();
    TestCapacity();
    TestEmptySize();
    
    DVDestroy(my_vector);
}

/******************Create tests******************/
static void TestCreate(dv_t *vector)
{
    assert(vector);
    if(vector)
    {
        printf("successfull creation of a new vector\n\n");
    }
    else
    {
        printf("unable to creat a new vector\n");
    }
}

/******************Push tests******************/
static void TestPushInt()
{
    int element = 20;
    size_t i = 0;
    size_t size = 4;
    size_t amount = 1;
    
    dv_t *my_vector = DVCreate(amount, size);

    printf("****pushing test****\n\n");
    for (i = 0; i < 4; ++i)
    {
        if (0 == DVPushBack(my_vector, &element))
        {
            printf("successfull push of element: %d\n", element);
            printf("capacity: %ld\n",DVCapacity(my_vector));
            printf("size: %ld\n\n",DVSize(my_vector));
        }
        else
        {
            printf("unsuccessfull allocation of new memory\n\n");
        }
        element += 1;
    }
    TestDestroy(my_vector);
}

/******************Peek tests******************/
static void TestPeekInt()
{
    size_t size = 4;
    size_t amount = 1;
    dv_t *my_vector = DVCreate(amount, size);
    
    size_t i = 0;
    int element = 20;
    void * ans = NULL;
    size_t vector_size = 0;
    /*filling the vector*/
    for (i = 0; i < 4; ++i)
    {
        DVPushBack(my_vector, &element);
        ++element;
    }
    vector_size = DVSize(my_vector);
    printf("****peeking test****\n\n");
    for (i = 0; i < vector_size; ++i)
    {
        ans = DVGetItemAddress(my_vector, i);
        printf("the element in index: %ld, is:%d\n\n",i, *(int*)ans);
    }
    /*peeking at empty indexes*/
    for (i = vector_size; i < vector_size + 2; ++i)
    {
        ans = DVGetItemAddress(my_vector, i);
        printf("the element in index: %ld, is:%p\n\n",i, ans);
    }
    TestDestroy(my_vector);
}

/******************Size tests******************/
static void TestEmptySize()
{
    size_t size = 4;
    size_t amount = 0;
    dv_t *my_vector = DVCreate(amount, size);
    
    printf("****checking the size of an empty vector****\n\n");
    
    TestCreate(my_vector);
    
    printf("the current size of the vector is: %ld\n\n",DVSize(my_vector));
    
    TestDestroy(my_vector);
}

/******************Pop tests******************/
static void TestPop()
{
    size_t size = 4;
    size_t amount = 1;
    int element = 20;
    dv_t *my_vector = DVCreate(amount, size);
    
    size_t size_vector = 0;
    size_t i = 0;
    printf("****checking pop****\n\n");
    /*filling the vector*/
    for (i = 0; i < 4; ++i)
    {
        DVPushBack(my_vector, &element);
        ++element;
    }
    size_vector = DVSize(my_vector);
    for ( i = 0; i < size_vector + 2; ++i)
    {
        DVPopBack(my_vector);
        printf("pop number: %ld\n\n",i + 1);
        printf("capacity: %ld\n\n",DVCapacity(my_vector));
        printf("size: %ld\n\n",DVSize(my_vector));   
    }
    TestDestroy(my_vector);
}

/******************Get item tests******************/
static void TestGetItemAddressInt()
{
    size_t size = 4;
    size_t amount = 1;
    int element = 20;
    dv_t *my_vector = DVCreate(amount, size);
    
    size_t index = 0;
    size_t size_vector = DVSize(my_vector);
    void * ans = NULL;
    printf("****checking get item address****\n\n");
    
    for (index = 0; index < 4; ++index)
    {
        DVPushBack(my_vector, &element);
        ++element;
    }
    
    for ( index = 0; index < size_vector + 2; ++index)
    {
        if(DVGetItemAddress(my_vector, index))
        {
            ans = DVGetItemAddress(my_vector, index);
            printf("the element at index: %ld, is: %d: \n", index, *(int*)ans);
        }
        else
        {
            printf("index %ld, is invalid index\n", index);
        }
    } 
    TestDestroy(my_vector);
    printf("\n"); 
}

/******************Reserve item tests******************/
static void TestReserveSmall()
{
    size_t size = 4;
    size_t amount = 2;
    dv_t *my_vector = DVCreate(amount, size);
    printf("****checking reserve for a smaller size than init****\n\n");
    TestCreate(my_vector);
    printf("original  capacity: %ld\n\n", amount);
    printf("requested  capacity: %ld\n\n", amount - 1);
    printf("size: %ld\n\n", DVSize(my_vector));
    
    if(!DVReserve(my_vector, amount - 1)) /* success */
    {
        printf("successfull allocation of new memory\n\n"); 
    }
    else
    {
        printf("fail of reserve function\n\n");
    }
    
    TestDestroy(my_vector);
}

static void TestReserveBigger()
{
    size_t size = 4;
    size_t amount = 0;
    dv_t *my_vector = DVCreate(amount, size);
    printf("****checking reserve for a bigger size than init****\n\n");
    TestCreate(my_vector);
    printf("original  capacity: %ld\n\n", amount);
    printf("requested  capacity: %ld\n\n", amount + 1);
    printf("size: %ld\n\n", DVSize(my_vector));
    
    if(0 == DVReserve(my_vector, size + 1)) /* success */
    {
        printf("successfull allocation of new memory\n\n");
    }
    else
    {
        printf("fail of reserve function\n\n");
    }
    TestDestroy(my_vector);
}

/******************Destroy item tests******************/
static void TestDestroy(dv_t *vector)
{
    assert(vector);
    DVDestroy(vector);
}

/******************Capacity item tests******************/
static void TestCapacity()
{
    size_t size = 4;
    size_t amount = 2;
    int element = 20;    
    size_t i = 0;
        dv_t *my_vector = DVCreate(amount, size);
    printf("****checking capacity****\n\n");
    TestCreate(my_vector);
    
    for (i = 0; i < 4; ++i)
    {
        if (!DVPushBack(my_vector, &element))
        {
            printf("successfull push of element: %d\n", element);
        }
        else
        {
            printf("unsuccessfull allocation of new memory\n\n");
        }
        element += 1;
    }
    
    printf("capacity: %ld\n\n",DVCapacity(my_vector));
    TestDestroy(my_vector);
}



