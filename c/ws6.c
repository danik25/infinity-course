#include <stdio.h>

unsigned int Pow2(unsigned int x, int y)
{
    if(y < 0)
    {
        y *= -1;
        return x >> y;
    }
    return x << y;
}

unsigned int PowerLoop(unsigned int num)
{
    while(num > 0 && num != 1)
    {
        /*if the number is uneven, return false*/
        if(num%2 != 0)
        {
            return 0;
        }
        num >>= 1;
    }
    return 1;
}
unsigned int PowerNoLoop(unsigned int num)
{
    if (num & (num-1))
    {
        return 0; /*return false*/
    }
    return 1; /*return true*/
}

unsigned int Add(unsigned int num)
{
    return -(~num);
}

void ThreeBits(unsigned int *arr, int size)
{
<<<<<<< HEAD
    int cnt=0;
    unsigned int num;
    while (size>0)
    {
        num = *arr;
        while(num!=0)
=======
    int cnt = 0;
    unsigned int num;
    while (size > 0)
    {
        num = *arr;
        while(num != 0)
        {
            if(num%2 != 0) /*if there in "1" at the begining*/
            {
                ++cnt;
            }
            num >>= 1;
        }
        if( 3 == cnt )
        {
            printf("number with 3 bits:%u\n",*arr);
        }
        --size;
        ++arr;
        cnt = 0;
    }   
}

unsigned int Mirror(unsigned int num)
{
    unsigned int i = 7;
    unsigned int n = 0;
    while(i>0)
    {
        n += num&1;
        num >>= 1;
        n <<= 1;
        --i;  
    }
    n += num&1;
    return n;
	
}

unsigned int MirrorNoLoop(unsigned int num)
{
    num = num >> 4 | num << 4; /*swapping two halfes*/
    num = (num & 0xcc) >> 2 | ((num << 2) & 0xcc); /*swapping paires*/
    num = (num & 0xaa) >> 1|((num << 1) & 0xaa); /*swapping individuals*/
    return num;
}


int TwoAndSix(unsigned char ch)
{
    return !!((ch & 1 << 2) & (ch & 1 << 6)); 
}
int TwoOrSix(unsigned char ch)
{
    return !!((ch & 1 << 2) | (ch & 1 << 6)); 
}
int SwapThreeAndFive(unsigned char ch)
{
    unsigned char ch_zero= ch&(~40); /*40 = bits number 3 + 5 are on*/
    unsigned char three = ch&(1 << 3);
    unsigned char five = ch&(1 << 5);
    unsigned char all;
    three <<= 2;
    five >>= 2;
    all = three|five;
    return ch_zero|all;
}

unsigned int DividedSixteen(unsigned int num)
{
    unsigned int ans =~ 15; /*zero for 1-8*/
    return num&ans;
}

void Swap(unsigned int *num1, unsigned int *num2)
{
    *num1 ^= *num2;
    *num2 ^= *num1;
    *num1 ^= *num2;
}

int CountSet(unsigned int num)
{
    int cnt = 0;
    while(num > 0)
    {
        if(num&1) /*if there in "1" at the begining*/
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
        {
            if(num%2!=0)
            {
                ++cnt;
                if( cnt == 3 )
       			{
            		break;
        		}
            }
            num>>=1;
        }
<<<<<<< HEAD
        if( cnt == 3 )
        {
            printf("number with 3 bits:%u\n",*arr);
        }
        --size;
        ++arr;
        cnt=0;
    }   
}

void Mirror(unsigned int num)
{
    unsigned int i=31;
    unsigned int n=0;
    while(i>0)
    {
        n+=num&1;
        num>>=1;
        n<<=1;
        --i;
    }
	
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
        (n & i)? printf("1"): printf("0"); 
=======
        num >>= 1;
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1
    }
   
}

<<<<<<< HEAD
void PrintBit(unsigned int num)
{
    unsigned int i;
    printf("binary representatin of: %u\n", num);
    /*binary representation*/
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
        (num & i)? printf("1"): printf("0"); 
    }
    printf("\n");
    /*
    printf("bits ");
    for (i = 1 << 31; i > 0; i = i / 2) 
    {
        if(i<32)
        {
            printf("%u", i);
        }
        else
        {
            printf(" ");
        }
    }
    
    printf("\n");
    printf("index: ");
    for (i = 32; i > 0; --i) 
    {
    	if(i<20)
        {
            printf("%u", i);
        }
        else
        {
            printf(" ");
        } 
    }
    printf("\n\n");*/
    
}

int TwoAndSix(unsigned int num)
{
    PrintBit(68);
    return num>=68; /*bit number 6 + bit number 2*/
}
int TwoOrSix(unsigned int num)
{
    PrintBit(34);
    return num&34;
}
int SwapThreeAndFive(unsigned int num)
{
    return num^=40; /*bits number 3+5 are on*/
}

unsigned DividedSixteen(unsigned int num)
{
    unsigned int ans=~15; /*zero for 1-8*/
    return num&ans;
}


=======
int CountSetNoLoop(unsigned int num)
{
    num = (num & (0x55555555)) + ((num >> 1) & (0x55555555));
    num = (num & (0x33333333)) + ((num >> 2) & (0x33333333));
    num = (num & (0x0f0f0f0f)) + ((num >> 4) & (0x0f0f0f0f));
    num = (num & (0x00ff00ff)) + ((num >> 8) & (0x00ff00ff));
    num = (num & (0x0000ffff)) + ((num >> 16) & (0x0000ffff));
    return num;
}

int FloatPrint(float num)
{
    union float_n_int
    {
        int int_num;
        float f_num;
    }x;

    x.f_num = num; 
    
    return x.int_num;
   
}
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1




