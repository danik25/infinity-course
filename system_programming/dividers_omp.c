#include <stdio.h> /* printf */
#include <pthread.h> /* pthread_create */
#include <stdlib.h> /* malloc */
#include <omp.h> /* openmp */

#include "dani_utilities.h"

size_t sum_of_dividors = 0;

int main()
{
    size_t num = 1234567891;
    size_t i = 0;

    #pragma omp parallel for reduction (+:sum_of_dividors)
    
    for(i = 1; i <= num; ++i)
    {
        if(num % i == 0)
        {
            sum_of_dividors += i;
        }
    }

    #pragma omp barrier
    
    printf("thread: %lu\n", sum_of_dividors);
    return(0);
}


