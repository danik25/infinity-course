/****************************************************************
*                         Binary Search Tree                     
* 						=====================
* File Name: BST_test.c
* Related files: BST.c, BST_test.c 
* #Version: V 2.2                    
* Writer: Dani Benjamin                         
* Reviewer: Lev Shubert                       
* Last update: 20/05/19            
****************************************************************/ 
#include <stdio.h> /* printf */
#include "BST.h"

#define UNUSED(x) (void)(x)

#define GREEN(str)      printf("\033[1;32m%s\033[0m\n", str)
#define RED(str)        printf("\033[1;31m%s\033[0m\n", str)
#define YELLOW(str)     printf("\033[1;33m%s\033[0m\n", str)
#define CYAN(str)       printf("\033[1;36m%s\033[0m\n", str)
#define PURPLE(str)     printf("\033[1;35m%s\033[0m\n", str)


/* compare function */
int CompareInt (const void *data1, const void *data2, void *param);

/* action function */
int PrintInt(void *data, void *param);

static void BSTCreatetest();
static void BSTInserttest();
static void BSTRemovetest();
static void BSTCounttest();
static void BSTFindtest();
static void BSTPrevNexttest();

static void BSTIntegrationtest();

/* assistance functions */
static int CompareTreeDataInt(BST_t *tree, int *exp);

int main()
{
    CYAN("\n\n\t\t~TEST FILE BST- binary search tree~");
    CYAN("\t\t\t Dani Benjamin\n\n");
    YELLOW("\n********Create********\n");
    BSTCreatetest();
    YELLOW("\n********insert********\n");
    BSTInserttest();
    YELLOW("\n********remove********\n");
    BSTRemovetest();
    YELLOW("\n********find********\n");
    BSTFindtest();
    YELLOW("\n********count********\n");
    BSTCounttest();
    YELLOW("\n********prev and next********\n");
    BSTPrevNexttest();
    YELLOW("\n********integration********\n");
    BSTIntegrationtest();

    CYAN("\n\n\t\t\t   ~THE END~\n\n");
    return(0);
}

static void BSTCreatetest()
{
    BST_t *tree = BSTCreate(CompareInt, NULL);
    (tree) ? GREEN("success") : RED("fail");
    BSTDestroy(tree);
}

static void BSTInserttest()
{
	BST_t *tree1 = BSTCreate(CompareInt, NULL);
	BST_t *tree2 = BSTCreate(CompareInt, NULL);
	BST_iter_t start = NULL;
	BST_iter_t end = NULL;

	int values1[] = {10, 8, 12, 7, 9, 15};
    int exp1[] = {7, 8, 9, 10, 12, 15};
	int values2[] = {1, 0, 33, 7, 15, 33};
    int exp2[] = {0, 1, 7, 15, 33};
	size_t i = 0;
	for(i = 0; i < sizeof(values1) / sizeof(int); ++i)
	{
		BSTInsert(tree1, &values1[i]);
	}
	start = BSTBegin(tree1);
	end = BSTEnd(tree1);
	BSTForEach(start, end, PrintInt, NULL);
    (!CompareTreeDataInt(tree1, exp1)) ? GREEN("success") : RED("fail");
	printf("\n");

	for(i = 0; i < sizeof(values2) / sizeof(int); ++i)
	{
		BSTInsert(tree2, &values2[i]);
	}
	start = BSTBegin(tree2);
	end = BSTEnd(tree2);
	BSTForEach(start, end, PrintInt, NULL);
    (!CompareTreeDataInt(tree2, exp2)) ? GREEN("success") : RED("fail");

	BSTDestroy(tree1);
	BSTDestroy(tree2);
}

static void BSTRemovetest()
{
    BST_t *tree = BSTCreate(CompareInt, NULL);
    BST_t *tree2 = BSTCreate(CompareInt, NULL);

    int values[] = {10, 8, 12, 7, 9, 15, 25, 19};
    int exp1[] = {8, 9, 10, 12, 15, 19, 25};
    int exp2[] = {8, 9, 10, 12, 15, 19};
    int exp3[] = {8, 9, 12, 15, 19};
    int exp4[] = {8, 9, 15, 19};

    int root_num = 10;

    BST_iter_t node = NULL;

    size_t i = 0;
    for(i = 0; i < sizeof(values)/sizeof(int); ++i)
    {
        BSTInsert(tree, &values[i]);
    }

    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    printf("\n");

    PURPLE("1. removing first element");
    printf("removing: %d\n", values[3]);
    node = BSTFind(tree, &values[3]);
    BSTRemove(node);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    (!CompareTreeDataInt(tree, exp1)) ? GREEN("success") : RED("fail");

    PURPLE("\n2. removing last element");
    printf("removing: %d\n", values[6]);
    node = BSTFind(tree, &values[6]);
    BSTRemove(node);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    (!CompareTreeDataInt(tree, exp2)) ? GREEN("success") : RED("fail");

    PURPLE("\n3. removing the root");
    printf("removing: %d\n", values[0]);
    node = BSTFind(tree, &values[0]);
    BSTRemove(node);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    (!CompareTreeDataInt(tree, exp3)) ? GREEN("success") : RED("fail");

    PURPLE("\n4. removing another one children node");
    printf("removing: %d\n", values[2]);
    node = BSTFind(tree, &values[2]);
    BSTRemove(node);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    (!CompareTreeDataInt(tree, exp4)) ? GREEN("success") : RED("fail");

    PURPLE("\n5. removing the root from a one node tree");
    node = BSTInsert(tree2, &root_num);
    BSTForEach(BSTBegin(tree2), BSTEnd(tree2), PrintInt, NULL);
    BSTRemove(node);
    (BSTIsEmpty(tree2)) ? GREEN("success") : RED("fail");

    BSTDestroy(tree);
    BSTDestroy(tree2);
}


static void BSTPrevNexttest()
{
    BST_t *tree = BSTCreate(CompareInt, NULL);
    int status = 0;
    BST_iter_t runner = NULL;

    int values[] = {10, 7, 3, 4, 1, 0};
    int exp[] = {0, 1, 3, 4, 7, 10};
    int i = 0;
    int size = sizeof(values)/sizeof(int);

    for(i = 0; i < size; ++i)
    {
        BSTInsert(tree, &values[i]);
    }
    runner = BSTFind(tree, &values[0]);
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);
    printf("\n");
    PURPLE("\n1. prev\n");
    for(i = size - 1; i >= 0; --i)
    {
        if(*(int*)BSTGetData(runner) != exp[i])
        {
            status = 1;
        }
        runner = BSTPrev(runner);
    }
    ((!status)) ? GREEN("success") : RED("fail");
    
    PURPLE("\n2. next\n");
    runner = BSTBegin(tree);
    for(i = 0; i < size; ++i)
    {
        if(*(int*)BSTGetData(runner) != exp[i])
        {
            status = 1;
        }
        runner = BSTNext(runner);
    }
    (!status) ? GREEN("success") : RED("fail");

    BSTDestroy(tree);    
}


static void BSTCounttest()
{
	BST_t *tree = BSTCreate(CompareInt, NULL);

	int values[] = {10, 8, 12, 7, 9, 15};
	size_t i = 0;
    PURPLE("\n1. empty tree");
    (BSTCount(tree) == 0) ? GREEN("success") : RED("fail");
	for(i = 0; i < sizeof(values)/sizeof(int); ++i)
	{
		BSTInsert(tree, &values[i]);
	}
	PURPLE("\n2. not empty tree");
	(BSTCount(tree) == sizeof(values) / sizeof(int)) ? GREEN("success") : 
                                                                RED("fail");
	BSTDestroy(tree); 
}

static void BSTFindtest()
{
    BST_t *tree = BSTCreate(CompareInt, NULL);

    int values[] = {10, 8, 12, 7, 9, 15};
    int num = 6;
    size_t i = 0;
    for(i = 0; i < sizeof(values)/sizeof(int); ++i)
    {
        BSTInsert(tree, &values[i]);
    }
    PURPLE("\n1. exsists");
    (*(int*)BSTGetData(BSTFind(tree, &values[2])) == values[2]) ? 
                                        GREEN("success") : RED("fail");
    PURPLE("\n2. not exsists");
    (BSTFind(tree, &num) == BSTEnd(tree)) ? GREEN("success") : RED("fail");

    BSTDestroy(tree);
}

static void BSTIntegrationtest()
{
    BST_t *tree = BSTCreate(CompareInt, NULL);
    BST_iter_t node = NULL;
    size_t count = 0;

    int values[] = {60, 40, 50, 65, 64, 75, 70, 45, 80, 66};
    int values2[] = {80, 0};
    int exp1[] = {40, 45, 50, 60, 64, 65, 66, 70, 75, 80};
    int exp2[] = {40, 45, 50, 60, 64, 65, 66, 70, 75};
    int exp3[] = {0, 40, 45, 50, 60, 64, 65, 66, 70, 75, 80};

    int i = 0;
    int size = sizeof(values) / sizeof(int);

    PURPLE("\n1. count on empty");
    count = BSTCount(tree);
    (!count) ? GREEN("success") : RED("fail");

    PURPLE("\n2. is empty");
    (BSTIsEmpty(tree)) ? GREEN("success") : RED("fail");

    PURPLE("\n3. is same iter");
    node = BSTInsert(tree, &values[0]);
    (BSTIsSameIter(node, BSTBegin(tree))) ? GREEN("success") : RED("fail");

    for(i = 1; i < size; ++i)
    {
        BSTInsert(tree, &values[i]);
    }
    PURPLE("\n4. first insertion");
    (!CompareTreeDataInt(tree, exp1)) ? GREEN("success") : RED("fail");

    PURPLE("\n5. remove the max node, with left child");
    node = BSTFind(tree, &values[8]);
    BSTRemove(node);
    (!CompareTreeDataInt(tree, exp2)) ? GREEN("success") : RED("fail");

    PURPLE("\n6. second insertion");
    BSTInsert(tree, &values2[0]);
    BSTInsert(tree, &values2[1]);
    (!CompareTreeDataInt(tree, exp3)) ? GREEN("success") : RED("fail");

    PURPLE("\n7. count");
    count = BSTCount(tree);
    (count = size + 1) ? GREEN("success") : RED("fail");

    PURPLE("\n8. forech- print");
    BSTForEach(BSTBegin(tree), BSTEnd(tree), PrintInt, NULL);

    BSTDestroy(tree);
}



/*===============static functions=======================*/

int CompareInt(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    return(*(int*)data1 - *(int*)data2);
}

int PrintInt(void *data, void *param)
{
	UNUSED(param);
	printf("%d\n", *(int*)data);
	return(0);
}

/*===============assistance static functions=======================*/
static int CompareTreeDataInt(BST_t *tree, int *exp)
{
    int status = 0;
    int i = 0;
    BST_iter_t runner = NULL;
    for(i = 0, runner = BSTBegin(tree); runner != BSTEnd(tree); 
                                    ++i, runner = BSTNext(runner))
    {
        if(*(int*)BSTGetData(runner) != exp[i])
        {
            status = 1;
        }
    }
    return(status);

}