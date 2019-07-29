#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* system */

int SwitchCaseWay();

int main()
{    
    printf("*******switch case*******\n\n");
    SwitchCaseWay(); 
    printf("\n\n");
    
    return 0;   
}

int SwitchCaseWay()
{
    char input = ' ';
    system("stty -icanon -echo"); /*turning off the terminal echoing*/
    printf("please enter A or T for printing, or ESC for escaping\n");
    
    while(1)
    {
        input = getchar(); /*user input*/
        switch(input)
        {
            case 'A':
            {
                printf("%c passed\n",input);
                break;
            }
            case 'T':
            {
                printf("%c passed\n",input);
                break;
            }
            case 27 : /*ASCII for ESC*/
            {
                system("stty icanon  echo"); /*turning the terminal 
                                                    echoing back on*/
                return 0;
            }
        
        }
    }
}
