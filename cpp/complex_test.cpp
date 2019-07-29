/****************************************************************
*                              Complex
*                       =====================
* File Name: complex_test.cpp
* Related files: complex.hpp
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Idan Argaman    
* Last update: 23/07/19
****************************************************************/
#include <iostream>
#include "complex.hpp"
#include "dani_utilities.h"

void PlusTest();
void ComparisonTest();
void AssignmentTest();
void StreamTest();

using namespace hrd9;
int main()
{
    YELLOW("operators\n");
    PlusTest();
    YELLOW("\nstream test\n");
    StreamTest();
    YELLOW("\ncomparison test\n");
    ComparisonTest();
    YELLOW("\nmember function test\n");
    AssignmentTest();

    return(0);
}

void PlusTest()
{
    Complex obj1(4, 5);
    Complex obj2(6, 2);

    Complex ans = obj1 + obj2;
    std::cout << "entered-> obj1: "  << obj1.get_real() << ", " << 
        obj1.get_img() <<", obj2: " << obj2.get_real() << ", " << 
        obj2.get_img() << std::endl;


    std::cout << "after adding the two-> real and img: "<<ans.get_real()<<", "<< 
                                        ans.get_img() << std::endl;
}

void ComparisonTest()
{
    Complex obj1(6, 5);
    Complex obj2(6, 2);
    double fix = 2;

    obj1 != obj2 ? TEST(1) : TEST(0);
    
    obj1.set_img(fix);
    obj1 == obj2 ? TEST(1) : TEST(0);
}

void AssignmentTest()
{
    Complex obj1(6, 5);
    Complex obj2(3, 2);

    std::cout << "obj1 real and img: "<<obj1.get_real()<<", "<< 
                                        obj1.get_img() << std::endl;
    std::cout << "after addition of 3, 2:"<< std::endl;

    obj1 += obj2;

    std::cout << "obj1 real and img: "<<obj1.get_real()<<", "<< 
                                        obj1.get_img() << std::endl;
}

void StreamTest()
{
    Complex obj1(6, 5);
    Complex obj2;

    std::cout << "printing the object: " << obj1 << std::endl;
    std::cout << "pleas enter a real and imaginary inputs..." << std::endl;
    std::cin >> obj2;

    std::cout << "the entered values" << std::endl;
    std::cout << obj2 << std::endl;
}