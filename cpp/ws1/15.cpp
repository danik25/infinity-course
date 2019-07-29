#include <iostream>
#include "15.hpp"

int main()
{
    int arr[12];

    std::cout<<Max<int>(3,5)<<"\n"<<Max<double>(3.7, 12.9)<<"\n";
    std::cout<<Max<int*>(arr, arr+8)<<std::endl;
    std::cout<<Max('a','b')<<std::endl<<"\n";

    return(0);
}