/*Dani Benjamin.
reviewer: Ayala Rosel.
modification date: 23.3.19*/ 

#include <stdio.h> /*printf*/

#define SIZE_VAR(x) (char*)(&x)-(char*)(&x-1)

#define SIZE_TYPE(x) (size_t)(((x*)(1)) + 1)-(size_t)((x*)(1))
                    
                    

int main(void)
{
    int int_num = 6;
    struct testing
    {
        int struct_int;
        char struct_char;
        long int struct_long;
    }test;
    
    printf("the size of: %d:\nmy size: %ld\n",int_num, SIZE_VAR(int_num));
    printf("sizeof: %ld\n\n", sizeof(int_num));
    
    printf("the size of: struct:\nmy size: %ld\n",SIZE_VAR(test));
    printf("sizeof: %ld\n\n", sizeof(test));\
    
    printf("my size of type: %ld\n", SIZE_TYPE(int));
    printf("sizeof: %ld\n\n", sizeof(int));
    
    return 0;
}


