#include <stdio.h>

void PrintMessage();
float Power(float power_num);
int Flip(int num);
void swap(int *first, int *second);

int main()
{
    int power_num;
    int flip_num;
    int first, second;
    
    /*first function*/
    printf("the first function\n");
    PrintMessage();
    printf("\n");
    
    /*second function*/
    printf("the second function\n");
    printf("Enter a number to rase 10 by\n");
    scanf("%d",&power_num);
    printf("the result of the calculation is: %.2f\n",Power(power_num));
    printf("\n");
    
    /*third function*/
    printf("the third function\n");
    printf("enter a number to be flipped\n");
    scanf("%d",&flip_num);
    printf("the number that you entered: %d\n",flip_num);
    printf("the number after the flip: %d\n",Flip(flip_num));
    printf("\n");
    
    /*third function*/
    printf("Enter the first number out of the two to be swapped \n");
    scanf("%d", &first);
    printf("Enter the second number \n");
    scanf("%d", &second);
    printf("the first number: %d\n",first);
    printf("the second number: %d\n",second);
    swap(&first, &second);
    printf("after the swap: \n");
    printf("the first number: %d\n",first);
    printf("the second number: %d\n", second);
    
    return 0;
}

void PrintMessage()
{
    char hexline[] = {0x22,0x48,0x65,0x6c,0x6c,0x6f,0x20,
    0x57,0x6f,0x72,0x6c,0x64,0x21,0x22};
    int i;
    for(i=0; i<hexline[i];i++)
        printf("%c", hexline[i]);
    printf("\n");
}

float Power(float power_num)
{
    int i;
    float result=1.0;
    float base=10.0;
    
    /*if the entered number is negative*/
    if (power_num<0)
    {
        base=1/base;
        power_num=-power_num;
    }
    for (i=0; i<power_num; i++)
    {
        result*=base;
    }
    
    return result;
}

int Flip(int num)
{
    int res=0;
    
    while (num>0)
    {
        res*=10;
        res+=num%10;
        num/=10;
    }
    return res;
}
void swap(int *first, int *second)
{
    int temp;
    temp = *first;
    *first = *second;
    *second= temp; 
}


