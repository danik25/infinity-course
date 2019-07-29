/****************************************************************
*        dictionary shuffle and sort mt - Single Threaded       
* file: dict_shuff_sort_st.h
* Related files: dict_shuff_sort_st.c, dict_shuff_sort_st_test.c      
* #Version: V 1.0
* Writer: Dani Benjmain
* Reviewer: Oded Bryt
* Last update: 03/07/19
****************************************************************/
#include <stddef.h> /* size_t */

typedef int (*compare_t)(const void *data1, const void *data2);

typedef struct SORTING_STRUCT
{
    unsigned char *dictionary;
    unsigned char **word_pointer;
    size_t num_of_chars;
    size_t num_of_lines;
}dict_t;

int QuickSortMT(void *array, size_t arr_size, size_t element_size,
                                                    compare_t CompareFunc);

int QuickSort(void *array, size_t arr_size, size_t element_size,
                                                    compare_t CompareFunc);

