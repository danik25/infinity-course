/****************************************************************
*                Counting Sort Multi thread
* file: counting_sort_mt_test.c
* Related files: counting_sort_mt.c, counting_sort_mt.h
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Lev Shubert
* Last update: 01/07/19
****************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */

#include "counting_sort_mt.h"
#include "dani_utilities.h"

#define DICT_PATH "/usr/share/dict/american-english"
#define MULTIPLE 1000

static void SortMTTest();
static unsigned char* CreateArray(size_t size);
static size_t DictSize();

int main()
{
    SortMTTest();
    return(0);
}

static void SortMTTest()
{
    size_t size = 0;
    int status = 0;
    size_t i = 0;
    unsigned char* array = NULL;

    size = DictSize();
    
    array = CreateArray(size);
    CountingSortMT(array, size * MULTIPLE);


    #ifdef TESTING
    /* tests */

    printf("size test:\n");
    printf("%ld\n", strlen((char*)array));
    TEST(size * MULTIPLE == strlen((char*)array));

    printf("sorting test:\n");
    for(i = 1; i < size * MULTIPLE; ++i)
    {
        if(array[i] < array[i - 1])
        {
            printf("%d", array[i]);
            status = 1;
        }
    }
    TEST(!status);

    #endif

    free(array);
}

static size_t DictSize()
{
    FILE *fptr = NULL;
    size_t size = 0;

    fptr = fopen(DICT_PATH, "r");

    if (fptr == NULL)
    {
       return(0);
    }

    /* the size in bytes of the file */
    fseek(fptr, 0, SEEK_END); 
    size = ftell(fptr); 
    fseek(fptr, 0, SEEK_SET);

    fclose(fptr);

    return(size);
}

static unsigned char* CreateArray(size_t size)
{
    FILE *fptr = NULL;
    unsigned char * char_array = NULL;
    int i = 0, j = 0;

    fptr = fopen(DICT_PATH, "r");

    if (fptr == NULL)
    {
       return(NULL);
    }

    char_array = (unsigned char*)malloc(sizeof(unsigned char) * 
                                                    size * MULTIPLE + 1);
    char_array[sizeof(unsigned char) * size * MULTIPLE] = '\0';

    if(NULL == char_array)
    {
        fclose(fptr);
        return (NULL);
    }
    for(i = 0; i < MULTIPLE; ++i)
    {
        if(fread(char_array + j, sizeof(unsigned char), size, fptr) 
            != size)
        {
            return(NULL);
        }
        j += size;
        fseek(fptr, 0, SEEK_SET);
    }
    
    fclose(fptr);

    return(char_array);
}
