#include <stdio.h> /*printf*/
#include <time.h>
#include "uid.h"

static void UIDTest();

#define GREEN(str) printf("\033[1;32m%s\033[0m\n", str)
#define RED(str) printf("\033[1;31m%s\033[0m\n", str)

int main()
{
    UIDTest();
    return (0);
}

static void UIDTest()
{
    UID_t id1 = UIDCreate();
    UID_t id2 = UIDCreate();
    /*UID_t g_bad_uid2 = UIDCreate();
    UID_t g_bad_uid = {0, {0}, 0};
    g_bad_uid2.counter += 1;*/
    printf("\nfirst:\n");
    printf("pid: %d\n", id1.pid);
    printf("sec: %ld, microsec: %ld\n", id1.time.tv_sec, id1.time.tv_usec);
    printf("counter: %ld\n", id1.counter);
    printf("\n");
    printf("second:\n");
    printf("pid: %d\n", id2.pid);
    printf("sec: %ld, microsec: %ld\n", id2.time.tv_sec, id2.time.tv_usec);
    printf("counter: %ld\n", id2.counter);

    printf("\nchecking if the two id's are the same:\n");
    (!UIDIsSame(id1, id2)) ?  GREEN("not the same\n") : RED("same\n");
/*
    printf("\nchecking for bad uid:\n");
    printf("pid: %d\n", g_bad_uid2.pid);
    printf("sec: %ld, microsec: %ld\n", g_bad_uid2.time.tv_sec, 
                                            g_bad_uid2.time.tv_usec);
    printf("counter: %ld\n", g_bad_uid2.counter);
    UIDIsBad(g_bad_uid2) ? GREEN("bad\n") : RED("good\n");*/
}