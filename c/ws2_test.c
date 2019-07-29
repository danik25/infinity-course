#include <stdio.h> /* printf, scanf */
#include <ctype.h> /* tolower */
#include <string.h> /* string library */
#include <strings.h> /* strcsaecmp */
#include <stdlib.h> /* size_t, malloc */
#include "ws2.h"

int main()
{
	/*Strcmp variabels*/
    char str_len[40];
    
	/*Strcmp variabels*/
    char str_cmp1[40];
    char str_cmp2[40];
    
    /*Strcpy and strncpy variabels*/
    char dest[40];
    char dest2[40];
    char src[40];
    size_t num=0;
    
	/*Strcasecmp variabels*/
    char str_case1[40];
    char str_case2[40];
    
    /*Strchr variabels*/
    char ch;
    char str[40];
    
    /*Strdup variabels*/
    char str_to_dup[40];
    
    /*Strcat variabels*/
    char *org = "original string";
    char *add = "addition";
    
    /*Strncat variabels*/
    char *org2 = "original string";
    char *add2 = "addition";
    
    /*Strstr variabels*/
    char *string = "hello world";
	char *sub = "llo";
    
    /*Strspn variabels*/
    char origin_string[40];
    char sub_string[40];
    int ans1;
    int ans2;
    
    /*Strtok variabels*/
    char *tok;
    char str_tok[]="hello to the world";
    char delim[]=" ";
    
    
    /*cheking Strlen*/
    printf("*********Strlen*********\n");
    printf("Enter a string to be measure \n");
    scanf("%s", str_len);
    printf("the string entered: %s\n", str_len);
    if ( 0 == strlen(str_len) - Strlen(str_len) )
    {
        printf("the length: %ld\n", Strlen(str_len));
    	printf("Strlen- success \n");
    }
    printf("\n");
    
	/*cheking Strcmp*/
	printf("*********Strcmp*********\n");
	printf("Enter the first string \n");
    scanf("%s", str_cmp1);
    printf("Enter the second string \n");
    scanf("%s", str_cmp2);
    
    printf("you entered: %s, %s\n",str_cmp1, str_cmp2); 
    if ( 0 == strcmp(str_cmp1,str_cmp2)-Strcmp(str_cmp1,str_cmp2))
    {
        if ( Strcmp(str_cmp1,str_cmp2) != 0)
        {
            printf("not the same\n");
        }
        else
        {
            printf("the same!\n");
        }
    	printf("Strcmp- success \n");
    }
    printf("\n");
    
    /*cheking Strcpy*/
    printf("*********Strcpy*********\n");
    printf("Enter the source string \n");
    scanf("%s", src);
    printf("you entered: %s\n", src);
        
    printf("new function output: %s \n",Strcpy(dest, src) );
    printf("Strcpy- success \n");
    
    printf("\n");
    
    /*cheking Strncpy*/
    printf("*********Strncpy*********\n");
    printf("Enter a number of char to be copied \n");
    scanf("%lu", &num);
    printf("you entered: %ld\n", num);
    
    printf("%s\n",Strncpy(dest2, src, num));
    printf("Strncpy- success \n");
   
    printf("\n");
    
    /*cheking Strcasecmp*/
    printf("*********Strcasecmp*********\n");
    printf("Enter the first string (strcasecmp) \n");
    scanf("%s", str_case1);
    printf("Enter the second string (strcasecmp) \n");
    scanf("%s", str_case2);
    
    printf("you entered: %s, %s\n",str_case1, str_case2);
    
    if ( 0 == strcasecmp(str_case1,str_case2)-Strcasecmp(str_case1,str_case2))
    {
        if ( Strcasecmp(str_case1,str_case2) != 0)
        {
            printf("not the same\n");
        }
        else
        {
            printf("the same!\n");
        }
    	printf("Strcasecmp- success \n");
    }
    printf("\n");
    
	/*cheking Strchr*/
	printf("*********Strchr*********\n");
	printf("Enter the string you want a part of \n");
    scanf("%s", str);
    printf("Enter the letter to start from \n");
    scanf(" %c", &ch);
    
    printf("you entered: %s, %c \n", str,ch);
    
    printf("output from original function: %s\n", strchr(str, ch));
    printf("output from new function: %s\n", Strchr(str, ch));

    printf("\n");
    
    /*cheking Strdup*/
    printf("*********Strdup*********\n");
    printf("Enter the string to be duplicated \n");
    scanf("%s", str_to_dup);
    
    printf("new function: %s\n", Strdup(str_to_dup));

	printf("\n");
	
	/*cheking strcat*/
	printf("*********strcat*********\n");
	printf("first string: %s, second: %s\n", org, add);
	printf("new word (strcat): %s\n", Strcat(org, add));
	printf("\n");
	
	/*cheking strncat*/
	printf("*********strncat*********\n");
	printf("and now by number: %d\n",3);
	printf("new word (strncat): %s\n", Strncat(org2, add2, 3));
	printf("\n");
	
	/*cheking strstr*/
	printf("*********strstr*********\n");
	printf("strstr: the string: %s, the sub: %s, the output: %s \n", string,
	sub ,Strstr(string, sub));
	printf("\n");
	
	/*cheking strspn*/
	printf("*********strspn*********\n");
	printf("enter the major string \n");
	scanf(" %s", origin_string);
	printf("enter the sub to look in the major \n");
	scanf("%s", sub_string);
	ans1 = strspn(origin_string, sub_string);
	ans2 = Strspn(origin_string, sub_string);
	printf("origin function: %d\nnew function: %d\n",ans1 ,ans2);
	printf("\n");
	
	/*cheking strtok*/
	printf("*********strtok*********\n");
	printf("the string: %s, the delim: %s \n",str_tok,delim);
    tok = Strtok(str_tok,delim);
    while(tok!=NULL)
    {
        printf("%s\n", tok);
        tok = Strtok(NULL,delim);
    }
    
    return 0;
    
}



