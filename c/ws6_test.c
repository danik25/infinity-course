#include <stdio.h>
#include "ws6.h"

<<<<<<< HEAD
void TestPow2();
void TestPowerOfTwo();
void TestAddsOne();
void TestThreeBits();
void TestRev();
void TestWithoutIf();
void TestDivided();
=======
/*assisting function for printing the binary representation*/
static void PrintBit32(unsigned int num);
static void PrintBit8(unsigned char ch);

static void TestPow2();
static void TestPowerOfTwo();
static void TestAddsOne();
static void TestThreeBits();
static void TestRev();
static void TestWithoutIf();
static void TestDivided();
static void TestSwap();
static void TestCount();
static void TestFloat();
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1

int main()
{
    TestPow2();
    TestPowerOfTwo();
    TestAddsOne();
    TestThreeBits();
    TestRev();
    TestWithoutIf();
    TestDivided();
<<<<<<< HEAD
=======
    TestSwap();
    TestCount();
    TestFloat();
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    
    return 0;
}

void TestPow2()
{
<<<<<<< HEAD
	unsigned int x=3;
    int y=3;
=======
	unsigned int x = 3;
    int y = 3;
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
	printf("*****x*2^y*****\n");
   /*x multiplied by 2 by the power of two*/
    printf("%u multiplied by: %d powered by:%d is:%d\n",x,2,y, Pow2(x, y));
    printf("\n\n");
}

void TestPowerOfTwo()
{
<<<<<<< HEAD
	unsigned num=1;
=======
	unsigned num = 1;
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
	printf("*****is power of two*****\n");
	/*is num a power of two?*/
    printf("is %u is a power of 2?, 1-YES, 0- NO\n",num);
    printf("loop way: %d\n", PowerLoop(num));
    printf("no loop way: %d\n", PowerNoLoop(num));
    printf("\n\n");
}

void TestAddsOne()
{
<<<<<<< HEAD
	unsigned num=1;
=======
	unsigned num = 1;
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
	printf("*****add one to a number*****\n");
	printf("%u+1 is:%d\n",num, Add(num));
	printf("\n\n");
}

void TestThreeBits()
{
<<<<<<< HEAD
    unsigned int i;
=======
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    unsigned int arr[] = {1,2,7,8,11,25};
    int size = sizeof(arr)/sizeof(unsigned int);
    unsigned int *arr_copy = arr;
    
    printf("*****numbers with 3 bits*****\n");
<<<<<<< HEAD
    /*printing the number a s bits for convenience*/
    while (size>0)
    {
        printf("%d in binary is:\n", *arr_copy);
        for (i = 1 << 31; i > 0; i = i / 2) 
        {
            (*arr_copy & i)? printf("1"): printf("0"); 
        }
=======
    
    while (size > 0)
    {
        printf("binary representatin of: %d, is:\n", *arr_copy);
        PrintBit32(*arr_copy); /*printing the number as bits for          
                                                convenience*/
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
        printf("\n");
        ++arr_copy;
        --size;
    }
<<<<<<< HEAD
    printf("\n\n");
    ThreeBits(arr, sizeof(arr)/sizeof(unsigned int));
=======
    size = sizeof(arr)/sizeof(unsigned int);
    printf("\n\n");
    ThreeBits(arr, size);
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    printf("\n\n");
}

void TestRev()
{
<<<<<<< HEAD
    unsigned int i;
    unsigned int num = 7;
    
    printf("*****reverese bits*****\n");
    
    printf("binary for %u:\n",num);
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
        (num & i)? printf("1"): printf("0"); 
    }
    
    printf("\n");
   
    printf("reverse:\n");
    Mirror(num);
=======
    unsigned int num = 127;
    
    printf("*****reverese bits*****\n");
    printf("binary representatin of: %d, is:\n", num);
    PrintBit8(num);
   
    printf("reverse:\n");
    PrintBit8(Mirror(num));
    printf("\n");
    
    printf("and without a loop: \n");
    PrintBit8(MirrorNoLoop(num)); /*printing the number as bits*/
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    printf("\n\n\n");
}

void TestWithoutIf()
{
<<<<<<< HEAD
    unsigned int num = 9;
    unsigned int new_num;
    
    printf("*****without if's*****\n");
    
    PrintBit(num);

    (TwoAndSix(num))?printf("2 and 6 indexes are both ON\n"):printf("at least 2 or 6 are OFF\n");
    printf("\n\n");
    (TwoOrSix(num))?printf("2 or 6 indexes are ON\n"):printf("2 and six are both OFF\n");
    
    printf("\nafter a swap of %u:\n",num);
    new_num=SwapThreeAndFive(num);
    PrintBit(new_num);
    printf("\n\n\n");
    
=======
    unsigned char ch = ',';
    
    printf("*****without if's*****\n");
    printf("binary representatin of: '%c', is:\n", ch);
    PrintBit8(ch); /*printing the number as bits*/
    printf("\n");
    
    (TwoAndSix(ch))?printf("2 and 6 indexes are both ON\n"):
                printf("at least 2 or 6 are OFF\n");
    printf("\n\n");
    (TwoOrSix(ch))?printf("2 or 6 indexes are ON\n"):
                printf("2 and 6 are both OFF\n");
    

    printf("\nafter a swap of 3 and 5: %u:\n",SwapThreeAndFive(ch));
    PrintBit8(SwapThreeAndFive(ch)); /*printing the number as bits*/
    printf("\n\n\n");
    
    PrintBit8(Function3(ch));
    
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
}

void TestDivided()
{
    unsigned int num = 115;
    printf("*****divided by 16*****\n");
<<<<<<< HEAD
    printf("the closest number to: %u, that is divided by 16 is: %u\n", num, DividedSixteen(num));
=======
    printf("the closest number to: %u, that is divided by 16 is: %u\n",
                num, DividedSixteen(num));
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    printf("\n\n\n");
    
}

<<<<<<< HEAD



=======
void TestSwap()
{
    unsigned int num1 = 7;
    unsigned int num2 = 12;
    printf("*****swapping numbers*****\n");
    printf("befor the swap- number 1 :%u, number 2: %u\n", num1, num2);
    Swap(&num1, &num2);
    printf("after the swap- number 1 :%u, number 2: %u\n", num1, num2);
    printf("\n\n\n");
}

void TestCount()
{
    unsigned int num = 7;
    printf("*****set bits*****\n");
    printf("binary representatin of: %d, is:\n", num);
    PrintBit32(num); /*printing the number as bits*/
    printf("loop way:\n");
    printf("the number of set bits in %u, is:%d\n", num, CountSet(num));
    printf("no loop way:\n");
    printf("answer: %d\n", CountSetNoLoop(num));
    printf("\n\n\n");
    
}

void TestFloat()
{
    float num = 5.5;
    printf("*****print a float*****\n");
    printf("the binary representation of the float number: %.2f, is: \n"
                            ,num);
    PrintBit32(FloatPrint(num)); /*printing the number as bits*/
    printf("\n\n\n");
}

void PrintBit32(unsigned int num)
{
    unsigned int i;
    
    /*binary representation by 32 bits*/
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
        (num & i)? printf("1"): printf("0"); 
    }
    printf("\n");
    
}

void PrintBit8(unsigned char ch)
{
    unsigned int i;
    
    /*binary representation by 8 bits*/
    for (i = 1 << 7; i > 0; i = i / 2) 
    {
        (ch & i)? printf("1"): printf("0"); 
    }
    printf("\n");
    
}
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1


