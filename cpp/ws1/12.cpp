#include <iostream>
#include <stdio.h>


void Foo();
void Foo(int i);
void Foo(char a);

int main()
{
    float a = 6.5;
    int x = 6;
    Foo(a);
    return(0);
}

void Foo()
{
    printf("no arguments\n");
}

void Foo(int i)
{
    printf("ints\n");
}

void Foo(char a)
{
    printf("chars\n");
}