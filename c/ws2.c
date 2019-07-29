#include <stdio.h> /* printf, scanf */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* size_t, malloc */
#include <string.h> /* string library */
#include <strings.h> /* strcsaecmp */

/*first- Strlen*/
size_t Strlen(const char *s)
{
    size_t i = 0;
    while(s[i])
    {
        ++i;
    }
    return i;
}

/*second- Strcmp*/
int Strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while( s1[i] || s2[i] )
    {
        if( s1[i] != s2[i] )
        {
            return s1[i]-s2[i];
		}
        ++i;
    }
    return 0;
}

/*third- Strcpy*/
char *Strcpy(char *dest, const char *src)
{
    int i;
    for ( i = 0; src[i] != '\0' ; i++ )
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

/*fourth- Strncpy*/
char *Strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    

    for ( i = 0; i < n && src[i] != '\0'; i++ )
    {
        dest[i] = src[i];
    }
    for ( ; i < n; i++)
    {
        dest[i] = '\0';
    }
    dest[i] = '\0';
    return dest;
}

/*fifth- Strcasecmp*/
int Strcasecmp (const char *s1, const char *s2)
{
    int i = 0;
    while( s1[i] || s2[i] )
    {
        if(tolower(s1[i])!=tolower(s2[i]))    
            return tolower(s1[i])-tolower(s2[i]);
        ++i;
    }
    return 0;
}

/*sixth- strchr*/
char *Strchr(const char *str, int c)
{
    int i;
    for ( i = 0; str[i] != '\0' ; i++ )
    {
        if ( str[i] == c )
            return (char *) str+i;
    }
    return NULL;
}

/*seventh - strdup*/
char *Strdup (const char *s)
{
    char *newstr= malloc( strlen(s) +1 );
    if ( newstr == NULL )
    {
        return NULL;
    }
    
    return Strcpy(newstr, s);
}

/*eighth- strcat*/
char *Strcat(char *dest, const char *src)
{
	int i,j;
	int len_dest = strlen(dest);
	int len_src = strlen(src);
	char *addition_len = malloc (len_dest*sizeof(char)+len_src*sizeof(char));
	for ( i = 0; i < len_dest; i++ )
	{
		addition_len[i] = dest[i];
	}
	for( j = 0; j < len_src; j++ )
	{
	    addition_len[i+j] = src[j];
	}
	dest=addition_len;
	dest[len_dest+i]='\0';
	return (char* )dest;
}

/*ninth-strncat*/
char *Strncat(char *dest, const char *src, size_t n)
{
	int i;
	size_t j;
	int len_dest = Strlen(dest);
	int len_src = Strlen(src);
	char *addition_len = malloc (len_dest*sizeof(char)+n*sizeof(char));

	for ( i = 0; i < len_dest; i++ )
	{
		addition_len[i] = dest[i];
	}
	for( j = 0; j < n && j < len_src; j++ )
	{
	    addition_len[i+j] = src[j];
	}
	addition_len[len_dest + j]='\0';
	dest=addition_len;
	

	return dest;
}

/*tenth-strstr*/
char *Strstr(const char *haystack, const char *needle)
{
    int i = 0;
    int j = 0;
    while(*(haystack +i))
    {
        j = 0;
        while(*(needle+j) && *(haystack+i+j) && *(haystack+j+i) == *(needle+j))
        /* keep running as long as haystack and neelde is not '\0', and equal */
        {     
              ++j;     
        }
        if (!*(needle+j))
              {
                  return  (char *)(haystack+i);
              }
        ++i;
    }
    return NULL;
}

/*eleventh- strspn*/
size_t Strspn(const char *s, const char *accept)
{
    size_t len = 0;
    int i, j = 0;
    for ( i = 0; s[i] != '\0' ; i++ )
    {
        for( j = 0; j<accept[j]; j++ ) 
        {
            if (s[i] == accept[j])
            {
                ++len;
                break;
            }
        }
        if (!accept[j])
        {
            break;
        }
        
    }
    return len;
}


/*twelveth- Strtok*/
int TheDelim(char ch, const char *delim)
{
    int i = 0;
    while(delim[i]!='\0')
    {
        if(delim[i] == ch)
        {
            return 1; /*if it is the delim*/
        }
        i++;
    }
    return 0; /*if not the delim*/
}

char *Strtok(char *str, const char *delim)
{
    static char *token;
    int i;
    
    if (str == NULL)
    {
        str = token;
        if (token == NULL)
        {
            return NULL;
        }
    }
    token = '\0';
    for ( i = 0; i < str[i]; i++ )
    {
        if ( 1 == TheDelim(str[i], delim))
        {
            str[i] = '\0';
            token = str + i + 1;
            
            return str;
        }
    }
    return str;
}






