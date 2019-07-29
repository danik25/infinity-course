#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* system */

int IfElseWay();

int main()
{
    printf("*******if else*******\n\n");
    IfElseWay(); 
    printf("\n\n");
    
    return 0;   
}

int IfElseWay()
{
    char input = ' ';
    system("stty -icanon -echo"); /*turning off the terminal echoing*/
    printf("please enter A or T for printing, or ESC for escaping\n");
    
    
    while (1)
    {
        input = getchar();  /*user input*/
        if (input == 'T' || input == 'A')
        {
            printf("%c passed\n",input);
        }
        else if (input == 27 ) /*ASCII for ESC*/
        {
            system("stty icanon  echo"); /*turning the terminal 
                                                    echoing back on*/
            return 0;
        }
    } 
}










