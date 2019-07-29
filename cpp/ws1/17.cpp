#include <iostream>
#include <stdio.h>

int main()
{
	int i = 8;
	int& ip = i;
	ip = 9;
	std::cout << i<< std::endl;
	printf("%p\n", &ip);
	printf("%p\n", &i);
}