#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H
/*================================
TEST UTILITIES
--------------

this headers contains commonly used enums and macro's in my test files,
mostly numbers and generic enums.

*/

#define RED(x)     printf("\033[1;31m"), (x), printf("\033[0m")
#define GREEN(x)   printf("\033[1;32m"), (x), printf("\033[0m")
#define BLUE(x)    printf("\033[1;34m"); (x); printf("\033[0m")
#define YELLOW(x)  printf("\033[1;33m"); (x); printf("\033[0m")
#define MAGENTA(x) printf("\033[1;35m"); (x); printf("\033[0m")
#define CYAN(x)    printf("\033[1;36m"); (x); printf("\033[0m")
#define TEST_HEADLINE(func) printf("\n============================Test "#func""\
                            "===========================================\n\n" \
                                                       "Test for "#func" - \n");
#define UNUSED (void)

enum BOOLEAN {FALSE = 0, TRUE};
enum STATUS {SUCCESS = 0, FAIL};
                                                         

#endif /* TEST_UTILITIES_H */
