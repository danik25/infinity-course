/****************************************************************
*                                 Recursion 
*                       ==============================
* File Name: recursive.h
* Related files: recursive.c, recursive_test.c
* #Version: V 1.8
* Writer: Dani Benjamin                         
* Reviewer: Ayala Rosel 
* Last update: 28/05/19
****************************************************************/
#define GREEN(str)      printf("\033[1;32m%s\033[0m\n", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str)     printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str)       printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str)     printf("\033[1;35m%s\033[0m\n", str)

#define TEST(x) x ? GREEN("success") : RED("fail")

#include <string.h> /* strcmp */
#include <stdio.h> /* printf */
#include <time.h> /* clock */
#include "sl_list.h"
#include "recursive.h"

static void testFibRec();
static void testFibIter();
static void testStrlen();
static void testStrcmp();
static int CmpMesure(char *s1, char *s2, char *kind);
static void testStrcpy();
static void testStrcat();
static void testStrstr();
static void TestFlip();
static void PrintNodeInt(sl_node_t *node);

int main()
{
    YELLOW("recursive fibonacci");
    testFibRec();
    YELLOW("\niteration fibonacci");
    testFibIter();
    YELLOW("\nstrlen");
    testStrlen();
    YELLOW("\nstrcmp");
    testStrcmp();
    YELLOW("\nstrcpy");
    testStrcpy();
    YELLOW("\nstrcat");
    testStrcat();
    YELLOW("\nstrstr");
    testStrstr();
    YELLOW("\nflipping");
    TestFlip();
    return(0);
}

static void testFibRec()
{
    int i = 0;
    for(i = 0; i < 12; ++i)
    {
        printf("%ld ", RecurFibonacci(i));
    }
    printf("\n");
}

static void testFibIter()
{
    int i = 0;
    for(i = 0; i < 12; ++i)
    {
        printf("%ld ", IterFibonacci(i));
    }
    printf("\n");
}

static void testStrlen()
{
    char *first = "";
    char *second = "abcd";
    TEST((Strlen(first) == 0));
    TEST((Strlen(second) == 4));
}

static void testStrcmp()
{
    char *s1 = "";
    char *s2 = "abcd";

    char *s3 = "abcde";
    char *s4 = "abcde";

    char *s5 = "fgh";
    char *s6 = "fghi";

    int sum_lib = 0;
    int sum_rec = 0;

    sum_lib = CmpMesure(s1, s2, "lib") + CmpMesure(s3, s4, "lib") + 
                                                CmpMesure(s5, s6, "lib");

    sum_rec = CmpMesure(s1, s2, "rec") + CmpMesure(s3, s4, "rec") + 
                                                CmpMesure(s5, s6, "rec");
    
    TEST(Strcmp(s1, s2) == strcmp(s1, s2));
    TEST(Strcmp(s3, s4) == strcmp(s3, s4));
    TEST(Strcmp(s5, s6) == strcmp(s5, s6));

    printf("library function time: %f\n", 
                        (double)sum_lib / 3 / CLOCKS_PER_SEC);
    printf("recursive function time: %f\n", 
                        (double)sum_rec / 3 / CLOCKS_PER_SEC);
}

static int CmpMesure(char *s1, char *s2, char *kind)
{
    clock_t start = 0;
    clock_t end = 0;
    start = clock();
    
    
    if(0 == strcmp(kind, "lib"))
    {
        strcmp(s1, s2);
    }
    if(0 == strcmp(kind, "rec"))
    {
        Strcmp(s1, s2);
    }
    end = clock();

    return(end - start);
}
static void testStrcpy()
{
    char *s1 = "abcd";
    char s2[5] = {""};
    char s3[5] = {""};

    clock_t start_lib = 0;
    clock_t end_lib = 0;

    clock_t start_rec = 0;
    clock_t end_rec = 0;

    start_lib = clock();
    strcpy(s2, s1);
    end_lib = clock();

    start_rec = clock();
    strcpy(s3, s1);
    end_rec = clock();

    TEST(!strcmp(s2, s3));
    printf("library function time: %f\n", 
                        (double)(end_lib - start_lib) / CLOCKS_PER_SEC);
    printf("recursive function time: %f\n", 
                        (double)(end_rec - start_rec) / CLOCKS_PER_SEC);
}

static void testStrcat()
{
    char* src = "benjamin";
    char dest[50];
    strcpy(dest, "dani");
    printf("%s\n", Strcat(dest, src));
    TEST(!strcmp(dest, "danibenjamin"));
}

static void testStrstr()
{
    const char haystack[20] = "finity";
    const char needle[10] = "init";
    const char no_needle[10] = "no";
    printf("%s\n", Strstr(haystack, needle));
    TEST(!strcmp(Strstr(haystack, needle), "inity"));
    TEST(NULL == (Strstr(haystack, no_needle)));
}

static void TestFlip()
{
	int array[] = {10, 11, 12, 13};
	sl_node_t *node = NULL;
	size_t i = 0;
	sl_node_t *ans_node = NULL;
	node = SLLCreate(&array[i], NULL);
	
	PURPLE("1. flipping one node list\n");
	printf("original:\n");
	PrintNodeInt(node);
	ans_node = RecurSLLFlip(node);
	printf("flipped:\n");
	PrintNodeInt(ans_node);
	printf("\n");
	PURPLE("2. flipping multiple nodes list\n");
	for(i = 1; i < sizeof(array)/sizeof(int); ++i)
	{
		node = SLLCreate(&array[i], node);
	}
	printf("original:\n");
	PrintNodeInt(node);
	ans_node = RecurSLLFlip(node);
	printf("flipped:\n");
	PrintNodeInt(ans_node);
	SLLDestroy(ans_node);
	printf("\n");
}

static void PrintNodeInt(sl_node_t *node)
{
    if(node == NULL)
    {
        printf("none");
    }
    while(node != NULL)
    {
        printf("%d ",*(int*)node->data);
        node = node->next;
    }
    printf("\n");
}