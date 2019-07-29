#include <stdio.h> /*printf*/

#define ARRAY_SIZE 256

static unsigned char CountOn1(unsigned char num);
static unsigned char MirrorByte(unsigned char num);
/* check the "fprintf" function for strings */
static void CheckFprintf(char *str, FILE *fptr);

int main()
{
    unsigned char i = 0;
    FILE *fptr = fopen("prep_lut.h", "w+");  
      
    /* fopen testing */
    if(NULL == fptr) 
    {
        printf("unsuccessfull open of a file");
        return 1;
    }
    
    /* writing preprocessor commands */
    CheckFprintf("#ifndef _PREP_LUT_H_\n", fptr); 
    CheckFprintf("#define _PREP_LUT_H_\n\n", fptr);
    
    /* creating count lut */
    CheckFprintf("unsigned char count_arr[256] = {\n", fptr);  
    for (i = 0; i < ARRAY_SIZE - 1; ++i)
    {
        if (0 == i % 16 && i != 0)
        {
            CheckFprintf("\n", fptr);
        }
        if (fprintf(fptr, "%d, ",CountOn1(i)) == 0)
        {
            printf("unsuccessfull writing to a file\n");
            return 1;
        }
    }
    if (fprintf(fptr, "%d\n};\n\n",CountOn1(i)) == 0)
        {
            printf("unsuccessfull writing to a file\n");
            return 1;
        }
    
    /* creating mirror lut */
    CheckFprintf("unsigned char mirror_arr[256] = {\n", fptr);
    
    for (i = 0; i < ARRAY_SIZE - 1; ++i)
    {
        if (0 == i % 16 && i != 0)
        {
            CheckFprintf("\n", fptr);
        }
        if (fprintf(fptr, "%d, ",MirrorByte(i)) == 0)
        {
            printf("unsuccessfull writing to a file\n");
            return 1;
        }
    }
    
    if (fprintf(fptr, "%d\n};\n",MirrorByte(i)) == 0)
    {
        printf("unsuccessfull writing to a file\n");
        return 1;
    }
    
    /* writing includes to the file */
    CheckFprintf("\n#endif /*_PREP_LUT_H_*/", fptr); 
    
    /* fclose testing */
    if( EOF == fclose(fptr)) 
    {
        printf("unsuccessfull closing of file\n");
        return 1;
    }
    
    return 0;
}

static void CheckFprintf(char *str, FILE *fptr)
{
    if (fprintf(fptr, "%s",str) == 0)
    {
        printf("unsuccessfull writing to a file\n");
        return;
    }    
}

static unsigned char CountOn1(unsigned char num)
{    
    num = (num & (0x55)) + ((num >> 1) & (0x55));
    num = (num & (0x33)) + ((num >> 2) & (0x33));
    num = (num & (0xF)) + ((num >> 4) & (0xF));

    return num;
}

static unsigned char MirrorByte(unsigned char num)
{
    num = num >> 4 | num << 4; /*swapping two halfes*/
    num = (num & 0xcc) >> 2 | ((num << 2) & 0xcc); /*swapping paires*/
    num = (num & 0xaa) >> 1|((num << 1) & 0xaa); /*swapping individuals*/
    return num;
}
