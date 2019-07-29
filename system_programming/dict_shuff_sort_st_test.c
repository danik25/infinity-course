/****************************************************************
*        dictionary shuffle and sort mt - Single Threaded       
* file: dict_shuff_sort_st_test.c
* Related files: dict_shuff_sort_st.c, dict_shuff_sort_st.h      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Oded Bryt
* Last update: 03/07/19
****************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen, strcmp */
#include <time.h> /* time */
#include <assert.h> /* assert */

#include "dict_shuff_sort_st.h" 
#include "dani_utilities.h"

#define DICT_PATH "/usr/share/dict/american-english"

/* test functions */
static void CreationAndTesting();
static void TestSingleThread(dict_t *handle, dict_t *reference);
static void TestMultiThread(dict_t *handle, dict_t *reference);

/* verification function */
static int IsSorted(unsigned char **first, unsigned char **second, size_t size);

/* assistance functions */
static size_t GetLinesNumAndChangeEndOfWord(unsigned char* word_array);
static size_t GetDictCharNum();

static void* DictCreate(dict_t *handle);
static unsigned char** CreateWordPointers(dict_t *handle);

static void Shuffle(dict_t *handle);
static void SwapPointers(unsigned char ** first, unsigned char ** second);

/* compare function */
static int WordCompare(const void *first, const void *second);


int main()
{
    CYAN("\n\n\t\t\t~TEST FILE - THREADED SORT~\n");
    CYAN("\t\t\t      Dani Benjamin\n\n");

    CreationAndTesting();

    CYAN("\n\n\t\t\t\t~THE END~\n\n");

    return(0);
}

static void CreationAndTesting()
{
    dict_t handle_ot;
    dict_t handle_mt;
    dict_t reference;
    time_t t;

    srand((unsigned) time(&t));
    
    /* single thread */
    handle_ot.dictionary = DictCreate(&handle_ot);
    handle_ot.word_pointer = CreateWordPointers(&handle_ot);

    /* multithread thread */
    handle_mt.dictionary = DictCreate(&handle_mt);
    handle_mt.word_pointer = CreateWordPointers(&handle_mt);

    /* sorted dictionary, for the test */
    reference.dictionary = DictCreate(&reference);
    reference.word_pointer = CreateWordPointers(&reference);

    Shuffle(&handle_ot);
    Shuffle(&handle_mt);

    YELLOW("single thread\n");
    TestSingleThread(&handle_ot, &reference);

    YELLOW("\nmultiple threads\n");
    TestMultiThread(&handle_mt, &reference);

    free(handle_ot.word_pointer);
    free(handle_mt.word_pointer);
    free(reference.word_pointer);

    free(handle_ot.dictionary);
    free(handle_mt.dictionary);
    free(reference.dictionary);

}

static void TestSingleThread(dict_t *handle, dict_t *reference)
{
    QuickSort(handle->word_pointer, handle->num_of_lines, 
                                        sizeof(unsigned char*), WordCompare);

    TEST(!IsSorted(handle->word_pointer, reference->word_pointer, 
                                                        handle->num_of_lines));
}

static void TestMultiThread(dict_t *handle, dict_t *reference)
{

    QuickSortMT(handle->word_pointer, handle->num_of_lines, 
                                        sizeof(unsigned char*), WordCompare);

    TEST(!IsSorted(handle->word_pointer, reference->word_pointer, 
                                                        handle->num_of_lines));

}


/*============================================================================*/

static void* DictCreate(dict_t *handle)
{
    FILE *fptr = NULL;
    unsigned char *word_array = NULL;    
    
    handle->num_of_chars = GetDictCharNum();

    fptr = fopen(DICT_PATH, "r");

    if (fptr == NULL)
    {
       return(NULL);
    }

    word_array = (unsigned char*)malloc(handle->num_of_chars);

    if(NULL == word_array)
    {
        fclose(fptr);
        return (NULL);
    }

    if(fread(word_array, sizeof(unsigned char), handle->num_of_chars, fptr) 
            != handle->num_of_chars)
    {
        return(NULL);
    }

    fclose(fptr);
    return(word_array);
}

static size_t GetLinesNumAndChangeEndOfWord(unsigned char* word_array)
{
    FILE *fptr = NULL;
    char ch = ' ';
    size_t count = 0;
    int i = 0;
    
    fptr = fopen(DICT_PATH, "r");
    if (fptr == NULL)
    {
       return(0);
    }
    ch = getc(fptr);
    while (ch != EOF) 
    {
        if (ch == '\n')
        {
            word_array[i] = '\0';
            ++count; 
        }
        ++i;
        ch = getc(fptr);
    }
    fclose(fptr);
    return(count);
}

static size_t GetDictCharNum()
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

static unsigned char** CreateWordPointers(dict_t *handle)
{
    FILE *fptr = NULL;
    unsigned char **word_pointer = NULL;
    size_t i = 0, j = 0;;

    handle->num_of_lines = GetLinesNumAndChangeEndOfWord(handle->dictionary);
    word_pointer = (unsigned char**)malloc(sizeof(unsigned char*) * 
                                                        handle->num_of_lines);

    if(NULL == word_pointer)
    {
        return(NULL);
    }

    fptr = fopen(DICT_PATH, "r");
    if (fptr == NULL)
    {
        free(word_pointer);
        return(NULL);
    }

    while (j < handle->num_of_lines) 
    {
        *(word_pointer + j) = handle->dictionary + i;
        /*printf("%ld. %s\n", j, *(word_pointer + j));*/
        i += strlen((char*)(*(word_pointer + j))) + 1;
        ++j;

    }
    fclose(fptr);

    return(word_pointer);
}

static void Shuffle(dict_t *handle)
{
    size_t i = 0;
    size_t first = 0;
    size_t second = 0;

    for(i = 0; i < handle->num_of_lines; ++i)
    {
        first = rand() % handle->num_of_lines;
        second = rand() % handle->num_of_lines;
        SwapPointers(&handle->word_pointer[first], &handle->word_pointer[second]);
    }
}

static void SwapPointers(unsigned char ** first, unsigned char ** second)
{
    unsigned char *tmp = NULL;
    tmp = *first;
    *first = *second;
    *second = tmp;
}

/*++++++++++++++++++++++ compare function for QuickSort ++++++++++++++++++++++*/

static int WordCompare(const void *first, const void *second)
{
    return(strcmp(*(char**)first, *(char**)second));
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int IsSorted(unsigned char **first, unsigned char **second, size_t size)
{
    int status = 0;
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        if(0 != strcmp((char*)first[i], (char*)second[i]))
        {
            status = 1;
        }
    }
    return(status);
}