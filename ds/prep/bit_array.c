#include "bit_array_v2.h"
#include "prep_lut.h"

#define BITE_IN_WORD 64 
#define UNUSED(n) (void)(n)

unsigned long AllOn(unsigned long barr)
{
    UNUSED(barr);
    return 0xFFFFFFFFFFFFFFFF;
}

unsigned long AllOff(unsigned long barr)
{
    UNUSED(barr);
    return 0;
}

unsigned long SetOn(unsigned long barr, size_t index)
{
    return barr | 1UL<<index;
}

unsigned long SetOff(unsigned long barr, size_t index)
{
    return barr & (~(1UL<<index));
}

unsigned long SetBit(unsigned long barr, size_t index, char value)
{
    return (value > 0) ? barr | (1UL << index) : barr & (~(1UL << index));
}

bool_t IsOn(unsigned long barr, size_t index)
{
    return (barr & (1UL << index)) ?  TRUE : FALSE;
}

bool_t IsOff(unsigned long barr, size_t index)
{
    return (barr & (1UL << index)) ?  FALSE : TRUE;
}

unsigned long FlipBit(unsigned long barr, size_t index)
{
    return (barr & 1UL << index) ? SetOff(barr, index) : SetOn(barr, index);
}

unsigned long RotateLeft(unsigned long barr, size_t offset)
{
    unsigned long int tmp = (~0);
    tmp <<= BITE_IN_WORD - offset;
    tmp &= barr;
    tmp >>= BITE_IN_WORD - offset;
    return (barr<<offset) | tmp;
}

unsigned long RotateRight(unsigned long barr, size_t offset)
{
    unsigned long int tmp = (~0);
    tmp >>= BITE_IN_WORD - offset;
    tmp &= barr;
    tmp <<= BITE_IN_WORD - offset;
    return barr>>(offset) | tmp;
}

unsigned long Mirror(unsigned long barr)
{
    /*swapping two halfes*/
    barr = barr >> 32 | barr << 32; 
    /*swapping sixteenth*/
    barr = (barr & 0xFFFF0000FFFF0000) >> 16 | 
                                ((barr << 16) & 0xFFFF0000FFFF0000);
    /*swapping eighth*/ 
    barr = (barr & 0xFF00FF00FF00FF00) >> 8 | 
                                ((barr << 8) & 0xFF00FF00FF00FF00);
    /*swapping fourth*/ 
    barr = (barr & 0xF0F0F0F0F0F0F0F0) >> 4 | 
                                ((barr << 4) & 0xF0F0F0F0F0F0F0F0);
    /*swapping twos*/ 
    barr = (barr & 0xCCCCCCCCCCCCCCCC) >> 2 | 
                                ((barr << 2) & 0xCCCCCCCCCCCCCCCC);
    /*swapping individuals*/ 
    barr = (barr & 0xAAAAAAAAAAAAAAAA) >> 1|
                                ((barr << 1) & 0xAAAAAAAAAAAAAAAA); 
    return barr;
}

size_t CountOn(unsigned long barr)
{
    barr = (barr & (0x5555555555555555)) + ((barr >> 1) & (0x5555555555555555));
    barr = (barr & (0x3333333333333333)) + ((barr >> 2) & (0x3333333333333333));
    barr = (barr & (0x0F0F0F0F0F0F0F0F)) + ((barr >> 4) & (0x0F0F0F0F0F0F0F0F));
    barr = (barr & (0x00FF00FF00FF00FF)) + ((barr >> 8) & (0x00FF00FF00FF00FF));
    barr = (barr & (0x0000FFFF0000FFFF)) + ((barr >> 16) & (0x0000FFFF0000FFFF));
    barr = (barr & (0x00000000FFFFFFFF)) + ((barr >> 32) & (0x00000000FFFFFFFF));
    return barr;
}

size_t CountOff(unsigned long barr)
{
    barr = (~barr);
    barr = (barr & (0x5555555555555555)) + ((barr >> 1) & (0x5555555555555555));
    barr = (barr & (0x3333333333333333)) + ((barr >> 2) & (0x3333333333333333));
    barr = (barr & (0x0F0F0F0F0F0F0F0F)) + ((barr >> 4) & (0x0F0F0F0F0F0F0F0F));
    barr = (barr & (0x00FF00FF00FF00FF)) + ((barr >> 8) & (0x00FF00FF00FF00FF));
    barr = (barr & (0x0000FFFF0000FFFF)) + ((barr >> 16) & (0x0000FFFF0000FFFF));
    barr = (barr & (0x00000000FFFFFFFF)) + ((barr >> 32) & (0x00000000FFFFFFFF));
    return barr;
}

size_t CountBitsLUT(unsigned long barr)
{
    size_t cnt = 0;
    int i = 0;
    
    for (i = 0; i < 8; ++i)
    {
        cnt += count_arr[(unsigned char)barr];
        barr >>= 8;
    }
    
    return cnt;
}

unsigned long MirrorBitsLUT(unsigned long barr)
{
    unsigned long mask = 0;
    int i = 0;
    
    for (i = 0; i < 7; ++i)
    {
        mask |= mirror_arr[(unsigned char)barr];
        barr >>= 8;
        mask <<= 8;
    }
    mask |= mirror_arr[(unsigned char)barr];
    return mask;
}





