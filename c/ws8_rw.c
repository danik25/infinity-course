/*Dani Benjamin.
reviewer: Ayala Rosel.
modification date: 23.3.19*/


#include <stdio.h> /*printf, scanf*/
#include <stdlib.h> /*exit*/

int main(void)
{
    int i = 0;
    typedef struct
    {
        size_t day;
        size_t month;
        size_t year;
    }DateOfBirth;
    
    typedef struct
    {
        char f_name[50];
        char l_name[50];
        DateOfBirth dob;
        size_t ID;
    }Contact;
    
    Contact arr_read[10] = {0};    
        
    Contact arr_write[10] = 
    {{"Joey","Tribbiani", {1,1,2000},1234},
    {"Phoebe", "Buffay", {2,1,2000},1235},
    {"Ross", "Geller", {3,1,2000},1236},
    {"Matthew", "Perry", {4,1,2000},1237},
    {"Rachel", "Green", {5,1,2000},1238},
    {"Monica", "Geller", {6,1,2000},1239},
    {"Gunther", "Something", {7,1,2000},1240},
    {"Marcel", "Monkey", {8,1,2000},1241},
    {"Janice", "Goralnik", {9,1,2000},1242},
    {"Emily", "Waltham", {10,1,2000},1243}
    };
    
    FILE *fptr = fopen("friends.txt", "w+");
    
    /* fopen testing */
    if(NULL == fptr) 
        {
            printf("unsuccessfull open of a file");
            exit(1);
        }
        
    /* fwrite testing */
    if (fwrite(&arr_write, sizeof(Contact), 10, fptr) != 10)
    {
        printf("unsuccessfull write to a file");
        exit(1);
    }
    /* getting back to the beginning of the file */
    fseek(fptr, 0, SEEK_SET);
    
    /* fread testing */
    if (fread(&arr_read, sizeof(Contact), 10, fptr) != 10)
    {
        printf("unsuccessfull read of a file");
        exit(1);
    }
    
    /* printing for the comfert of the testing */
    for(i = 0; i < 10; ++i)
    {
        printf ("name = %s, last name = %s, , id: %ld\n",
        arr_read[i].f_name, arr_read[i].l_name, arr_read[i].ID); 
        printf("date of birth: %ld/%ld/"
        "%ld\n\n",arr_read[i].dob.day,arr_read[i].dob.month,
        arr_read[i].dob.year);
        
    }
    /* fclose testing */
    if( EOF == fclose(fptr) ) 
    {
        printf("unsuccessfull closing of file");
        exit(1);
    }
    
    return 0;
} 
