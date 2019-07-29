#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* system */

int LUT();
int TFunction();
int AFunction();
int EscFunction();
int OtherLettersFunction();

int main()
{    
    printf("*******LUT*******\n\n");
    LUT(); 
    printf("\n\n");
    
    return 0;   
}

int LUT()
{
    int answer;
    int i;
    unsigned char input;
    
    int (*PointerArray[256])();
 
    for (i = 0; i < 256; i++) /*assigning all the places with default
                                                        function*/
    {
        PointerArray[i] = &OtherLettersFunction;
    }
    PointerArray[27] = &EscFunction; /*ASCII for ESC*/
    PointerArray[84] = &TFunction; /*ASCII for T*/
    PointerArray[65] = &AFunction; /*ASCII for A*/
    
    system("stty -icanon -echo"); /*turning off the terminal echoing*/
    printf("please enter A or T for printing, or ESC for escaping\n");
    while(1)
    {
        input = getchar(); /*user input*/
        answer = PointerArray[input]();
        if ( 0 == answer) /*if the ESC function was triggered*/
        {
            return 0;
        }
    }     
}

int TFunction()
{
    printf("T passed\n");
    return 1;
}
int AFunction()
{
    printf("A passed\n");
    return 1;
}
int EscFunction()
{
    system("stty icanon  echo"); /*turning the terminal 
                                                 echoing back on*/
    return 0;
}
int OtherLettersFunction()
{
    return 1;
}
