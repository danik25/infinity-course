#include <stdio.h> /* printf */
#include <string.h> /* strcpy, strlen */
#include <assert.h> 
#include <math.h> /*pow*/
#include <stdlib.h> /*exit, calloc*/
#include <ctype.h> /* isalnum */

#include "ws9.h"

#define NUMBER 57
#define ASCII_GAP 87
#define ASCII_LENGTH 256

#define IS_LITTLE ((short*)"a" != (short*)'a')

void *Memset(void *s, int c, size_t n)
{
    unsigned long *ptr_word = 0; /* a pointer that holds word size string */
    char *ptr_byte = (char *)s;
    unsigned long c_word = c;
    
    assert(s);
    
    /* word size representation of 'c' */
    c_word |= c_word<<8;
    c_word |= c_word<<16;
    c_word |= c_word<<32;
    
    while ((unsigned long int)ptr_byte % 8 != 0 && 
    					n > 0)
    {
        *ptr_byte = c;
        ++ptr_byte;
        --n;
    }
    
    ptr_word = (unsigned long*)ptr_byte;
    
    /* word size changes */
    while (n >= 8)
    {
        *ptr_word = c_word;
        ++ptr_word;
        n -= 8;
        ptr_byte += 8;
    }
     
    while (n > 0)
    {
        *ptr_byte = c;
        ++ptr_byte;
        --n;
    }
    return s;
}  

void *Memcpy(void *dest, const void *src, size_t n)
{
	/* pointers that holds a word size strings */
    unsigned long *ptr_word_dest = 0;
    unsigned long *ptr_word_src = 0;
    
    /* pointers that holds one byte */
    char *ptr_byte_dest = 0;
    char *ptr_byte_src = 0;
    
    assert(dest);
    assert(src);
    
    ptr_byte_dest = (char *)dest;
    ptr_byte_src = (char *)src;
    
    /* loops while the address is not divided by 8 (word size) */
    while ((unsigned long int)ptr_byte_dest % 8 !=0 && n > 0)
    {
        *ptr_byte_dest = *ptr_byte_src;
        ++ptr_byte_dest, ++ptr_byte_src;
        --n;
    }
    
    ptr_word_dest = (unsigned long*)ptr_byte_dest;
    ptr_word_src = (unsigned long*)ptr_byte_src;
    
    /* word size changes */
    while (n >= 8)
    {
        *ptr_word_dest = *ptr_word_src;
        ++ptr_word_dest, ++ptr_word_src;
        ptr_byte_dest += 8, ptr_byte_src += 8; /* advancing the byte pointer 
                                                    by word size */
         n -= 8;
    }
    
    while (n > 0)
    {

        *ptr_byte_dest = *ptr_byte_src;
        ++ptr_byte_dest, ++ptr_byte_src;
        --n;
    }
    return dest;
}

void *Memmove(void *dest, const void *src, size_t n)
{
    /* pointers that holds a word size strings */
    unsigned long *ptr_word_dest = 0;
    unsigned long *ptr_word_src = 0;
    
    /* pointers that holds one byte */
    char *ptr_byte_dest = 0;
    char *ptr_byte_src = 0;
    
    assert(dest);
    assert(src);
    
    ptr_byte_dest = (char *)dest;
    ptr_byte_src = (char *)src;
    
    /* if source and dest overlap, start the copy process from the end */
    if (ptr_byte_src + n >= ptr_byte_dest)
    {
        ptr_byte_dest = (char*) dest + n -1;
        ptr_byte_src = (char*) src + n -1;
        
        while ((unsigned long int)ptr_byte_dest % 8 != 0 && n > 0)
        {
            *ptr_byte_dest = *ptr_byte_src;
            --ptr_byte_dest, --ptr_byte_src;
            --n;
        }
    
        ptr_word_dest = (unsigned long*)ptr_byte_dest;
        ptr_word_src = (unsigned long*)ptr_byte_src;
    
        /* word size changes */
        while (n >= 8)
        {
            --ptr_word_dest, --ptr_word_src;
            *ptr_word_dest = *ptr_word_src;
            ptr_byte_dest -= 8, ptr_byte_src -= 8; /* advancing the byte pointer 
                                                    by word size */
            n -= 8;
        }
        while (n > 0)
        {
            *ptr_byte_dest = *ptr_byte_src;
            --ptr_byte_dest, --ptr_byte_src;
            --n;
        }  
    }  
    else
    {
        Memcpy(dest, src, n);
    }
    return dest;
}

char * Itoa(int value, char *str, int base)  
{
    char the_base[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int val_copy;
    int cnt = 0;
    int flag = 0; /* 0 incase of positive number */
    
    assert(str);
    
    if ( value == 0)
    {
        str[0] = '0';
        return str;
    }
    
    if (value < 0)
    {
        value *= -1;
        str[0] = '-'; 
        flag = 1; /* in case of a negative number, the loop run
                                                     until index 1 */
        ++cnt;
    }
    
    val_copy = value;
    
    /* counting the anount of chars needed in the string */
    while (val_copy > 0)
    {
        val_copy /= base;
        ++cnt;
    }
    str[cnt] = '\0';
    while (cnt > flag)
    {
        str[cnt -1] = the_base[value % base] ; /* cnt -1: we start counting
                                                     from 0 */
        value /= base;
        --cnt;
    }
    return str;
}

int Atoi(const char *str, int base)
{
    int answer = 0;
    double index = 0;
    int length = strlen(str)-1;
    
    assert(str);
    
    while (length >= 0)
    {
        /* if a base 10 number is negative*/
        if (length == 0 && str[length] == '-' && base == 10)
        {
            answer *= -1;
            return answer;
        }
        /* if there is a char that isn't a num or a letter*/
        if (!isalnum(str[length]))
        {
            printf("wrong char\n");
            exit(1);
        }
        if (str[length] > NUMBER)
        {
            /* if the letter is out of the base range */
            if (base - (int)(str[length] - ASCII_GAP) <= 0) 
            {
                printf("error, a digit in an incompatible base\n");
                exit(1);
            }
            answer += (str[length] - ASCII_GAP) * pow(base, index);
        }
        
        else
        {
            /* if the digit is out of the base range */
            if (base - (str[length] - '0') <= 0 )
            {
                printf("error, wrong base or string\n");
                exit(1);
            }
            answer += (str[length] - '0') * pow(base, index);
        }
        ++index;
        --length;
    }
    return answer;
}

void ThreeArrays(char *arr1, char *arr2, char *arr3, int size1, int size2,
                                                                int size3)
{
    int i = 0;
    char *letters = (char*)calloc(ASCII_LENGTH, sizeof(char));
    
    assert(*arr1);
    assert(*arr2);
    assert(*arr3);
    
    
    if (NULL == letters)
    {
        printf("unsuccessful memory allocation");
        exit(1);
    }
    
    for (i = 0; i < size1; ++i)
    {
        /* every array affects 'letters' once */
        if(*(letters + arr1[i]) < 1)
        {
            ++*(letters + arr1[i]);
        }
    }
    for (i = 0; i < size2; ++i)
    {
        if(*(letters + arr2[i]) < 2)
        {
            ++*(letters + arr2[i]);
        }
    }
    for (i = 0; i < size3; ++i)
    {
        *(letters + arr3[i]) = 0;
    }
    printf("the letters appearing in array 1 and 2, but not in 3:\n");
    for (i=0; i < ASCII_LENGTH; i++)
    {
        if (letters[i] > 1)
        {
            printf("%c ", i);
        }
    }
    printf("\n\n");
    free(letters);
    letters = NULL;
}

void Endian()
{
    int num = 1;
    printf("\n********endian********\n\n");
    printf("the computer is:\n");
    (*(char *)&num) ? printf("Little-Endian\n\n") : printf("Big-Endian\n\n");
    
    printf("and by macro:\n");
    printf("%d\n",IS_LITTLE);
}






  
