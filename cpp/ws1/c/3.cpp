#include <iostream>
#include <stdio.h>

using namespace std;
int main()
{
    bool b1 = true;
    bool b2;
    int i = b1;
    i = 7;

    printf("%d\n", b2);

    b2 = i;

    cout << "uninitialized bool:\n" << i << "\n";
    return(0);
}