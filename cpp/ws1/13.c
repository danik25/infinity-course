#include <stdio.h>



int main()
{
    const int variable = 3;
    /*int var2 = variable;*/
  
    int *ip = (int*)&variable;
    *ip = 5;

    printf("%d %d\n", variable, *ip);

    return(0);
}