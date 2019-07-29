#include <stdio.h> /*printf, scanf*/
#include <stdlib.h> /*exit*/
#include <string.h> /*strcmp*/
#include <assert.h> /*assert*/

#include "ws5.h" 

#define UNUSED(x) (void)(x);

/*Defined sruct containing sting and two functions*/
struct Functions
{
    char *str;
    int (*ptr_cmp)(char *str_user, char *str_array);
    enum Boolean (*ptr_oper)(char *file_name);
} array[3] = {
    {"-remove", Cmp, RemoveCommand},
    {"-count", Cmp, CountCommand},
    {"-exit", Cmp, ExitCommand}
    };

void Logger(char *file_name)
{
    FILE *fptr;
    int i;
    char str_user[20];
    enum Boolean answer;    
    
    printf("please enter a sentence\n");
        
    while(1)
    {
        /*accpeting input from the user*/
        fgets(str_user, sizeof(str_user), stdin);
        str_user[strlen(str_user) - 1] = '\0';
                
        for (i=0; i<3; ++i)
        {
            /* if the str entered by the user is equal to array's str*/
            if ( 1 == array[i].ptr_cmp(str_user, array[i].str) ) 
            {
                
                answer = array[i].ptr_oper(file_name);
                if (False == answer)
                {
                    exit(1);
                }
                break;
            }                              
        }
        /*if the users input starts with "<"*/
        if ( '<' == str_user[0] )
            {
                InsertFirstCommand(str_user, file_name);
                continue;
            }
        if (i!=3)
        {
            continue;
        }
        /* appending the line to the file*/
        fptr = fopen(file_name,"a");
        if(NULL == fptr) 
        {
            printf("unsuccessfull open of a file");
            exit(1);
        }
        fprintf(fptr, "%s\n", str_user);
        if( EOF == fclose(fptr) ) 
        {
            printf("unsuccessfull closing");
            exit(1);
        }

    }

}
  
int Cmp( char *str_user, char *str_array )
{
    assert(str_user); /* Program exits if the pointer returns NULL.*/
    assert(str_array);
    
    if ( 0 == strcmp(str_user, str_array) )
    {
        return 1;
    } 
    return 0;
}

enum Boolean RemoveCommand(char *file_name)
{
    assert(file_name);
    /* remove testing */
    if ((remove(file_name)) != 0)
    {
        printf("unsuccessfull removing");
        return False;
    }
    return True;
}


enum Boolean ExitCommand(char *file_name)
{ 
    assert(file_name);
    UNUSED(file_name);
    exit(0);
    return True;     
}

enum Boolean CountCommand(char *file_name)
{
    FILE *fptr;
    int cnt=0;
    char ch;
    
    assert(file_name);
    
    fptr = fopen(file_name,"r");
    
    /* fopen testing */
    if(NULL == fptr) 
    {
        printf("unsuccessfull open of a file");
        return False;
    }
    
    while(( ch = fgetc(fptr)) != EOF)
    {
        if('\n' == ch)
        {
            ++cnt;
        }
        
    }
    
    /* fclose testing */
    if( EOF == fclose(fptr) ) 
    {
        printf("unsuccessfull closing");
        return False;
    }
    
    printf("number of rows:%d\n", cnt);
    return True;
         
}

void InsertFirstCommand(char *str_user, char *file_name)
{
    FILE *fptr;
    FILE *copy;
    
    char ch;
    
    assert(file_name);
    assert(str_user);
    
    ++str_user;
    copy = fopen("file_copy.txt","w+");
    fptr = fopen(file_name,"r+");
   
    /* fopen testing */
    if (NULL == fptr)
    {
        exit(1);
    }
    if (NULL == copy)
    {
        exit(1);
    }
    
    fprintf(copy, "%s\n", str_user);
    while ( (ch = fgetc(fptr)) != EOF)
    {
        if( '\n' == ch )
        {
            fprintf(copy, "%c", '\n');
        }
        else
        {
            fprintf(copy, "%c", ch);
        } 
    } 
    fseek(fptr, 0, SEEK_SET); 
    fseek(copy, 0, SEEK_SET);
    while ( (ch = fgetc(copy)) != EOF)
    {
        fprintf(fptr, "%c", ch); 
    }
    
    
    /* fclose testing */
    if( EOF == fclose(copy) ) 
    {
        printf("unsuccessfull closing of copy file");
        exit(1);
    }
    /* remove testing */
    if (remove("file_copy.txt") != 0)
    {
        printf("unsuccessfull removing of copy file");
        exit(1);
    }
    
    /* fclose testing */
    if( EOF == fclose(fptr) ) 
    {
        printf("unsuccessfull closing of origin file");
        exit(1);
    }
        
}
 
 
 

