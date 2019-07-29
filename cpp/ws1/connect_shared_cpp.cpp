#include <iostream>
#include <stdio.h>
#include <dlfcn.h>

// cpp
void Foo();

int main()
{
    using std::cout;    
    using std::cerr;

    cout << "C++ dlopen demo\n\n";
    /*typedef void(*func_t)();

    void *handle = dlopen("./shared_cpp.so", RTLD_LAZY);
    func_t my_func = (func_t)dlsym(handle, "Foo");
    if(my_func == 0)
    {
        printf("error\n");
    }
    my_func();
    dlclose(handle);*/
    printf("dynamic linking\n");
    Foo();

    return(0);
}