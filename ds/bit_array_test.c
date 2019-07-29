#include <stdio.h>

#include "bit_array.h"

static void AllOnTest();
static void AllOffTest();
static void SetOnTest();
static void SetOffTest();
static void SetBitTest();
static void IsOnTest();
static void IsOffTest();
static void FlipBitTest();
static void RotateLeftTest();
static void RotateRightTest();
static void MirrorTest();
static void CountOnTest();
static void CountOffTest();
static void CountBitsLUTTest();
static void MirrorBitsLUTTest();

static void PrintBit64(unsigned long int num);


int main(void)
{
    AllOnTest();
    AllOffTest();
    SetOnTest();
    SetOffTest();
    SetBitTest();
    IsOnTest();
    IsOffTest();
    FlipBitTest();
    RotateLeftTest();
    RotateRightTest();
    MirrorTest();
    CountOnTest();
    CountOffTest();
    CountBitsLUTTest();
    MirrorBitsLUTTest();
    
    return 0;
}

static void AllOnTest()
{
    unsigned long int num = 18;
    printf("\n*****all on*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = AllOn(num);
    printf("after turning on:\n");
    PrintBit64(num);
}

static void AllOffTest()
{
    unsigned long int num = 18;
    printf("\n*****all off*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = AllOff(num);
    printf("after turning off:\n");
    PrintBit64(num);
}

static void SetOnTest()
{
    unsigned long int num = 63;
    size_t index = 60;
    
    printf("\n*****set on*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = SetOn(num, index);
    printf("after setting on index %ld, we get number: %lu\n", index, num);
    PrintBit64(num);
}

static void SetOffTest()
{
    unsigned long int num = 18;
    size_t index = 3;
    
    printf("\n*****set off*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = SetOff(num, index);
    printf("after setting off index %ld, we get number: %lu\n", index, num);
    PrintBit64(num);
}

static void SetBitTest()
{
    unsigned long int num = 18;
    size_t index = 2;
    char stat = 1;
    
    printf("\n*****set bit*****\n");
    printf("befor, binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = SetBit(num, index, stat);
    printf("after setting bit index %ld to-%d, we get number: %lu\n", index ,stat, num);
    PrintBit64(num);
}

static void IsOnTest()
{
    unsigned long int num = 18;
    size_t index = 2;
    
    printf("\n*****is on*****\n");
    printf("binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("is index number %ld on? \n", index);
    IsOn(num, index) ? printf("yes\n") : printf ("no\n");
}

static void IsOffTest()
{
    unsigned long int num = 18;
    size_t index = 2;
    
    printf("\n*****is off*****\n");
    printf("binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("is index number %ld off? \n", index);
    IsOn(num, index) ? printf ("no\n") : printf("yes\n");
}

static void FlipBitTest()
{
    unsigned long int num = 18;
    size_t index = 4;
    
    printf("\n*****flip bit*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    num = FlipBit(num, index);
    printf("after flipping index: %ld:, we get number: %lu\n", index, num);
    PrintBit64(num);
}

static void RotateLeftTest()
{
    size_t offset = 2;
    unsigned long int num = 1556444031214176;
    
    printf("\n*****rotate left*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    
    num = RotateLeft(num, offset);
    printf("after a rotation of: %ld to the left:, we get number: %lu\n", 
                                                            offset, num);
    PrintBit64(num);
}

static void RotateRightTest()
{
    size_t offset = 2;
    unsigned long int num = 32789;

    printf("\n*****rotate right*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    num = RotateRight(num, offset);
    printf("after a rotation of: %ld to the right:, we get number: %lu\n", 
                                                            offset, num);
    PrintBit64(num);
}

static void MirrorTest()
{
    unsigned long int num = 25;

    printf("\n*****Mirror*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    num = Mirror(num);
    printf("after mirroring, we get number: %lu\n", num);
    PrintBit64(num);
}

static void CountOnTest()
{
    unsigned long int num = 34;

    printf("\n*****count bit on*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    printf("the number of set bit:%ld \n\n",CountOn(num));
}

static void CountOffTest()
{
    unsigned long int num = 16;

    printf("\n*****count bit off*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    printf("the number of non-set bit:%ld \n\n",CountOff(num));
}

static void CountBitsLUTTest()
{
    unsigned long int num = 1;
    num <<= 63;

    printf("\n*****count bit on with a LUT*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    printf("the number of set bit:%ld \n\n",CountBitsLUT(num));
}

static void MirrorBitsLUTTest()
{
    unsigned long int num = 72340172838076673;

    printf("\n*****miroor with a LUT*****\n");
    printf("befor,binary representaton of number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
    num = MirrorBitsLUT(num);
    printf("after mirroring, we get number: %lu\n", num);
    PrintBit64(num);
    printf("\n");
}

static void PrintBit64(unsigned long int num)
{
    unsigned long i = 1;
    
    int cnt = 0;
    
    /*binary representation by 64 bits*/
    for (i <<= 63; i > 0; i >>= 1) 
    {
        if (cnt % 8 == 0 && cnt != 0)
        {
            printf(" ");
        }
        (num & i)? printf("1"): printf("0");
        ++cnt; 
    }
    printf("\n");
    cnt = 63;
    /*prints the index for convenience*/
    for (i = 1UL << 63; i > 0; i = i / 2) 
    {
        if (cnt < 10 )
        {
            printf("%d", cnt);
        }
        else
        {
            printf(".");
        }
        if (00 == cnt % 8 && cnt != 0)
        {
            printf(" ");
        }
        --cnt; 
    }
    printf("\n");  
}

