/****************************************************************
*                Data Structures - Hash Table
* file: hash_table.h
* Related files: hash_table.c, hash_table_test.c
* #Version: V 1.1
* Writer: Dani Benjmain
* Reviewer: Idan Argaman
* Last update: 04/06/19
****************************************************************/

#include <stdio.h> /* printf */
#include <string.h> /* srtcmp */
#include <stdlib.h> /* malloc, fopen */

#include "colours.h"
#include "hash_table.h"

/* basic tests */
static void HashCreateTest();
static void HashInsertTest();
static void HashRemoveTest();
static void HashFindTest();
static void HashCountTest();

/* dictionary tests */
static void DictTest();

static int CompareString(void *data1, void* data2);
static size_t KeyConvertion(const void *data);
int PrintString(void *data, void *param);
int FreeTmpMalloc(void *data, void *param);

#define UNUSED(x) (void)(x)
#define DICT_PATH "/usr/share/dict/american-english"

int main()
{
    CYAN("\n\n\t    ~TEST FILE Hash Table~");
    CYAN("\t\tDani Benjamin\n\n");
    
    YELLOW("\n********create test********\n");
    HashCreateTest();
    YELLOW("\n********insert test********\n");
    HashInsertTest();
    YELLOW("\n********remove test********\n");
    HashRemoveTest();
    YELLOW("\n********find test********\n");
    HashFindTest();
    YELLOW("\n********count test********\n");
    HashCountTest();

    YELLOW("\n********inegration and dictionary********\n");
    DictTest();
    

    CYAN("\n\t\t   THE END\n\n");
    return(0);
}

static void HashCreateTest()
{
    size_t capacity = 4;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);

    TEST(table);

    HashDestroy(table);
}

static void HashInsertTest()
{
    size_t capacity = 5;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);
    char *arr[] = {"abc", "cd", "h", "ab", "h"};

    size_t i = 0;

    for(i = 0; i < sizeof(arr) / sizeof(char*); ++i)
    {
        HashInsert(table, arr[i]);
    }
    HashForEach(table, PrintString, NULL);

    HashDestroy(table);
}

static void HashRemoveTest()
{
    size_t capacity = 5;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);
    char *arr[] = {"abc", "cd", "h", "ab", "lf"};
    char *not_exist = "bb";
    size_t i = 0;

    PURPLE("\n1. trying to remove data from empty table");
    HashRemove(table, not_exist);

    for(i = 0; i < sizeof(arr) / sizeof(char*); ++i)
    {
        HashInsert(table, arr[i]);
    }

    PURPLE("\n2. trying to remove not existing data");
    HashRemove(table, not_exist);
    HashForEach(table, PrintString, NULL);

    PURPLE("\n3. removing the whole table");
    for(i = 0; i < sizeof(arr) / sizeof(char*); ++i)
    {
        printf("\nremoving %s: \n======\n", arr[i]);
        HashRemove(table, arr[i]);
        HashForEach(table, PrintString, NULL);
        printf("======\n");
    }
    HashDestroy(table);
}

static void HashFindTest()
{
    size_t capacity = 5;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);
    char *arr[] = {"abc", "cd", "h", "ab", "h"};
    char *not_exist = "bb";
    size_t i = 0;

    PURPLE("1. empty table");
    TEST(NULL == HashFind(table, arr[0]));

    /* filling the table */
    for(i = 0; i < sizeof(arr) / sizeof(char*); ++i)
    {
        HashInsert(table, arr[i]);
    }

    PURPLE("\n2. not existing data");
    TEST(NULL == HashFind(table, not_exist));

    PURPLE("\n3. existing data");
    TEST(0 == strcmp(HashFind(table, arr[0]), arr[0]));

    HashDestroy(table);
}

static void HashCountTest()
{
    size_t capacity = 4;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);
    char *arr[] = {"abc", "cd", "h", "ab"};
    size_t i = 0;
    int status = 0;

    status = (0 != HashSize(table));

    /* filling the table */
    for(i = 0; i < sizeof(arr) / sizeof(char*); ++i)
    {
        HashInsert(table, arr[i]);
        if(HashSize(table) != i + 1)
        {
            status = 1;
        }
    }
    TEST(!status);
}

static void DictTest()
{
    FILE *fptr;
    char word[20] = "";
    char *tmp_word = NULL;
    size_t capacity = 102315;
    hash_t *table = HashCreate(capacity, KeyConvertion, CompareString);

    char user_input[20] = "";
    
    fptr = fopen(DICT_PATH, "r");
 
    if (fptr == NULL)
    {
       return;
    }

    while (fscanf(fptr, "%s", word) != EOF)
    {
        tmp_word = (char*)malloc(strlen(word) + 1);
        strcpy(tmp_word, word);
        HashInsert(table, tmp_word);
    }
    printf("enter a word to be checked, enter '0' when done:\n");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strlen(user_input) - 1] = '\0';

    while(0 != strcmp(user_input, "0"))
    {
        if(NULL == HashFind(table, user_input))
        {
            U_RED("\nnot existing!\n");
        }
        else if(0 == strcmp(HashFind(table, user_input), user_input))
        {
            U_GREEN("\nexists!\n");
        }
        else
        {
            printf("somthing went wrong\n");
        }
        printf("\nenter a word to be checked:\n");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strlen(user_input) - 1] = '\0';
    }

    fclose(fptr);
    HashForEach(table, FreeTmpMalloc, NULL);
    HashDestroy(table);
}

/*============================================================================*/

static int CompareString(void *data1, void* data2)
{
    return (!strcmp((char*)data1, (char*)data2));
}

static size_t KeyConvertion(const void *data)
{
    size_t sum = 0;
    char * runner = (char*)data;
    while('\0' != *runner)
    {
        sum += *runner;
        ++runner;
    }
    return(sum);
}

int PrintString(void *data, void *param)
{
    UNUSED(param);
    printf("%s \n", (char*)data);

    return(0);
}

int FreeTmpMalloc(void *data, void *param)
{
    UNUSED(param);
    free(data);

    return(0);
}