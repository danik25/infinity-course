/*Dani Benjamin.
reviewer: Ayala Rosel.
modification date: 23.3.19*/

#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, realloc*/
#include <string.h>
#include <assert.h> /*assert*/

#define UNUSED(x) (void)(x)


/*add functions decleration*/
void AddInt (void **data, void *data2);
void AddFloat (void **data, void *data2);
void AddString (void **data, void *data2);

/*print functions decleration*/
void PrintInt (void *data);
void PrintFloat (void *data);
void PrintString (void *data);

/*free functions decleration*/
void FreeInt (void *data);
void FreeFloat (void *data);
void FreeString (void *data);


int main (void)
{
    int i = 0;
  
    /*first struct values*/
    int int_num = 5;
    float float_num = 5.5;
  
    /*second struct values*/
    int int_num2 = 6;
    float float_num2 = 6.5;
    char *str2= "benjamin";
  
    typedef struct 
    {
        void *data;
        void (*add) (void **data, void *data2);
        void (*print) (void *data);
        void (*free_memory) (void *data);

    } elements;

    elements array[3] =
    {
    {0, AddInt, PrintInt, FreeInt},
    {0, AddFloat, PrintFloat, FreeFloat},
    {0, AddString, PrintString, FreeString}
    };

    /*struct for the added values*/
    typedef struct 
    {
        void *data2;
    }elements2; 

    elements2 array2[3] ={{0},{0},{0}};
  
    char *str = (char*) malloc(100*sizeof(char));
    
    
    /* memory allocation testing */
    if (str == NULL) 
    {
  		fprintf("unsuccessfull memory allocation");
  		exit(1);
	}
    
    strcpy(str,"dani");
  
    /*first struct assignment*/
    array[0].data = &int_num;
    array[1].data = &float_num;
    array[2].data = str;
  
    /*second struct assignment*/
    array2[0].data2 = &int_num2;
    array2[1].data2 = &float_num2;
    array2[2].data2 = str2;
  
  
  
    for (i = 0; i < 3; ++i)
        {
            printf("the variables:\n");
            array[i].print (array[i].data);
            array[i].print (array2[i].data2);
            array[i].add (&array[i].data, array2[i].data2 );
            printf("the variables after the 'add' proccess:\n");
            array[i].print (array[i].data);
            array[i].free_memory (array[i].data);
            printf("\n");
        }

    return 0;
}

/*add functions*/
void AddInt (void **data, void *data2)
{
    assert(data);
    assert(data2);
    **(int **) data += *(int *) data2;
}

void AddFloat (void **data, void *data2)
{
    assert(data);
    assert(data2);
    **(float **) data += *(float *) data2;
}

void AddString (void **data, void *data2)
{
     assert(data);
     assert(data2);
     *(char**)data= realloc(*(char**)data, strlen(*(char**)data)
                                            +strlen((char*)data2)+1);
     strcat(*(char**)data, (char*)data2);
}

/*print functions*/
void PrintInt (void *data)
{
    assert(data);
    printf ("%d\n", *(int *) data);
}

void PrintFloat (void *data)
{
    assert(data);
    printf ("%.2f\n", *(float *) data);
}

void PrintString (void *data)
{
    assert(data);
    printf ("%s\n", (char *)data);
}

/*free functions*/
void FreeInt (void *data)
{
    assert(data);
    UNUSED(data);
}

void FreeFloat (void *data)
{
    assert(data);
    UNUSED(data);
}

void FreeString (void *data)
{
    assert(data);
    free(data);
    data = NULL;
}





