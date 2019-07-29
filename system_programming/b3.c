#include <stdio.h>
#include "b3.h"
#include "a3.h"

void BPrintNum()
{
    printf("number, calling through b\n");
    APrintNum();
}

void BPrintLetter()
{
    printf("number, calling through b\n");
    APrintLetter();
}
