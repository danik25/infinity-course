#include <stdio.h>

void Foo(const double& i);
void Bar(double& i);

int main()
{
	int i = 5;
	Foo(i);
	Bar(reinterpret_cast<double&>(i));
	return(0);
}

void Foo(const double& i)
{
	printf("const\n");
	printf("address: %p, value: %f\n\n", &i, i);
}

void Bar(double& i)
{
	printf("non const\n");
	printf("address: %p, value: %f\n", &i, i);
}