/****************************************************************
*                   Knights Tour
* file: knight.c
* Related files: knight.h knight_test.c
* #Version: V 1.0
* Writer: Dani Benjamin
* Reviewer: Idan Argaman
* Last update: 15/06/19
***************************************************************/
#include <math.h> /* pow */
#include <stdio.h> /* printf */
#include <time.h> /* clock */
#include <assert.h> /* assert */

#include "knight.h"
#include "bit_array.h"
#include "dani_utilities.h"

#define EMPTY (~0)
#define FULL (0)
#define ROW_SIZE 8
#define COL_SIZE 8
#define BOARD_SIZE ((ROW_SIZE) * (COL_SIZE))

enum BOARD_STATE {FINISH, NOT_FINISH};

/* global luts */
int assistance_lut[ROW_SIZE][COL_SIZE] = {{0}};
unsigned long moves_lut[BOARD_SIZE] = {0};

/* recursive function */
static int RecMovment(int place, unsigned long board, 
                    unsigned long *print_array, int index);
static int RecMovment_Reguar(int place, unsigned long board, 
                        unsigned long *print_array, int index);

/* assistance functions */
static void CreateAssistanceLut(void);
static void CreateMovesLut(void);
static unsigned long CalculateMoves(int i, int j);

/* conversion functions */
static unsigned long ConvertFromInt(int num);
static int ConvertToInt(unsigned long num);

static int IsInPlace(int i , int j);
static unsigned long FirstBitOn(unsigned long num);


/* printing functions */
static void PrintBoard(unsigned long num, unsigned long hourse);

/* heuristic functions */
static int HeuristicPlaceToGo(int place, int last_place, unsigned long board);
static unsigned long LowestGradeMovment(unsigned long options);

void KnightTour(int num)
{
    clock_t start_r = 0;
    clock_t end_r = 0;
    clock_t start_h = 0;
    clock_t end_h = 0;
    int i = 0;

    unsigned long board = EMPTY;
    unsigned long print_array_r[BOARD_SIZE] = {0};
    unsigned long print_array_h[BOARD_SIZE] = {0};

    CreateAssistanceLut();
    CreateMovesLut();

    /* regular */
    printf("regular:\n\n");
    start_r = clock();
    RecMovment_Reguar(num, board, print_array_r, -1);

    printf("%d:\n", i);
    PrintBoard(print_array_r[i], ConvertFromInt(num));
    printf("\n");

    for(i = 1; i < BOARD_SIZE; ++i)
    {
        printf("%d:\n", i);
        PrintBoard(print_array_r[i], print_array_r[i] ^ print_array_r[i-1]);
        printf("\n");
    }

    end_r = clock();

    /* heuristic */
    printf("heuristic:\n\n");
    start_h = clock();
    board = EMPTY;
    i = 0;

    RecMovment(num, board, print_array_h, -1);

    printf("\n");

    printf("%d:\n", i);
    PrintBoard(print_array_h[i], ConvertFromInt(num));
    printf("\n");

    for(i = 1; i < BOARD_SIZE; ++i)
    {
        printf("%d:\n", i);
        PrintBoard(print_array_h[i], print_array_h[i] ^ print_array_h[i-1]);
        printf("\n");
    }

    end_h = clock();


    printf("rum time regular: %f\n", 
                    ((double)(end_r - start_r)/CLOCKS_PER_SEC) / 60);
    printf("rum time heuristic: %f\n", 
                    ((double)(end_h - start_h)/CLOCKS_PER_SEC) / 60);


}

static int RecMovment(int place, unsigned long board, 
                        unsigned long *print_array, int index)
{
    unsigned long answer = 0;
    int next_place = 0;

    assert(print_array);

    printf("\n");

    /* setting of the place the hourse at */
    board = SetOff(board, place);

    /* updating the printing array */
    print_array[index] = board + ConvertFromInt(place);

    /* no place to go, and the board is full */
    if(CountOff(board) == BOARD_SIZE)
    {
        return(SUCCESS);
    }

    next_place = HeuristicPlaceToGo(place, 0, board);

    /* no place to go, but the board is not full */
    if(-1 == next_place || -1 == place)
    {
        return(FAIL);
    } 

    answer = RecMovment(next_place, board, print_array, index + 1);

    if(FAIL == answer)
    {
        next_place = HeuristicPlaceToGo(place, next_place, board);
    }

    if(SUCCESS == answer)
    {
        return(SUCCESS);
    }

    return(RecMovment(next_place, board, print_array, index + 1));
}

static int HeuristicPlaceToGo(int place, int last_place, unsigned long board)
{
    unsigned long copy_lut = moves_lut[place];
    unsigned long possible_moves = 0;
    int ans_place = 0;

    possible_moves = copy_lut & board;

    if(0 == possible_moves)
    {
        return(-1);
    }

    /* finding the lowest grade place that hasn't been visited yet */
    if(last_place != 0)
    {
    	while(LowestGradeMovment(possible_moves) != ConvertFromInt(last_place))
    	{	
    		possible_moves -= LowestGradeMovment(possible_moves);
    	}

    	possible_moves -= LowestGradeMovment(possible_moves);
    }

    if(0 == possible_moves)
    {
        return(-1);
    }

    ans_place = ConvertToInt(LowestGradeMovment(possible_moves));

    return(ans_place);
}

static unsigned long LowestGradeMovment(unsigned long options)
{
    unsigned long min = 0;
    size_t num_of_bits_on = 8;
    int possible_movement = 0;

    while(0 != options)
    {
    	possible_movement = ConvertToInt(FirstBitOn(options));
        if(CountOn(moves_lut[possible_movement]) <= num_of_bits_on)
        {
        	num_of_bits_on = CountOn(moves_lut[possible_movement]);
            min = FirstBitOn(options);
        }

        options -= FirstBitOn(options);
    }

    return(min);
}

static void CreateAssistanceLut()
{
    int i = 0, j = 0;
    int num = 0;

    for(i = 0; i < ROW_SIZE; ++i)
    {
        for(j = 0; j < COL_SIZE; ++j)
        {
            assistance_lut[i][j] = num;
            ++num;
        }
    }
}

static void CreateMovesLut()
{
    int i = 0, j = 0, k = 0;
    for(i = 0; i < ROW_SIZE; ++i)
    {
        for(j = 0; j < COL_SIZE; ++j, ++k)
        {
            moves_lut[k] = CalculateMoves(i, j);
        }
    }
}

static unsigned long CalculateMoves(int i, int j)
{
    unsigned long sum = 0;
    sum += ConvertFromInt(IsInPlace(i - 2, j + 1));
    sum += ConvertFromInt(IsInPlace(i - 1, j + 2));
    sum += ConvertFromInt(IsInPlace(i + 1, j + 2));
    sum += ConvertFromInt(IsInPlace(i + 2, j + 1));
    sum += ConvertFromInt(IsInPlace(i + 2, j - 1));
    sum += ConvertFromInt(IsInPlace(i + 1, j - 2));
    sum += ConvertFromInt(IsInPlace(i - 1, j - 2));
    sum += ConvertFromInt(IsInPlace(i - 2, j - 1));

    return(sum);
}

static unsigned long ConvertFromInt(int num)
{
    if(-1 == num)
    {
        return(0);
    }
    return(pow(2, num));
}

static int ConvertToInt(unsigned long num)
{
    return(log(num) / log(2));
}

static int IsInPlace(int i , int j)
{
    if((i >= 0 && i < COL_SIZE) && (j >= 0 && j < ROW_SIZE))
    {
        return(assistance_lut[i][j]);
    }
    return(-1);
}

static unsigned long FirstBitOn(unsigned long num)
{
    return(num - (num & (num - 1)));
}

static void PrintBoard(unsigned long num, unsigned long hourse)
{
    unsigned long i = 1;
    
    int cnt = 0;
    
    /*representation of the board*/
    for (i = 1; cnt < 64; i <<= 1, ++cnt) 
    {
        if (cnt % 8 == 0 && cnt != 0)
        {
            printf("\n");
        }

        if(i & hourse)
        {
        	YELLOW(" H ");
        }
        
        else
        {
        	(num & i) ? GREEN(" - ") : RED(" X ");
        }
    }
    printf("\n");  
}

/* the functions befor the change for heuristic approach */


static int PlaceToGo(int place, unsigned long board);
static int NextPlace(int place, int past_place_to_go, unsigned long board);


static int RecMovment_Reguar(int place, unsigned long board, 
                        unsigned long *print_array, int index)
{
    unsigned long answer = 0;
    int next_place = 0;

    /* setting of the place the hourse at */
    board = SetOff(board, place);

    print_array[index] = board + ConvertFromInt(place);

    if(CountOff(board) == BOARD_SIZE)
    {
        return(SUCCESS);
    }


    if(-1 == PlaceToGo(place, board) || -1 == place)
    {
        return(FAIL);
    } 

    next_place = PlaceToGo(place, board);
    answer = RecMovment(next_place, board, print_array, index + 1);

    if(FAIL == answer)
    {
        next_place = NextPlace(place, next_place, board);
    }
    if(SUCCESS == answer)
    {
        return(SUCCESS);
    }

    return(RecMovment(next_place, board, print_array, index + 1));
}

static int PlaceToGo(int place, unsigned long board)
{
    unsigned long moves = moves_lut[place];
    unsigned long possible_moves = moves & board;
    unsigned long move = 0;
    int ans_place = 0;

    if(0 == possible_moves)
    {
        return(-1);
    }
    move = FirstBitOn(possible_moves);

    ans_place = ConvertToInt(move);
    return(ans_place);
}

static int NextPlace(int place, int past_place_to_go, unsigned long board)
{
    unsigned long new_lut = moves_lut[place];
    unsigned long possible_moves = 0;
    int ans_place = 0;

    while(FirstBitOn(new_lut) != ConvertFromInt(past_place_to_go))
    {
        new_lut -= FirstBitOn(new_lut);
    }
    new_lut -= FirstBitOn(new_lut);

    possible_moves = new_lut & board;

    if(0 == possible_moves)
    {
        return(-1);
    }
    ans_place = ConvertToInt(FirstBitOn(possible_moves));
    return(ans_place);
}

