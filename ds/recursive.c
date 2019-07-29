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
#include <string.h> /* strncmp */
#include <assert.h> /* assert */

#include "sl_list.h"
#include "recursive.h"

size_t RecurFibonacci (size_t index)
{
    if(index == 0 || index == 1)
    {
        return (index);
    }
    return (RecurFibonacci(index - 1) + RecurFibonacci(index - 2));
}

size_t IterFibonacci (size_t index)
{
    size_t first = 0;
    size_t second = 1;
    size_t i = 0;
    size_t ans = 1;
    
    if(index == 0 || index == 1)
    {
        return(index);
    }
    for(i = 1; i < index; ++i)
    {
        ans = first + second;
        first = second;
        second = ans;
    }

    return(ans);
}

 size_t Strlen(const char *s)
 {
    assert(s);

    if('\0' == *s)
    {
        return(0);
    }
    return(1 + Strlen(++s));
 }

int Strcmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);

    if('\0' == *s1 || *s1 != *s2)
    {
        return(*s1 - *s2);
    }

    return(Strcmp(++s1, ++s2));
}

char *Strcpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    *dest = *src;
    if('\0' != *src)
    {
        Strcpy(dest + 1, src + 1);
    }

    return(dest);
}

char *Strcat(char *dest, const char *src)
{
    Strcpy(dest + strlen(dest), src);
    return(dest);
}

char *Strstr(const char *haystack, const char *needle)
{
    if(0 == strncmp(haystack, needle, strlen(needle)))
    {
        return((char*)haystack);
    }
    if('\0' == *haystack)
    {
        return(NULL);
    }
    return(Strstr(haystack + 1, needle));
}

sl_node_t *RecurSLLFlip(sl_node_t *node)
{
    sl_node_t *head = NULL;

    assert(node);

    if (NULL == node->next) 
    {
       return(node);    
    }

    head = RecurSLLFlip(node->next); 
    node->next->next  = node;  
    node->next  = NULL;          
  
    return(head);
}