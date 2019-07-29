#include <iostream>

inline void foo();

int main()
{
    foo();
    return(0);
}

inline void foo()
{
    std::cout << "kkk\n";
}