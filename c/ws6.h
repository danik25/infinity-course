#ifndef _WS6_H_
#define _WS6_H_

<<<<<<< HEAD
/*assisting function for printing the binary representation*/
void PrintBit(unsigned int num);
=======

/* Dani Benjamin.
    reviewer: Yuval Shapira.
    modification date: 18.3.19 */

>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1

/*1: returns x*2^y*/
unsigned int Pow2(unsigned int x, int y);

/*2.1: returns 1 if the number is a power of 2, and 0 otherwise. with a loop*/
unsigned int PowerLoop(unsigned num);
/*2.2: returns 1 if the number is a power of 2, and 0 otherwise. without a loop*/
unsigned int PowerNoLoop(unsigned int num);

/*3: adds 1 to the number*/
unsigned int Add(unsigned int num);

/*4: prints the numbers with 3 bits*/
void ThreeBits(unsigned int *arr, int size);

<<<<<<< HEAD
/*5: prints the reveresed number*/
void Mirror(unsigned int num);

/*6.1: returns if the bits 2 and 6 are on*/
int TwoAndSix(unsigned int num);
/*6.2: returns if the bits 2 or 6 are on*/
int TwoOrSix(unsigned int num);
/*6.3: returns the number resulting from sweeping the bits at index 3 and 5*/
int SwapThreeAndFive(unsigned int num);

/*6: returns the closest number that is divided by 16*/
unsigned DividedSixteen(unsigned int num);
=======
/*5.1: prints the reveresed number with a loop*/
unsigned int Mirror(unsigned int num);
/*5.2: prints the reveresed number without a loop*/
unsigned int MirrorNoLoop(unsigned int num);

/*6.1: returns if the bits 2 and 6 are on*/
int TwoAndSix(unsigned char ch);
/*6.2: returns if the bits 2 or 6 are on*/
int TwoOrSix(unsigned char ch);
/*6.3: returns the number resulting from sweeping the bits at index 3 and 5*/
int SwapThreeAndFive(unsigned char num);

/*6: returns the closest number that is divided by 16*/
unsigned int DividedSixteen(unsigned int num);

/*7: swaps the numbers*/
void Swap(unsigned int *num1, unsigned int *num2);

/*8: counts the set bits with a loop*/
int CountSet(unsigned int num);
/*8: counts the set bits no loop*/
int CountSetNoLoop(unsigned int num);


/*9: float analysis*/
int FloatPrint(float num);

unsigned int Function3(unsigned char ch);
>>>>>>> dd661b761cb71aac5f390156315eb889ad3bdfc1

#endif
