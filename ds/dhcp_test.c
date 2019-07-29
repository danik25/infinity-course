/****************************************************************
*                <<<<<<<< DHCP >>>>>>>>                         *
* Related files: dhcp.c, dhcp_test.c                            *
* #Version: V 1.3                                               *
* Writer: Dani Benjamim                                         *   
* Reviewer: Ayala Rosel                                         *
* Last update: 18/06/19                                         *
****************************************************************/ 
#include <stdio.h> /* printf */
#include <math.h> /* pow */

#include "dhcp.h"
#include "dani_utilities.h"

#define ITER 5

static void TestDhcp();

static void TestCreate();
static void TestAlloc();
static void TestFree();
static void TestCount();
static void Integration();

static void PrintTmp(unsigned char array[]);
static int ArrayCmp(unsigned char array1[], unsigned char array2[]);

int main()
{
    CYAN("\n\n\t\t~TEST FILE DHCP~");
    CYAN("\n\n\t\t Dani Benjamin\n\n");

    TestDhcp();

    CYAN("\n\n\t\t   ~THE END~\n\n");
    return(0);
}

static void TestDhcp()
{
    
    YELLOW("********create********\n");
    TestCreate();
    YELLOW("\n********alloc********\n");
    TestAlloc();
    YELLOW("\n********free********\n");
    TestFree();
    YELLOW("\n********count********\n");
    TestCount();
    YELLOW("\n********integration********\n");
    Integration();
    
}

static void TestCreate()
{
    unsigned char network_ip[IP_BYTES_SIZE] = {10, 3, 4, 0};
    DHCP_t *new_dhcp = DHCPCreate(network_ip, 2);

    TEST(new_dhcp);
    DHCPDestroy(new_dhcp);
}

static void TestAlloc()
{
    unsigned char network_ip[IP_BYTES_SIZE] = {10, 3, 5, 0};

    unsigned char desired_ip[3][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 0},
                                                {10, 3, 5, 2},
                                                {10, 3, 5, 255},
                                                };
    unsigned char exp[3][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 1},
                                                {10, 3, 5, 2},
                                                {10, 3, 5, 3}
                                                };


    unsigned char alloced[3][IP_BYTES_SIZE] = {{0}, {0}, {0}};

    DHCP_t *new_dhcp = DHCPCreate(network_ip, 3);

    PURPLE("\n1. attempt to allocate saved path\n");
    TEST(!DHCPAllocIP(new_dhcp, desired_ip[0], alloced[0]));
    TEST(ArrayCmp(alloced[0], exp[0]));
    PrintTmp(alloced[0]);

    PURPLE("\n2. attempt to allocate unsaved path\n");
    TEST(!DHCPAllocIP(new_dhcp, desired_ip[1], alloced[1]));
    TEST(ArrayCmp(alloced[1], exp[1]));
    PrintTmp(alloced[1]);

    PURPLE("\n3. attempt to allocate the biggest saved path\n");
    TEST(DHCPAllocIP(new_dhcp, desired_ip[2], alloced[2]));
    PrintTmp(alloced[2]);

    PURPLE("\n4. using NULL\n");
    TEST(!DHCPAllocIP(new_dhcp, NULL, alloced[2]));
    TEST(ArrayCmp(alloced[2], exp[2]));
    PrintTmp(alloced[2]);

    DHCPDestroy(new_dhcp);
}

static void TestFree()
{
    unsigned char network_ip[IP_BYTES_SIZE] = {10, 3, 5, 0};

    unsigned char desired_ip[3][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 1},
                                                {10, 3, 5, 0},
                                                {10, 3, 5, 0}
                                                };

    unsigned char exp[2][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 2},
                                                {10, 3, 5, 1}
                                                };
                                                                                            
    unsigned char alloced[3][IP_BYTES_SIZE] = {{0}, {0}, {0}};

    unsigned char free_req[IP_BYTES_SIZE] = {10, 3, 5, 1};

    DHCP_t *new_dhcp = DHCPCreate(network_ip, 3);

    printf("allocation of 1:\n");
    DHCPAllocIP(new_dhcp, desired_ip[0], alloced[0]);
    PrintTmp(alloced[0]);

    printf("\nattempt to allocate 0, 2 expected:\n");
    DHCPAllocIP(new_dhcp, desired_ip[1], alloced[1]);
    TEST(ArrayCmp(alloced[1], exp[0]));
    PrintTmp(alloced[1]);

    printf("\nfreeing 1....\n");
    DHCPFreeIP(new_dhcp, free_req);

    printf("\nanother attempt to allocate 0, 1 expected:\n");
    DHCPAllocIP(new_dhcp, desired_ip[2], alloced[2]);
    TEST(ArrayCmp(alloced[2], exp[1]));
    PrintTmp(alloced[2]);

    DHCPDestroy(new_dhcp);
}

static void TestCount()
{
    int i = 0;
    int status = 0;
    size_t max = pow(2, 8) - 3;
    unsigned char network_ip[IP_BYTES_SIZE] = {10, 3, 5, 0};

    unsigned char desired_ip1[IP_BYTES_SIZE] = {10, 3, 5, 0};
    unsigned char alloced[IP_BYTES_SIZE] = {0};

    DHCP_t *new_dhcp = DHCPCreate(network_ip, 3);

    for( i = 0; i < 5; ++i)
    {
        if(DHCPCountFree(new_dhcp) != max - i)
        {
            status = 1;
        }
        DHCPAllocIP(new_dhcp, desired_ip1, alloced);
        PrintTmp(alloced);
    }

    TEST(!status);
    DHCPDestroy(new_dhcp);
}

static void Integration()
{
    unsigned char network_ip[IP_BYTES_SIZE] = {10, 3, 5, 0};

    size_t i = 0;
    int status = 0;

    unsigned char desired_ip[ITER][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 0},
                                                {10, 3, 5, 5},
                                                {10, 3, 5, 255},
                                                {10, 3, 5, 10},
                                                {10, 3, 5, 1},
                                                };
    unsigned char exp[ITER][IP_BYTES_SIZE] = 
                                                {
                                                {10, 3, 5, 1},
                                                {10, 3, 5, 5},
                                                {0},
                                                {10, 3, 5, 10},
                                                {10, 3, 5, 2},
                                                };

    unsigned char alloced[ITER][IP_BYTES_SIZE] = {{0}, {0}, {0}, {0}, {0}};
    unsigned char not_exists[IP_BYTES_SIZE] = {10, 3, 5, 7};
    int exp_count[ITER] = {1, 2, 2, 3, 4};
    size_t exp_count_after_removal[ITER] = {250, 251, 251, 252, 253};

    DHCP_t *new_dhcp = DHCPCreate(network_ip, 3);
    size_t max = pow(2, 8) - 3;
    PURPLE("allocation and count\n");
    for(i = 0; i < ITER; ++i)
    {
        if(SUCCESS == DHCPAllocIP(new_dhcp, desired_ip[i], alloced[i]))
        {
            PrintTmp(alloced[i]);
            if(!ArrayCmp(alloced[i], exp[i]))
            {
                status = 1;
            }
        }
        if(DHCPCountFree(new_dhcp) != max - exp_count[i])
        {
            status = 1;
        }
    }
    TEST(!status);

    PURPLE("\nremoval of a non existing ip\n");
    DHCPFreeIP(new_dhcp, not_exists);
    TEST(DHCPCountFree(new_dhcp) == max - exp_count[i - 1]);

    PURPLE("\nremoval of allocated ip\n");
    for(i = 0; i < ITER; ++i)
    {
        if(SUCCESS == DHCPFreeIP(new_dhcp, alloced[i]))
        {
            if(DHCPCountFree(new_dhcp) != exp_count_after_removal[i])
            {
                status = 1;
            }
        }
    }
    TEST(!status);

    DHCPDestroy(new_dhcp);
}


/*============================ users functions ============================*/

static void PrintTmp(unsigned char array[])
{
    size_t i = 0;
    for(i = 0; i < IP_BYTES_SIZE; ++i)
    {
        printf("%u . ", array[i]);
    }
    printf("\n");
}

static int ArrayCmp(unsigned char array1[], unsigned char array2[])
{
    size_t i = 0;
    for(i = 0; i < IP_BYTES_SIZE; ++i)
    {
        if(array1[i] != array2[i])
        {
            return(0);
        }
    }
    return(1);
}
