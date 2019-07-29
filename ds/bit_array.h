/****************************************************************
*                           Bit Array                           *
* Related files: bit_array.h , bit_array.c , bit_array_test.c   *
* writer: Dani Benjamin                                         *
* reviewer: Tom Valershtein                                     *
* last update: 27.3.19                                          *
****************************************************************/


#ifndef _BIT_ARRAY_V2_H_
#define _BIT_ARRAY_V2_H_

#include <stdio.h> /* size_t */


typedef enum BOOL {FALSE, TRUE} bool_t;

/* turn on/ off all bits in <barr> */
unsigned long AllOn(unsigned long barr);
unsigned long AllOff(unsigned long barr);

/* set on/off bit <#index> in <barr> */
unsigned long SetOn(unsigned long barr, size_t index);
unsigned long SetOff(unsigned long barr, size_t index);

/* set bit <#index> to status <stat> */
unsigned long SetBit(unsigned long barr, size_t index, char value);

/* return TRUE / FALSE according to bit <#index> status */
bool_t IsOn(unsigned long barr, size_t index);
bool_t IsOff(unsigned long barr, size_t index);

/* switch status of bit <#index> */
unsigned long FlipBit(unsigned long barr, size_t index);

/* rotate <barr> left/right, n times */ 
unsigned long RotateLeft(unsigned long barr, size_t offset);
unsigned long RotateRight(unsigned long barr, size_t offset);

/* mirror <barr> */
unsigned long Mirror(unsigned long barr);

/* return number of bit on/off in <barr> */
size_t CountOn(unsigned long barr);
size_t CountOff(unsigned long barr);

/* mirror <barr> using LUT */
unsigned long MirrorBitsLUT(unsigned long barr);

/* return number of bits on in <barr> using LUT */
size_t CountBitsLUT(unsigned long barr);

#endif


