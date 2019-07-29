/****************************************************************
*                   Knights Tour
* file: knight_test.c
* Related files: knight.c knight_test.h
* #Version: V 1.0
* Writer: Dani Benjamin
* Reviewer: Idan Argaman
* Last update: 15/06/19
***************************************************************/
#include "knight.h"
#include "dani_utilities.h"

static void KnightTest();

int main()
{
    KnightTest();

    return(0);
}

static void KnightTest()
{
    KnightTour(0);
}
