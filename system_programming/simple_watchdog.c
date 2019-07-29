#include <sys/types.h>
#include <unistd.h> /* fork(), execve() */
#include <sys/wait.h> /* waitpid */
#include <stdio.h> /* printf */
#include <stdlib.h> /* system */


#define UNUSED(x) (void)(x)

void CommandLineProc(char **name);
void SystemProc(char **name);

int main (int argc, char **argv)
{
    UNUSED(argc);
    CommandLineProc(argv);
    SystemProc(argv);
    return(0);
}

void CommandLineProc(char **name)
{
    int pid;
    int status, ret;

    pid = fork ();

    /* child */
    if (pid == 0) 
    {
        execvp(name[1], &name[1]);
    }

    /* parent */
    if ((ret = waitpid (pid, &status, 0)) == -1)
         printf ("parent:error\n");
}

void SystemProc(char **name)
{
    if(-1 == system(name[1]))
    {
        printf("error\n");
    }
}

