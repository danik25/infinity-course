/****************************************************************
*                   Scheduler                                   *
* Related files: scheduler.c, scheduler_test.c scheduler.h      *
*                task.c, task.h uid.h, uid.c                    *
* #Version: V 1.3                                               *
* Writer: Dani Benjamin                                         *
* Reviewer: Moshe Greenberg                                     *
* Last update: 21/04/19                                         *
****************************************************************/

#include <stdio.h> /*printf*/
#include "scheduler.h"
#include "task.h" 

#define UNUSED(x) (void)(x)
#define GREEN(str) printf("\033[1;32m%s\033[0m\n", str)
#define RED(str) printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str) printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str) printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str) printf("\033[1;35m%s\033[0m\n", str)

int cnt_beep = 0;
int cnt_print = 0;

static void CreateTest();
static void AddTest();
static void RunTest();
static void RemoveTest();
static void SizeTest();
static void IsEmptyTest();


/*tasks*/
int PrintSec(void *param);
int PrintTime(void *param);
int PrintSecNum(void *param);
int BeepFunc(void *param);
int Stop(void *param);

int main()
{
    CYAN("\n\n\t\t\t~TEST FILE SCHEDUALER~");
    CYAN("\t\t\t    Dani Benjamin\n\n");
    YELLOW("\n********creation test********\n");
    CreateTest();
    YELLOW("\n********add test********\n");
    AddTest();
    YELLOW("\n********run test********\n");
    RunTest();
    YELLOW("\n********remove test********\n");
    RemoveTest();
    YELLOW("\n********size test********\n");
    SizeTest();
    YELLOW("\n********is empty test********\n");
    IsEmptyTest();
    CYAN("\n\n\t\t\t~THE END~\n\n");
    return (0);
}

static void CreateTest()
{
    sched_t *new_sched = SCHCreate();
    (new_sched) ? GREEN("success") : RED("fail");
    SCHDestroy(new_sched);
}

static void AddTest()
{
    sched_t *new_sched = SCHCreate();
    int intervals[] = {5, 7};
    int stop_num = 12;
    int exp[] = {2, 1};
    
    SCHAdd(new_sched, PrintTime, &intervals[0], intervals[0]);
    SCHAdd(new_sched, BeepFunc, &intervals[1], intervals[1]);
    SCHAdd(new_sched, Stop, new_sched, stop_num);

    SCHRun(new_sched);

    (exp[0] == cnt_print && exp[1] == cnt_beep) ? GREEN("success") : RED("fail");

    SCHDestroy(new_sched);
    
}

static void RunTest()
{
    sched_t *new_sched = SCHCreate();
    int intervals[] = {1, 7, 5, 3};
    int stop_num = 5;
    size_t i = 0;
    for(i = 0; i < sizeof(intervals)/sizeof(int); ++i)
    {
        SCHAdd(new_sched, PrintSecNum, &intervals[i], intervals[i]);
    }
 
    SCHAdd(new_sched, Stop, new_sched, stop_num);
    SCHRun(new_sched);
    printf("\n");
    SCHDestroy(new_sched);
}

static void RemoveTest()
{
    sched_t *new_sched = SCHCreate();
    int intervals[] = {1, 4, 3};
    UID_t intervals_id[] = {{0}, {0}, {0}};
    int stop_num = 10;
    size_t i = 0;
    for(i = 0; i < sizeof(intervals)/sizeof(int); ++i)
    {
        intervals_id[i] = SCHAdd(new_sched, PrintSecNum, 
                        &intervals[i], intervals[i]);
    }
    SCHAdd(new_sched, Stop, new_sched, stop_num);
    SCHRun(new_sched);
    printf("\nremoving 4:\n");
    SCHRemove(new_sched, intervals_id[1]);
    SCHRun(new_sched);
    printf("\n");
    SCHDestroy(new_sched);
}

static void SizeTest()
{
    sched_t *new_sched = SCHCreate();
    int intervals[] = {1, 4, 3};
    UID_t intervals_id[] = {{0}, {0}, {0}, {0}};
    int stop_num = 7;
    int status = 0;
    size_t i = 0;
    for(i = 0; i < sizeof(intervals)/sizeof(int); ++i)
    {
        intervals_id[i] = SCHAdd(new_sched, PrintSecNum, 
                        &intervals[i], intervals[i]);
        if(SCHSize(new_sched) != i + 1)
        {
            printf("here\n");
            status = 1;
        }
    }
    intervals_id[i] = SCHAdd(new_sched, Stop, new_sched, stop_num);
    printf("removing\n");
    for(i = 0; i < 4; ++i)
    {
        SCHRemove(new_sched, intervals_id[i]);
        if(SCHSize(new_sched) != sizeof(intervals)/sizeof(int) - i)
        {
            status = 1;
        }
    }
    (!status) ? GREEN("success") : RED("fail");
    printf("\n");
    SCHDestroy(new_sched);
}

static void IsEmptyTest()
{
    sched_t *new_sched = SCHCreate();
    int num = 3;
    PURPLE("1. checking empty queue:");
    (SCHIsEmpty(new_sched)) ? GREEN("success") : RED("fail");
    SCHAdd(new_sched, PrintTime, &num, num);
    PURPLE("\n2. checking not empty queue:");
    (!SCHIsEmpty(new_sched)) ? GREEN("success") : RED("fail");
    printf("\n");
    SCHDestroy(new_sched);
}

/*tasks*/
int PrintSecNum(void *param)
{
    time_t curtime = time(NULL); 
    printf("every %d sec: %s\n", *(int*)param, ctime(&curtime));
    return (0);
}
int BeepFunc(void *param)
{
    time_t curtime = time(NULL);
    printf("every %d sec: %s: ", *(int*)param, ctime(&curtime));
    fprintf(stdout, "\abeep\n\n" );
    ++cnt_beep;
    return (0);
}

int PrintSec(void *param)
{
    time_t curtime = time(NULL); 

    UNUSED(param);
    printf("every %d: %s\n", *(int*)param, ctime(&curtime));
    return (0);
}

int PrintTime(void *param)
{
    time_t curtime = time(NULL);
    printf("every %d: %s\n", *(int*)param, ctime(&curtime));
    ++cnt_print;
    return (0);
}

int Stop(void *param)
{
    SCHStop(param);
    return (0);
}