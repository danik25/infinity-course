#include <stdio.h>
#include <dlfcn.h>
int main()
{
    

    void *handle = dlopen("shared.so", RTLD_LAZY);
    void(*func)(void) = dlsym(handle, "_Z3Foov");
    if(func == NULL)
    {
        printf("error\n");
    }
    func();
    dlclose(handle);

    return(0);
}