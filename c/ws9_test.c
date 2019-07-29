#include <stdio.h> /* printf */
#include <string.h> /* strcpy, strlen */
#include <stdlib.h> /* atoi, itoa */

#include "ws9.h"

static void MemsetTest(void);
static void MemcpyTest(void);
static void MemmoveTest(void);
static void ItoaTest(void);
static void AtoiTest(void);
static void ThreeArraysTest(void);

int main(void)
{
    
    MemsetTest();
    MemcpyTest();
    MemmoveTest();
    ItoaTest();
    AtoiTest();
    ThreeArraysTest();
    Endian();
    
    return 0;
}

static void MemsetTest(void)
{
	char str[50];
    int token = '$';
    size_t num = 2;
	
	printf("\n********Memset********\n\n");
	
    strcpy(str,"a sentence to be changed");
    printf("original sentence:\n'%s'\n\n", str);

    Memset(str, token, num);
    
    printf("modified sentence, replaced with:'%c', %ld times: \n",
    token, num);
    printf("'%s'\n\n", str);
}

static void MemcpyTest(void)
{
	const char str_src[50] = "this is the sentece to be copied";
    char str_dest[50] = {0};
    size_t num = 14;
    
    printf("\n********Memcpy********\n\n");
    
    strcpy(str_dest,"dest sentence");
    printf("origin source: '%s'\n", str_src);
    printf("origin destenation: '%s'\n\n", str_dest);
    
	printf("after a copy of %ld characters from the source sentence:\n",num);
	
    printf("my Memcpy:\n");
    Memcpy(str_dest, str_src, num);
    printf("%s\n\n", str_dest);
    
    printf("library Memcpy:\n");
    memcpy(str_dest, str_src, num);
    printf("%s\n", str_dest);
}

static void MemmoveTest(void)
{
	char str[50] = "123ABC0001111";
    char str_test[50] = "123ABC0001111";
    size_t num = 9;
    
    printf("\n********Memmove********\n\n");
    
    /*strcpy(str_dest,"destenation sentence");*/
    printf("origin source: '%s'\n", str);
    /*printf("origin destenation: '%s'\n\n", str_dest);*/
    
	printf("after a copy of %ld characters from the source sentence:\n",num);
	
    printf("my Memmove:\n");
    Memmove(str + 3, str, num);
    printf("%s\n\n", str);
    
    printf("library Memmove:\n");
    memmove(str_test + 3, str_test, num);
    printf("%s\n", str_test);
}

static void ItoaTest(void)
{
    int num = 7;
    int base = 10;
    char buffer[20];
    
    printf("\n********Itoa********\n\n");
 
    Itoa(num,buffer,base);   
    printf("Decimal value = %d\n", num);
    printf("string, by base:%d = %s\n", base, buffer); 
}

static void AtoiTest(void)
{
    char *str1="12345";
    char *str2 = "d435";
    char *str3 = "111";
    
    printf("\n********Atoi********\n\n");
    
    printf("String = '%s', base = %d, int value = %d\n", str1, 10,
                                                    Atoi(str1, 10));
    printf("library function: = %d\n\n", atoi(str1));
    
    printf("String = '%s', base = %d, int value = %d\n", str2, 16,
                                                    Atoi(str2, 16));
    printf("String = '%s', base = %d, int value = %d\n", str3, 2, 
                                                    Atoi(str3, 2));
}

static void ThreeArraysTest(void)
{
    char *str1="ABCDDD";
    char *str2 = "BCD";
    char *str3 = "XBX";
    
    printf("\n********three arrays********\n\n");
    printf("array number 1: '%s',\narray number 2: '%s',\narray number 3:"
                                            "'%s'.\n\n", str1, str2, str3);
    ThreeArrays(str1, str2, str3, strlen(str1), strlen(str2), strlen(str3)); 
}



