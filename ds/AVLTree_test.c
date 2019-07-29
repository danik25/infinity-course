/****************************************************************
*                       AVL Binary Search Tree
*                       =====================
* File Name: AVLTree.h
* Related files: AVLTree.c, AVLTree_test.c
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Moshe Greenberg    
* Last update: 02/06/19
****************************************************************/
#include <stdio.h> /* printf */

#include "AVLTree.h"
#include "colours.h"

#define UNUSED(x) (void)(x)

/* compare function */
static int CompareInt (const void *data1, const void *data2, void *param);

/* action function */
static int PrintInt(void *data, void *param);

/* test functions */
static void AVLCreatetest();
static void AVLInserttest();
static void AVLRemovetest();
static void AVLFindtest();
static void AVLCounttest();
static void AVLIsEmptytest();
static void AVLHeigttest();


int main()
{
    CYAN("\n\n\t  ~TEST FILE AVL- balanced binary search tree~");
    CYAN("\t\t\t Dani Benjamin\n\n");
    YELLOW("\n********Create********\n");
    AVLCreatetest();
    YELLOW("\n********Insert********\n");
    AVLInserttest();
    YELLOW("\n********Remove********\n");
    AVLRemovetest();
    YELLOW("\n********Find********\n");
    AVLFindtest();
    YELLOW("\n********Count********\n");
    AVLCounttest();
    YELLOW("\n********IsEmpty********\n");
    AVLIsEmptytest();
    YELLOW("\n********Height********\n");
    AVLHeigttest();

    CYAN("\t\t\t THE END\n\n");
    return(0);
}

/*===============test functions=======================*/

static void AVLCreatetest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    TEST(tree);
    AVLDestroy(tree);
}

static void AVLInserttest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    int values[] = {30, 0, 10, 7, 9, 50, 8, 1, 6, 12, 15, 14, 13, 35};
    size_t i = 0;

    for(i = 0; i < sizeof(values) / sizeof(int); ++i)
    {
        AVLInsert(tree, &values[i]);
    }

    AVLForEach(tree, PrintInt, NULL);

    printf("\n");

    AVLDestroy(tree);
}

static void AVLRemovetest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    int values[] = {30, 20, 10, 25, 21, 23, 40, 35, 45, 41};
    size_t i = 0;
    int leaf = 35;
    int root = 30;
    int two_children = 20;
    int one_children = 25;
    int not_exists = 1;

    for(i = 0; i < sizeof(values) / sizeof(int); ++i)
    {
        AVLInsert(tree, &values[i]);
    }

    printf("original list:\n");
    AVLForEach(tree, PrintInt, NULL);

    PURPLE("\n\n1. removing a leaf");
    printf("\nremoved: %d\n",leaf);
    AVLRemove(tree, &leaf);
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");

    PURPLE("2. removing the root");
    printf("\nremoved: %d \n",root);
    AVLRemove(tree, &root);
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");

    PURPLE("3. removing a node with two children");
    printf("\nremoved: %d \n",two_children);
    AVLRemove(tree, &two_children);
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");

    PURPLE("4. removing a node with one child");
    printf("\nremoved: %d \n",one_children);
    AVLRemove(tree, &one_children);
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");

    PURPLE("5. trying to remove data that doesnt exsists");
    printf("\nto remove: %d \n",not_exists);
    AVLRemove(tree, &not_exists);
    AVLForEach(tree, PrintInt, NULL);
    printf("\n");

    AVLDestroy(tree);
    
}

static void AVLFindtest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);

    int values[] = {10, 8, 12, 7, 9, 15};
    int num = 6;
    size_t i = 0;

    PURPLE("\n1. empty tree");
    TEST(NULL == AVLFind(tree, &num));

    for(i = 0; i < sizeof(values)/sizeof(int); ++i)
    {
        AVLInsert(tree, &values[i]);
    }

    PURPLE("\n2. exsists");
    TEST((*(int*)AVLFind(tree, &values[2])) == values[2]);  
                                        
    PURPLE("\n3. not exsists");
    TEST(NULL == AVLFind(tree, &num));

    AVLDestroy(tree);
}

static void AVLCounttest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    int values[] = {1, 2, 6, 4, 7, 12};
    size_t i = 0;

    PURPLE("1. empty tree");
    TEST(!AVLCount(tree));

    AVLInsert(tree, &values[i]);

    PURPLE("\n2. one node tree");
    TEST(AVLCount(tree) == 1);

    for(i = 1; i < sizeof(values) / sizeof(int); ++i)
    {
        AVLInsert(tree, &values[i]);
    }

     PURPLE("\n3. full tree");
     TEST(AVLCount(tree) == sizeof(values) / sizeof(int));

     AVLDestroy(tree);
}

static void AVLIsEmptytest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    int num = 1;

    PURPLE("1. empty tree");
    TEST(AVLIsEmpty(tree));

    AVLInsert(tree, &num);

    PURPLE("\n2. not empty");
    TEST(!AVLIsEmpty(tree));

    AVLDestroy(tree);
}

static void AVLHeigttest()
{
    AVL_t *tree = AVLCreate(CompareInt, NULL);
    int input[] = {25, 30, 34, 20, 29, 27, 28, 18, 24, 37, 36, 35};
    int to_remove[] = {35, 29, 37, 18, 34, 28, 30, 20, 27, 25, 36, 24};
    size_t exp_insert[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4};
    size_t exp_remove[] = {4, 4, 4, 4, 4, 3, 3, 3, 2, 2, 1, 0};
    size_t i = 0;
    int status = 0;

    PURPLE("1. inserts\n");
    printf("empty tree, height:  %ld\n", AVLHeight(tree));
    for(i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        AVLInsert(tree, &input[i]);
        printf("%d inserted, height: %ld, exp: %ld \n", input[i], AVLHeight(tree), exp_insert[i]);
        if(AVLHeight(tree) != exp_insert[i])
        {
            status = 1;
        }
    }

    printf("\nlist: \n");
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");
    TEST(!status);

    PURPLE("\n2. removes\n");

    printf("list: \n");
    AVLForEach(tree, PrintInt, NULL);
    printf("\n\n");

    for(i = 0; i < sizeof(to_remove) / sizeof(int); ++i)
    {
        AVLRemove(tree, &to_remove[i]);
        printf("%d removed, height: %ld, exp: %ld\n", to_remove[i], AVLHeight(tree), exp_remove[i]);
        if(AVLHeight(tree) != exp_remove[i])
        {
            status = 1;
        }
    }
    printf("\n");
    TEST(!status);

    AVLDestroy(tree);
}

/*===============static functions=======================*/

static int CompareInt(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    return(*(int*)data1 - *(int*)data2);
}

static int PrintInt(void *data, void *param)
{
    UNUSED(param);
    printf("%d ", *(int*)data);
    return(0);
}

