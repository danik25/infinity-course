/****************************************************************
*                         calculator- state machine
*                       ==============================
* File Name: SMCal_test.c
* Related files: SMCal.h, SMCal.c
* #Version: V 1.1
* Writer: Dani Benjamin                         
* Reviewer: Ofer Tauber 
* Last update: 23/05/19
****************************************************************/

# include <stdio.h>
# include "SMCal.h"

#define GREEN(str)      printf("\033[1;32m%s\033[0m\n", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)

static void GenerateExp();
static void CalculatorTest();

int main()
{
    GenerateExp();
    return (1);
}

static void GenerateExp()
{
    char * exp1 = "16-5*4+13";
    char * exp2 = "  17  \n-5* 4+13";
    char * exp3 = "  18a +13";
    char * exp4 = "  1 +13/0";
    char * exp5 = "  12 ++ 4";
    char * exp6 = "  19\n-8 +    15/3*2-9   +16/18/19      ";
    char * exp7 = "2+2^3*9-3";

    double ans1 = 9;
    double ans2 = 10;
    double ans3 = 0;
    double ans4 = 1.0 / 0.0;
    double ans5 = 0;
    double ans6 = 19.0-8.0+15.0/3.0*2.0-9.0+16.0/18.0/19.0;
    double ans7 = 71;

    CalculatorTest(exp1, ans1);
    CalculatorTest(exp2, ans2);
    CalculatorTest(exp3, ans3);
    CalculatorTest(exp4, ans4);
    CalculatorTest(exp5, ans5);
    CalculatorTest(exp6, ans6);
    CalculatorTest(exp7, ans7);
}

static void CalculatorTest(char *exp, double ans)
{
    cal_t *cal = SMCalculator(exp);
    printf("%s\n", exp);
    printf("answer: %.2f\n", cal->answer);
    printf("message: %s\n", cal->message);
    (cal->answer == ans) ? GREEN("success") : RED("fail");
    printf("\n");
}