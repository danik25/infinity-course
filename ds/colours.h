#define GREEN(str)      printf("\033[1;32m%s\033[0m", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)
#define U_GREEN(str)      printf("\033[0;32m%s\033[0m\n", str)
#define U_RED(str)        printf("\033[0;31m%s\033[0m\n", str)
#define YELLOW(str)     printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str)       printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str)     printf("\033[1;35m%s\033[0m\n", str)

#define TEST(x) x ? GREEN("success") : RED("fail")
#define UNUSED(x) (void)(x)