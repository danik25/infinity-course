
#ifndef  _REC_H_
#define  _REC_H_
#include <stddef.h>
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

/*
 * API Design: 
 * An introduction to recursion, that consists of a calculation fibonacci
 * sequence sum with iterative and recursive solution. implementation of a few
 * string.h library functions using recursion.
 */ 

#ifndef _SL_LIST_
typedef struct sl_node
 {
                    
        void * data;
        struct sl_node *next; 

} sl_node_t;
#endif /* _SL_LIST_ */

/* Description:
 * Recives an index in a fibonacci sequence and returns its value using
 * recursion. The sequence starts 0 1 1 2...
 * 
 *
 * Params:
 *        index - an index in a fibonacci sequence
 *
 * Return Value: value of a givin index. 
 */
size_t RecurFibonacci (size_t index);


/* Description:
 * Recives an index in a fibonacci sequence and returns its value using
 * iteration. The sequence starts 0 1 1 2...
 *
 *
 * Params:
 *        index - an index in a fibonacci sequence
 *
 * Return Value: value of a givin index.
 */
size_t IterFibonacci (size_t index);


/* Description:
 * Using recursion, calculates the length of the string pointed to by s,
 * excluding the terminating null byte ('\0').
 * 
 * 
 * Params:
 *        s − This is the string whose length is to be found.
 *
 * Return Value: This function returns the length of string.
 */
 size_t Strlen(const char *s);


/* Description:
 * Using recursion, compares the two strings s1 and s2.  It returns an integer
 * less than, equal to, or greater than zero if s1 is found, respectively, to
 * be less than, to match, or be greater than s2.
 *
 *
 * Params:
 *        s1 − This is the first string to be compared
 *        s2 − This is the second string to be compared.
 *
 * Return Value: An integer less than, equal to, or greater than zero if s1 
 *        (or the first  n  bytes thereof) is found, respectively, to be less 
 *        than, to match, or be greater than s2.
 */
int Strcmp(const char *s1, const char *s2);


/* Description:
 * Using recursion copies the string pointed to by src, including the 
 * terminating null byte ('\0'), to the buffer pointed to by dest.  The strings
 * may not overlap, and the destination string dest must be large enough to 
 * receive the copy.  Beware of buffer overruns!
 *
 *
 * Params:
 *        dest − This is the pointer to the destination array where the content
 *        is to be copied.
 *        src − This is the string to be copied
 *
 * Return Value: A pointer to the destination string dest.
*/
char *Strcpy(char *dest, const char *src);


/* Description:
 * Using recursion appends the src string to the dest string, overwriting the
 * terminating null byte ('\0') at the end of dest, and then adds a terminating
 * null byte. The strings may not overlap, and  the  dest  string  must  have 
 * enough space for the result.  If dest is not large enough, program behavior
 * is unpredictable.
 * 
 * 
 * Params:
 *        dest − This is pointer to the destination array, which should contain
 *        a C string, and should be large enough to contain the concatenated
 *        resulting string.
 *        src − This is the string to be appended. This should not overlap 
 *        the destination.
 *
 * Return Value: This function returns a pointer to the resulting string dest.
 */       
char *Strcat(char *dest, const char *src);



/* Using recursion finds the first occurrence of the substring needle in
 * the string haystack. The terminating null bytes ('\0') are not compared.     
 * 
 * 
 * Params:
 *        haystack − This is the main C string to be scanned
 * 
 *        needle − This is the small string to be searched with-in haystack
 *        string.
 *
 *        Return Value: These functions return a pointer to the beginning of the
 *               located substring, or NULL if the substring is not found.
 */  
char *Strstr(const char *haystack, const char *needle);


/* Using recursion reverse the direction of the singly linked list.
 *
 * 
 * Params: 
 *        node - reference node.
 * Return value : 
 *        a pointer to the new first node of the list.
*/
sl_node_t *RecurSLLFlip(sl_node_t *node);




#endif /* _REC_H_  */