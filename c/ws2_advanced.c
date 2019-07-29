#include <stdio.h> /*printf*/
#include <string.h>
#include <stdlib.h> /* size_t, malloc */
#include <assert.h> /* assert */


#include "ws2.h"

int main() 
{
    /*palindrom variabels*/
    char pal[40];
    
    /*7 boom variabels*/
    int start;
    int end;
    
    /*swap pointers variables*/
    int a=5, b=6;
    int *ptr1=&a;
    int *ptr2=&b;
    
    /*white spaces variables*/
    char word[] = "   one\ttwo\t   \t \tthree \t  \t ";
    
    /*large numbers variables*/
    char *num1="42";
    char  *num2 = "53";
    char *ans1;
    
    char *num3="59";
    char  *num4 = "444444";
    char *ans2;
    
    /*cheking palindrom*/
    printf("********* palindrom *********\n");
    printf("enter a string to be checked for palindrom \n");
    scanf("%s", pal);
    if (0 == IsPalindrom(pal))
    {
    	printf("yes, a palindrom\n");
    }
    else
    {
    	printf("no palindrom\n");
    }
    
    /*cheking 7 boom*/
    printf("********* 7 boom *********\n");
    printf("enter the start of the range\n");
    scanf("%d",&start);
    printf("enter the end of the range\n");
    scanf("%d",&end);
    printf("\n");
    Boom(start, end);
    printf("\n");
    
    /*cheking swap pointers*/
    printf("********* swap pointers *********\n");
    printf("1: %p, 2:%p\n", (void*) ptr1, (void*) ptr2);
    SwapP(&ptr1, &ptr2);
    printf("1: %p, 2:%p\n", (void*) ptr1, (void*) ptr2);
    printf("\n");
    
    /*cheking white spaces*/
    printf("/********delete spaces*********/\n");
    printf("original: |%s|\n",word);
    WhiteSpace(word);
    printf("fixed: |%s|\n",word);
    printf("\n\n");
    
    /*cheking large numbers*/
    printf("/********large numbers*********/\n");
    printf("the numbers added: %s, %s\n", num1, num2);
    printf("regular calculation: %d\n", (42+53));
    ans1 = LargeNumbers(num1, num2);
    printf("string calculation: %s\n",ans1 );
    printf("\n\n");
    printf("the numbers added: %s, %s\n", num3, num4);
    printf("regular calculation: %d\n", (59+444444));
    ans2 = LargeNumbers(num3, num4);
    printf("string calculation: %s\n",ans2 );
    printf("\n\n");
    
    
    free(ans1);
    free(ans2);
    return 0;
}

/*palindrom*/
int IsPalindrom(const char *str)
{
    int i;
    int j;
    int len= strlen(str);
    int half=len/2;
    
    assert(str); 
    
    if ( len%2 != 0)
        half += 1;
    for( i=0, j = len-1; i<half; i++, j--)
    {
        if (str[i]!=str[j])
            return 1;
    }
    return 0;
}

/*7 BOOM*/
void Boom(int start, int end)
{
    int i;
    
    if ( end >= start )
    {
        for ( ; start<=end; ++start )
        {
            if(( start%7 == 0 && start != 0))
            {
                printf("BOOM\n");
                continue;
            }
            i=start;
            while( i != 0 )
            {
                if( i%10 == 7 || i%10 == -7 )
                {
                    printf("BOOM\n");
                    break;    
                }
                i /= 10;
            }
            if ( i == 0 )
            {
                printf("%d\n", start);   
            }  
        }          
    }
 
    else
    {
        printf ("range is illegal\n");
    }      
}

/*pointer swap*/
void SwapP(int **ptr1, int **ptr2)
{
    int *temp;
    temp = *ptr1;
    *ptr1= *ptr2;
    *ptr2 = temp;
}

/*7 white spaces*/
void *WhiteSpace(char * str)
{
    int i=0;
    int j;
    int cnt=0;
    assert(str);
    while( ' ' == str[i] || '\t' == str[i] )
    {
        for ( j = i; str[j] != '\0'; j++)
            {
                str[j] = str[j+1];
            }
    }
    for (i=1; str[i] != '\0'; i++)
    {
        if (str[i] == '\t')
            {
                str[i] = ' ';
            }
        if ((str[i] == ' ') && ( str[i-1] == ' ' ))
        {
            j=i;
            cnt=0;
            while( ' ' == str[j] || '\t' == str[j])
            {
                
                ++cnt;
                ++j;
            }
            
            while( cnt > 0 )
            {
                for (j=i; str[j] != '\0'; j++)
                {
                    str[j] = str[j+1];
                }
                --cnt;
            }
            
        }
    }    
    str[i]='\0';      
    if ( str[i-2] == ' ' || str[i-1] == '\t' )
    {
        str[i-2] = '\0';
    } 
    
    
    return 0;
}

/*large numbers*/
char *LargeNumbers(char * num1, char * num2)
{
    int i=strlen(num1)-1; /*the end of the string*/
    int j=strlen(num2)-1; /*the end of the string*/
    int k;
    int one, two;
    char *sum_string;
    int sum = 0;
    int left_over;
    if (i>j)
    {
        sum_string = malloc((i+2)*sizeof(char));
        k=(i+1)*sizeof(char);
    }
    else
    {
        sum_string = malloc((j+2)*sizeof(char));
        k= (j+1)*sizeof(char);
    }
    
    if (NULL == sum_string)
    {
        return NULL;
    }
    
    while (k>-1)
    {
        one = (i  < 0 ) ? 0 : (num1[i]-'0');
        two = (j < 0 ) ? 0 : (num2[j]-'0');
        
        sum+=one+two;
        if ( sum > 9 )
        {
            left_over = sum%10;
            sum = 1;
            sum_string[k] = (left_over + '0');
        }
        else
        {
            sum_string[k] = (sum + '0');
            sum =0;
        }
        
        --i, --j, --k;
    }
    sum_string[strlen(sum_string)]='\0';
    if ( sum_string[0] == '0' )
    {
        for (k=0 ; k< sum_string[k]-1; k++)
        {
            sum_string[k] = sum_string[k+1];
        }
        sum_string[k]='\0';
    }
    
    
    return sum_string;
}

