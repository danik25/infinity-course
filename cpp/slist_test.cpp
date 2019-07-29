/****************************************************************
*                              Slist
*                       =====================
* File Name: slist_test.cpp
* Related files: slist.hpp slist.cpp
* #Version: V 1.0
* Writer: Dani Benjamin     
* Reviewer: Tom Valershtein     
* Last update: 22/07/19
****************************************************************/

#include <stdio.h> /* printf */

#include "slist.hpp"
#include "dani_utilities.h"

using namespace hrd9;

void push_front_test();
void pop_front_test();
void peek_test();
void size_test();
void is_empty_test();

int main()
{
    YELLOW("\tpush front test\n");
    push_front_test();
    YELLOW("\n\tpop front test\n");
    pop_front_test();
    YELLOW("\n\tpeek test\n");
    peek_test();
    YELLOW("\n\tsize test\n");
    size_test();
    YELLOW("\n\tis empty test\n");
    is_empty_test();

    return(0);
}

void push_front_test()
{
    int array[] = {1, 2, 3, 4};
    size_t size = sizeof(array) / sizeof(int);
    size_t i = 0;
    Slist obj;
    int status = 0;

    for(i = 0; i < size; ++i)
    {
        obj.push_front(array[i]);
        if(obj.size() != i + 1)
        {
            status = 1;
        }
    }

    TEST(0 == status);
}

void pop_front_test()
{
    int array[] = {1, 2, 3, 4};
    size_t size = sizeof(array) / sizeof(int);
    size_t i = 0;
    Slist obj;
    int status = 0;

    for(i = 0; i < size; ++i)
    {
        obj.push_front(array[i]);
    }
    PURPLE("1. pop the list\n");
    for(i = 0; i < size; ++i)
    {
        if(obj.peek_head() != array[size - i - 1])
        {
            status = 1;
        }
        printf("poped: %d\n", obj.peek_head());
        obj.pop_front();
    }
    TEST(0 == status);

    PURPLE("\n2. pop on an empty list\n");
    obj.pop_front();
    TEST(0 == status);

    PURPLE("\n3. checking if the list is empty\n");
    if(true != obj.is_empty())
    {
        status = 1;
    }

    TEST(0 == status);
}

void peek_test()
{
    int array[] = {1, 2, 3, 4};
    size_t size = sizeof(array) / sizeof(int);
    size_t i = 0;
    Slist obj;
    int status = 0;

    PURPLE("1. peeking on empty list\n");
    {
        if(0 != obj.peek_head())
        {
            status = 1;
        }
    }
    TEST(0 == status);

    PURPLE("\n2. filling the list\n");
    for(i = 0; i < size; ++i)
    {
        obj.push_front(array[i]);
        if(array[i] != obj.peek_head())
        {
            status = 1;
        }
    }
    TEST(0 == status);

    PURPLE("\n3. poping the list\n");
    for(i = 0; i < size; ++i)
    {
        if(array[size - i - 1] != obj.peek_head())
        {
            status = 1;
        }
        obj.pop_front();
    }
    TEST(0 == status);
}

void size_test()
{
    int array[] = {1, 2, 3, 4};
    size_t size = sizeof(array) / sizeof(int);
    size_t i = 0;
    Slist obj;
    int status = 0;

    PURPLE("1. size of an empty list\n");
    {
        if(0 != obj.size())
        {
            status = 1;
        }
    }
    TEST(0 == status);

    PURPLE("\n2. filling the list\n");
    for(i = 0; i < size; ++i)
    {
        obj.push_front(array[i]);
        if(i + 1 != obj.size())
        {
            status = 1;
        }
    }
    TEST(0 == status);

    PURPLE("\n3. poping the list\n");
    for(i = 0; i < size; ++i)
    {
        if(size - i != obj.size())
        {
            status = 1;
        }
        obj.pop_front();
    }
    TEST(0 == status);
}

void is_empty_test()
{
    int data = 1;
    Slist obj;

    PURPLE("1. empty list\n");
    TEST(true == obj.is_empty());

    PURPLE("2. not empty list\n");
    obj.push_front(data);
    TEST(true != obj.is_empty());
}