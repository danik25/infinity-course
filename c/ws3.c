#include <stdio.h> /* printf, scanf */
#include <string.h> /* string library */
#include <strings.h> /* strcsaecmp */
#include <stdlib.h> /* size_t, malloc, envp */
#include <ctype.h> /*tolower*/
#include <math.h> /*pow, log*/
#include <assert.h> /*assert*/

/*addition of -lm flag after the file name while compiling!*/

void Environment(char *envp[]);
char *Strcpy(char *dest, const char *src);
void PrintFunc(char **print_envp);
void FreeFunc(char **free_buffer);
int Napoleon(int num);
int Napoleon2(int num);
void PrintTypes();

int main ( int arc, char *argv[], char *envp[] )
{    
    /*Napoleon variables*/
    int sold_num;
	int living_sold1;
	int living_sold2;
    
    /*environment test*/
	printf("\n**********environment**********\n\n");
    Environment(envp);
    
    
    /*Napoleon test*/
    printf("**********Napoleon**********\n\n");
    sold_num = 200;
    living_sold1 = Napoleon(sold_num);
	living_sold2 = Napoleon2(sold_num);
    printf("out of %d soldiers, the last living soldier is number %d\n",sold_num ,living_sold1);
    printf("second way: %d\n",living_sold2 );
    printf("\n\n");  
    
    
    /*types test*/
    printf("**********data types**********\n\n");
    PrintTypes();
    
    return 0;
}

void Environment(char *envp[])
{
    char **buffer=0;
    char **buffer_runner=0;
    char **envp_copy = envp;
    
    while(*envp_copy)
    {
        ++envp_copy; /*counting the rows in envp*/
    }
    buffer = (char**) calloc(sizeof(char*), (envp_copy-envp));
    
    if ( NULL == buffer )
    {
        exit(1);
    }
    
    buffer_runner = buffer;
    
    while (*envp)
    {
        *buffer_runner = (char*) malloc(sizeof(char*)*(strlen(*envp)));
        
        if ( NULL == buffer_runner )
        {
            exit(1);
        }
        
        *buffer_runner = Strcpy(*buffer_runner, *envp); /*copies in lower
                                                                case*/
        ++envp, ++buffer_runner;

    }
    
    PrintFunc(buffer);
    printf("\n\n");
    
    FreeFunc(buffer); /*freeing the rows*/
    free(buffer);   /*freeing the table*/
    buffer = NULL;
}
    
    
char *Strcpy(char *dest, const char *src)
{
    int i;
    
    assert(dest);
    assert(src);
    
    for ( i = 0; src[i] != '\0' ; i++ )
    {
        dest[i] = tolower(src[i]); /*copies in lower case*/
    }
    dest[i] = '\0';
    
    return dest;
}

void PrintFunc(char **print_buffer)
{
    assert(print_buffer);
    
    for (;*print_buffer != NULL; ++print_buffer)
    {
        printf("%s\n", *print_buffer);
    }
}

void FreeFunc(char **free_buffer)
{
    while (*free_buffer)
    {
        free(*free_buffer);
        *free_buffer = NULL;
        ++free_buffer;
    }
}


int Napoleon(int num)
{
    int *sold = (int*) calloc(num, sizeof(int));
    int i = 0;
    int num_copy = num;
    int alive_index;
    while (num > 1) /*as long as more than one soldier is alive*/
    {
    	if (num == 2) /*the next loop will kill the last soldier*/
        	{
        		alive_index = i;
        	}
        while( sold[i] == 0 )
        {
            i == num_copy-1 ? i =0 : ++i; /*if we are at the end of the
                                            array, return to the start*/
            while (sold[i] != 0)
            {
            	i == num_copy-1 ? i =0 : ++i; /*if we are at the end of the
                                            array, return to the start*/
            }
            
            sold[i] = 1;
            --num;
            
        }
        i == num_copy-1 ? i =0 : ++i;
    }
    
    free(sold);
    sold = NULL;
    
    return alive_index+1;
}
int Napoleon2(int num)
{
	int cal;
	int cal_pow;
	int ans;
	cal =(int)(log(num)/log(2));
    cal_pow = (int) pow(2, cal);
    
    ans = num/cal_pow+num%(cal_pow)*2;
    return ans;
}

void PrintTypes()
{
	printf("char:               %ld\n", sizeof(char));
	printf("unsigned char:      %ld\n", sizeof(unsigned char));
	printf("signed char:        %ld\n", sizeof(signed char));
	printf("short int:          %ld\n", sizeof(short int));
	printf("int:                %ld\n", sizeof(int));
	printf("long int:           %ld\n", sizeof(long int));
	printf("unsigned int:       %ld\n", sizeof(unsigned int));
	printf("unsigned short int: %ld\n", sizeof(unsigned short int));
	printf("unsigned long int:  %ld\n", sizeof(unsigned long int));
	printf("float:              %ld\n", sizeof(float));
	printf("double:             %ld\n", sizeof(double));
	printf("long double:        %ld\n", sizeof(long double));
}









