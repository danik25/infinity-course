#include <stdio`.h> /*printf */
#include <dlfcn.h> /*dl open, dlclose */

void myfunc();
void foo();
void Bar1();
void Bar2();

int main()
{
	void *dl_handle = NULL;
    void (*func)(void);

    myfunc();
    foo();
    Bar1();
    dl_handle = dlopen("libso2.so", RTLD_NOW);
    if (!dl_handle) 
    {
    	printf( "cant open with explicit request %s\n", dlerror() );
    	return (1);
    }
    func = dlsym(dl_handle, "Bar2");
    (*func)();
    dlclose( dl_handle);

    return (0);
}

void myfunc()
{
    printf("myfunc\n");
}