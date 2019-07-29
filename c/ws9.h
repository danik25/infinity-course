#ifndef _WS9_H_
#define _WS9_H_

/*writer: Dani Benjamin.
reviewer: Oded Bryt.
last modification: 24.3.19*/

/*copies the character c to the first n characters of the string pointed to, by 
the argument str.*/
void *Memset(void *str, int c, size_t n);

/*copies n characters from memory area str2 to memory area str1*/
void *Memcpy(void *dest, const void *src, size_t n);

/*copies n bytes from memory area src to memory area dest. The memory areas may 
overlap: copying takes place as though the bytes in src are first copied into a 
temporary array that does not overlap src or dest, and the bytes are then copied
from  the  temporary array to dest.*/ 
void *Memmove(void *dest, const void *src, size_t n);

/*converts int data type to string data type*/
char *Itoa( int value, char * str, int base );

/*converts the string argument str to an integer (type int).*/
int Atoi(const char *str, int base);

/*a function that prints the letters appearing in the first and second arrays,
but not the third*/
void ThreeArrays(char * arr1, char *arr2, char *arr3, int size1, int size2,
                                                                int size3);
/*check he endian type of the computer*/
void Endian();

#endif /*_WS9_H*/
