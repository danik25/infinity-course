/*
Unit tests:
1. Create a new circular buffer:
    1.1 standard case.
    1.2 creation with 0 size capacity.
2. Write to the buffer:
    2.1 standard case.
    2.2 asking to write more than the word length.
    2.3 asking to write less than the word length.
    2.4 asking to write more than the capacity size.
4. Read from the buffer
    4.1 standard case.
    4.2 asking to read a size greater than source.
    4.3 read from empty buffer.
    4.4 asking to read a size greater than capacity.
5. Check if the buffer is empty
6. Get the free space for writing 

Intigration tests:

*/

#include <stdio.h> /*printf*/
#include <string.h> /*strlen*/
#include "cb.h"

/*main tests function*/
static void TestCircularBuffer();
/*creation tests*/
static void TestCreate();
static void TestCreateZero();
/*is empty tests*/
static void TestIsEmpty();
static void TestIsEmptyFull();
/*free space tests*/
static void TestFreeSpace();
/*writing tests*/
static void WriteTest();
static void WriteNumBiggerThanWord();
static void WriteNumSmallerThanWord();
static void WriteNumBiggerThanCapacity();
/*reading tests*/
static void ReadTest();
static void ReadAskedBiggerThanSrc();
static void ReadEmpty();
static void ReadAskedBiggerThanCap();

static void IntigrationTest();
static void test2();

int main()
{
    TestCircularBuffer();
    return 0;
}

static void TestCircularBuffer()
{
	
    printf("----------------creation tests----------------\n\n");
    TestCreate();
    /*TestCreateZero();*/
    printf("----------------is empty tests----------------\n\n");
    TestIsEmpty();
    TestIsEmptyFull();
    printf("----------------free space tests----------------\n\n");
    TestFreeSpace();
    printf("----------------writing tests----------------\n\n");
    WriteTest();
    WriteNumBiggerThanWord();
    WriteNumSmallerThanWord();
    WriteNumBiggerThanCapacity();
    printf("----------------reading tests----------------\n\n");
    ReadTest();
    ReadAskedBiggerThanSrc();
    ReadEmpty();
    ReadAskedBiggerThanCap();
    printf("----------------intigration tests----------------\n\n");
    IntigrationTest();
    test2();
}

/*---------------unit tests---------------*/
/****************creation tests****************/
static void TestCreate()
{
    size_t cap = 5;
    cb_t *my_buffer = CBCreate(cap);
    printf("********buffer creation********\n\n");
    
    (my_buffer) ? printf("successfull creation of a" 
                " new circular buffer\n\n") : printf("unable to" 
                "creat a new circular buffer\n");
    
    CBDestroy(my_buffer);
}

static void TestCreateZero()
{
    size_t cap = 0;
    cb_t *my_buffer = CBCreate(cap);
    printf("********no size creation********\n\n");
    
    (CBCapacity(my_buffer) == cap) ? printf("successfull creation of zero" 
                " size circular buffer\n\n") : printf("unable to" 
                "creat a new circular buffer\n");
    
    CBDestroy(my_buffer);
}

/****************writing tests****************/
static void WriteTest()
{
    size_t cap = 3;
    size_t wanted_size = 3;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "dog";
    size_t written = CBWrite(my_buffer, src, wanted_size);
    printf("********writing standard case********\n\n");
    printf("word: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked write size: %ld\n", wanted_size);
    if(written)
    {
        printf("the amount written is: %ld\n\n", written);
    }
    else
    {
        perror("error: ");
    }
                                    
    (wanted_size == written) ? printf("success\n\n") : printf("fail\n\n");      
    
    CBDestroy(my_buffer);
}

static void WriteNumBiggerThanWord()
{
    size_t cap = 3;
    size_t wanted_size = 4;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "dog";
    size_t written = CBWrite(my_buffer, src, wanted_size);
    printf("********the num asked is bigger than the word********\n\n");
    printf("word: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked write size: %ld\n", wanted_size);
    if(written)
    {
        printf("the amount written is: %ld\n\n", written);
    }
    else
    {
        perror("error: ");
    }
    (strlen(src) == written) ? printf("success\n\n") : printf("fail\n\n");
    CBDestroy(my_buffer);
}


static void WriteNumSmallerThanWord()
{
    size_t cap = 3;
    size_t wanted_size = 2;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "dog";
    size_t written = CBWrite(my_buffer, src, wanted_size);
    printf("********the num asked is smaller than the word********\n\n");
    printf("word: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked write size: %ld\n", wanted_size);
    if(written)
    {
        printf("the amount written is: %ld\n\n", written);
    }
    else
    {
        perror("error: ");
    }
                                    
    (wanted_size == written) ? printf("success\n\n") : printf("fail\n\n");
    CBDestroy(my_buffer);
}

static void WriteNumBiggerThanCapacity()
{
    size_t cap = 2;
    size_t wanted_size = 5;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "dog";
    size_t written = CBWrite(my_buffer, src, wanted_size);
    printf("********the num asked is bigger than" 
                                    " the capacity********\n\n");
    printf("word: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked write size: %ld\n", wanted_size);
    if(written)
    {
        printf("the amount written is: %ld\n\n", written);
    }
    else
    {
        perror("error: ");
    }
    (cap == written) ? printf("success\n\n") : printf("fail\n\n");
    CBDestroy(my_buffer);
}

/****************reading tests****************/
static void ReadTest()
{
    /*variables for the creation of the buffer*/
    size_t cap = 3;
    size_t wanted_size = 3;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "cat";
    
    size_t size_read = 3;
    char my_reader[3] = {0};
    size_t read = 0;
    
    /*buffer creation*/
    CBWrite(my_buffer, src, wanted_size);
    
    /*reading*/
    read = CBRead(my_buffer, my_reader, size_read);
    
    printf("********reading standard case********\n\n");
    printf("source: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked read size: %ld\n", size_read);
    if(read)
    {
        printf("the amount to read is: %ld\n\n", read);
    }
    else
    {
        perror("error: ");
    }         
    (wanted_size == read) ? printf("success\n\n") : printf("fail\n\n");                   
    printf("dest: '%s', (for convenience)\n\n", my_reader);
    CBDestroy(my_buffer);
}

static void ReadAskedBiggerThanSrc()
{
    /*variables for the creation of the buffer*/
    size_t cap = 3;
    size_t wanted_size = 3;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "cat";
    
    size_t size_read = 4;
    char my_reader[3] = {0};
    size_t read = 0;
    
    /*buffer creation*/
    CBWrite(my_buffer, src, wanted_size);
    
    /*reading*/
    read = CBRead(my_buffer, my_reader, size_read);
    
    printf("********reading asked size bigger than src size********\n\n");
    printf("source: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked read size: %ld\n", size_read);
    if(read)
    {
        printf("the amount to read is: %ld\n\n", read);
    }
    else
    {
        perror("error: ");
    }                           
    (strlen(src) == read) ? printf("success\n\n") : printf("fail\n\n");
    
    printf("dest: '%s', (for convenience)\n\n", my_reader);
    CBDestroy(my_buffer);

}

static void ReadEmpty()
{
    /*variables for the creation of the buffer*/
    size_t cap = 3;
    size_t wanted_size = 3;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "";
    
    size_t size_read = 4;
    char my_reader[3] = {0};
    size_t read = 0;
    
    /*buffer creation*/
    CBWrite(my_buffer, src, wanted_size);
    
    /*reading*/
    read = CBRead(my_buffer, my_reader, size_read);
    
    printf("********reading from empty src********\n\n");
    printf("source: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked read size: %ld\n", size_read);
    if(!read)
    {
        printf("the amount to read is: %ld\n\n", read);
    }
    else
    {
        perror("error: ");
    }                            
    (strlen(src) == read) ? printf("success\n\n") : printf("fail\n\n");
    
    printf("dest: '%s', (for convenience)\n\n", my_reader);
    CBDestroy(my_buffer);
}

static void ReadAskedBiggerThanCap()
{
    /*variables for the creation of the buffer*/
    size_t cap = 2;
    size_t wanted_size = 3;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "cat";
    
    size_t size_read = 3;
    char my_reader[3] = {0};
    size_t read = 0;
    
    /*buffer creation*/
    CBWrite(my_buffer, src, wanted_size);
    
    /*reading*/
    read = CBRead(my_buffer, my_reader, size_read);
    
    printf("********asked reading number is bigger than capacity********\n\n");
    printf("source: %s\n", src);
    printf("word size: %ld\n", strlen(src));
    printf("cap size: %ld\n", cap);
    printf("asked read size: %ld\n", size_read);
    if(read)
    {
        printf("the amount to read is: %ld\n\n", read);
    }
    else
    {
        perror("error:");
    }
                                
    (cap == read) ? printf("success\n\n") : printf("fail\n\n");
    
    printf("dest: '%s', (for convenience)\n\n", my_reader);
    CBDestroy(my_buffer);
}

/****************is empty tests****************/
static void TestIsEmpty()
{
    size_t cap = 5;
    cb_t *my_buffer = CBCreate(cap);
    int buffer_size = CBIsEmpty(my_buffer);
    printf("********empty size testing********\n\n");
    (buffer_size) ? printf("buffer is empty\n\n") : printf("not empty\n\n");
    (buffer_size == 1) ? printf("success\n\n") : printf("fail\n\n");
  
    CBDestroy(my_buffer);
}

static void TestIsEmptyFull()
{
    size_t cap = 9;
    cb_t *my_buffer = CBCreate(cap);
    char *src = "hipopotam";
    size_t wanted_size = 9;
    int buffer_size = 0;
    CBWrite(my_buffer, src, wanted_size);
    buffer_size = CBIsEmpty(my_buffer);
    printf("********not empty size testing********\n\n");
    (buffer_size) ? printf("buffer is empty\n\n") : printf("not empty\n\n");
    (buffer_size == 0) ? printf("success\n\n") : printf("fail\n\n");
  
    CBDestroy(my_buffer);
}

/****************free space tests****************/
static void TestFreeSpace()
{
    size_t cap = 5;
    cb_t *my_buffer = CBCreate(cap);
    printf("********empty buffer's free space testing********\n\n");
    printf("the free space for writing in a buffer with a capacity" 
                "size of: '%ld', is: %ld\n\n",cap, CBFreeSpace(my_buffer));
    CBDestroy(my_buffer);
}

/*---------------intigration tests---------------*/
static void IntigrationTest()
{
    size_t i = 0;
    size_t cap = 10;
    
    cb_t *my_buffer = CBCreate(cap);
    
    char *src = "abc";
    char dest[10] = {0};
    
    CBWrite(my_buffer, src, 5);
    printf("size is: %ld\n", cap - CBFreeSpace(my_buffer));

    CBRead(my_buffer, dest, 2);
    for(i = 0; i < cap/2 + 1; ++i)
    {
        printf("dest, in place %ld, is: %c\n", i, dest[i]);
        printf("size is: %ld\n", cap - CBFreeSpace(my_buffer));
    }
    (cap - CBFreeSpace(my_buffer) == 1) ? printf("success\n\n") : 
                                                    printf("fail\n\n");
    
    printf("inserting 12 more items:\n");
    CBWrite(my_buffer, src, 3);
    CBWrite(my_buffer, src, 3);
    CBWrite(my_buffer, src, 3);
    CBWrite(my_buffer, src, 3);
    
    printf("size is: %ld\n", cap - CBFreeSpace(my_buffer));
    (cap - CBFreeSpace(my_buffer) == 10) ? printf("success\n\n") : 
                                                    printf("fail\n\n");
    
    printf("capacity is: %ld\n", CBCapacity(my_buffer));
}

static void test2()
{
	size_t i = 0;
    size_t cap = 5;
    char *src = "x";
    char my_reader[5] = {0};
    cb_t *my_buffer = CBCreate(cap);
    size_t written = 0;
    size_t read = 0;
    size_t free_space = 0;
    for(i = 0; i < 3; ++i)
    {
    	written += CBWrite(my_buffer, src, 1);
    }
    for(i = 0; i < 2; ++i)
    {
    	read += CBRead(my_buffer, my_reader, 1);
    }
    for(i = 0; i < 10; ++i)
    {
    	written += CBWrite(my_buffer, src, 1);
    }
    printf("write- %lu \n", written);        
    free_space = CBFreeSpace(my_buffer); 
    printf("free space: %lu \n", free_space);
}


