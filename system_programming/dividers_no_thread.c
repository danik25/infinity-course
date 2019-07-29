#include <stdio.h> /* printf */

static size_t SumOfDivisorsChecker(size_t number);

int main()
{
    size_t num = 2000000000;

    printf("loop way: %ld\n", SumOfDivisorsChecker(num));
    
    return(0);
}


static size_t SumOfDivisorsChecker(size_t number)
{
    size_t i = 1;
    size_t sum = 0;
    for (i = 1; i <= number; ++i)
    {
        if(number % i == 0)
        {
            sum += i;
        }   
    }
    return(sum);
}