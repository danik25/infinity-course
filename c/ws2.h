#ifndef _WS2_H_
#define _WS2_H_

/*first- Strlen*/
size_t Strlen(const char *s);

/*second- Strcmp*/
int Strcmp(const char *s1, const char *s2);

/*third- Strcpy*/
char *Strcpy(char *dest, const char *src);

/*fourth- Strncpy*/
char *Strncpy(char *dest, const char *src, size_t n);

/*fifth- Strcasecmp*/
int Strcasecmp (const char *s1, const char *s2);

/*sixth- strchr*/
char *Strchr(const char *str, int c);

/*seventh - strdup*/
char *Strdup (const char *s);

/*eighth- strcat*/
char *Strcat(char *dest, const char *src);

/*ninth-strncat*/
char *Strncat(char *dest, const char *src, size_t n);

/*tenth-strncat*/
char *Strstr(const char *haystack, const char *needle);

/*eleventh- strspn*/
size_t Strspn(const char *s, const char *accept);

/*twelveth- Strtok*/
int TheDelim(char ch, const char *delim);
char *Strtok(char *str, const char *delim);

/*palindrom*/
int IsPalindrom(const char *str);

/*7 BOOM*/
void Boom(int start, int end);

/*swap pointers*/
void SwapP(int **ptr1, int **ptr2);

/*White spaces*/
void *WhiteSpace(char * str);

/*Large numbers*/
char *LargeNumbers(char * num1, char * num2);

#endif




