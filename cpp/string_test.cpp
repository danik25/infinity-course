/****************************************************************
*                              String
* 						=====================
* File Name: string_test.cpp
* Related files: string.hpp string.cpp
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Ayala Rosel    
* Last update: 23/07/19
****************************************************************/
#include <iostream>
#include <cstring> /* strcmp */
#include "string.hpp"
#include "dani_utilities.h"

void test_constructors();
void test_member_operators();
void test_comparison_operators();
void test_iostream();

using namespace hrd9;

int main()
{
	YELLOW("constructors\n");
	test_constructors();
	YELLOW("\nmember functions, '+=' and length\n");
	test_member_operators();
	YELLOW("\ncomparison operators\n");
	test_comparison_operators();
	YELLOW("\niostream\n");
	test_iostream();

	return(0);
}

void test_constructors()
{
	/* constructor */
	String str1("dani");

	/* copy constructor */
	String str2 = str1;

	/* copy assingment operator */
	String str3;
	str3 = str1;
}

void test_member_operators()
{
	String str1("dani");
	String str2("benjamin");
	String str3("danibenjamin");

	str1 += str2;
	PURPLE("1. +=\n");
	(str1 == str3) ? TEST(1) : TEST(0);

	PURPLE("2. length\n");
	TEST(str2.length() == 8);

	PURPLE("3. read by index - []\n");
	TEST(str2[2] == 'n');

	PURPLE("4. changing with []\n");
	str3[0] = 'b';
	(str3 == "banibenjamin") ? TEST(1) : TEST(0);

	PURPLE("5. get the string\n");
	TEST(!strcmp("benjamin", str2.to_c_str()));

}

void test_comparison_operators()
{
	String str1("abc");
	String str2("abc");
	String str3("def");
	String str4;

	PURPLE("1. ==\n");
	(str1 == str2) ? TEST(1) : TEST(0);

	PURPLE("2. !=\n");
	(str1 != str3) ? TEST(1) : TEST(0);

	PURPLE("3. >\n");
	(str3 > str2) ? TEST(1) : TEST(0);

	PURPLE("4. <\n");
	(str1 < str3) ? TEST(1) : TEST(0);

	PURPLE("5. +\n");
	str4 = str1 + str3;
	(str4 == "abcdef") ? TEST(1) : TEST(0);
}

void test_iostream()
{
	String str1("abc");

	std::cout << str1 << std::endl;
}
