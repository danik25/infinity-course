#include <stdio.h> /*printf*/
#include <stdlib.h> /*exit*/
#include "ws5.h" 

int main(int argc, char *argv[])
{ 
    if( argc < 2 )
    {
        printf("no file!\n");
        exit(1);
    }
    Logger(argv[1]);
    return 0;
}
