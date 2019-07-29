/****************************************************************
*                         Binary Search Tree                     
* 						=====================
* File Name: BST.c
* Related files: BST.c, BST_test.c 
* #Version: V 2.2                    
* Writer: Dani Benjamin                         
* Reviewer: Lev Shubert                        
* Last update: 20/05/19            
****************************************************************/ 

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "BST.h"

enum CHILDREN {LEFT, RIGHT};
 
typedef struct node
{
    void *data;
    struct node *parent;
    struct node *children[2];
}node_t;

struct BST
{
    node_t *dummy;
    compare_t CompareFunc;
    void *param;
};

/*static functions*/
static node_t *CreateNode(void * data);
static int IsLeaf(const BST_iter_t element);
static int IsRoot(const BST_iter_t element);
static int IsLeftChild(const BST_iter_t element);
static int IsRightChild(const BST_iter_t element);
static int HasOnlyLeftChild(const BST_iter_t element);
static int HasOnlyRightChild(const BST_iter_t element);

/*----------------------------------------------------------------------------*/

BST_t* BSTCreate(compare_t CompareFunc, void *param)
{
    BST_t * tree = NULL;
    node_t * dummy_node = NULL;

    assert(CompareFunc);

    tree = (BST_t*)malloc(sizeof(BST_t));

    if(NULL == tree)
    {
        return (NULL);
    }

    dummy_node = (node_t*)malloc(sizeof(node_t));

    if(NULL == dummy_node)
    {
        free(tree);
        tree = NULL;
        return (NULL);
    }
    /* dummy */
    dummy_node->children[LEFT] = NULL;
    dummy_node->children[RIGHT] = NULL;
    dummy_node->parent = NULL;
    dummy_node->data = NULL;

    tree->CompareFunc = CompareFunc;
    tree->param = param;
    tree->dummy = dummy_node;

    return(tree);
}

/*----------------------------------------------------------------------------*/
void BSTDestroy(BST_t *tree)
{
    node_t *runner = NULL;
    node_t *tmp = NULL;
    int count = 0;

    assert(tree);

    if(!BSTIsEmpty(tree))
    {
        count = BSTCount(tree);
        runner = BSTBegin(tree);

        while(count > 0)
        {
            while(!IsLeaf(runner))
            {   
                runner = BSTNext(runner);
            }
            tmp = runner->parent;
            tmp->children[IsRightChild(runner)] = NULL;
            free(runner);
            runner = tmp;
            --count;
        }
    }
    
    free(tree->dummy);
    tree->dummy = NULL;

    free(tree);
    tree = NULL;
}



/*----------------------------------------------------------------------------*/
BST_iter_t BSTInsert(BST_t *tree, void *data)
{
    node_t *new_node = NULL;
    node_t *runner = NULL;
    int compare_ans = 0;

    assert(tree);

    if(BSTIsEmpty(tree))
    {
        new_node = CreateNode(data);
        tree->dummy->children[LEFT] = new_node;
        tree->dummy->children[RIGHT] = new_node;
        new_node->parent = tree->dummy;
        return(new_node);
    }
    runner = BSTBegin(tree);
    compare_ans = tree->CompareFunc(data, runner->data, tree->param);

    while(compare_ans > 0 && BSTNext(runner) != BSTEnd(tree))
    {
        runner = BSTNext(runner);
        compare_ans = tree->CompareFunc(data, runner->data, tree->param);

    }
    if(0 == compare_ans)
    {
        return (NULL);
    }
    new_node = CreateNode(data);
    if(compare_ans < 0)
    {
        if(NULL != runner->children[LEFT] )
        {
            runner = BSTPrev(runner);
            while(NULL != runner->children[RIGHT])
            {
                runner = BSTNext(runner);
            }
            runner->children[RIGHT] = new_node;
        }
        else
        {
            runner->children[LEFT] = new_node;
        }
    }
    else
    {
        runner->children[RIGHT] = new_node;
    }
    new_node->parent = runner;
    return (new_node);
}

/*----------------------------------------------------------------------------*/

void BSTRemove(BST_iter_t element)
{
    assert(element);

    if(IsRoot(element) && IsLeaf(element))
    {
        element->parent->children[RIGHT] = NULL;
        element->parent->children[LEFT] = NULL;
        free(element);
        element = NULL;
        return;
    }
    /* has one child */
    if(HasOnlyRightChild(element) || HasOnlyLeftChild(element))
    {
        if(IsRoot(element))
        {
            element->parent->children[!IsRightChild(element)] = 
                            element->children[HasOnlyRightChild(element)];
        }
        element->parent->children[IsRightChild(element)] = 
                            element->children[HasOnlyRightChild(element)];
        element->children[HasOnlyRightChild(element)]->parent = element->parent;
        free(element);
        element = NULL;
        return ;
    }

    /* two children */
    while(!IsLeaf(element) && NULL != element->parent)
    {       
        element->data = BSTNext(element)->data;
        element = BSTNext(element);   
    }
    element->parent->children[IsRightChild(element)] = NULL;
    free(element);
    element = NULL;
}



/*----------------------------------------------------------------------------*/

BST_iter_t BSTFind(const BST_t *tree, const void *data)
{
    BST_iter_t runner = NULL;
    int compare = 0;
    int direction = 0;

    assert(tree);

    if(!BSTIsEmpty(tree))
    {
        runner = tree->dummy->children[LEFT];
        compare = tree->CompareFunc(data, runner->data, tree->param);
        while(compare != 0 && !IsLeaf(runner))
        {
            direction = (compare > 0) ? 1 : 0;
            if(!(runner->children[direction]))
            {
                return(tree->dummy);
            }
            runner = runner->children[direction];
            compare = tree->CompareFunc(data, runner->data, tree->param);
        }

        if(0 == compare)
        {
            return (runner);
        }
    }

    return (tree->dummy);
}

/*----------------------------------------------------------------------------*/

size_t BSTCount(const BST_t *tree)
{
    BST_iter_t runner = NULL;
    size_t cnt = 0;

    assert(tree);

    for(runner = BSTBegin(tree); runner != BSTEnd(tree); 
                                            runner = BSTNext(runner))
    {
        ++cnt;
    }
    
    return (cnt);
}

/*----------------------------------------------------------------------------*/

int BSTIsEmpty(const BST_t *tree)
{
    assert(tree);
    return(NULL == tree->dummy->children[LEFT]);
}

/*----------------------------------------------------------------------------*/

int BSTForEach(BST_iter_t from, BST_iter_t to, action_func_t ActionFunc,
																   void *param)
{
    BST_iter_t runner = NULL;

    assert(from);
    assert(to);
    assert(ActionFunc);

    for(runner = from; runner != to; runner = BSTNext(runner))
    {
    	if(ActionFunc(runner->data, param))
    	{
    		return(1);
    	}
    }
    return(0);
}

/*----------------------------------------------------------------------------*/

BST_iter_t BSTBegin(const BST_t *tree)
{
    BST_iter_t runner = NULL;

    assert(tree);
    if(BSTIsEmpty(tree))
    {
    	return(tree->dummy);
    }

    runner = tree->dummy->children[LEFT];
    while(NULL != runner->children[LEFT])
    {
        runner = runner->children[LEFT];
    }
    return(runner);
}

/*----------------------------------------------------------------------------*/

BST_iter_t BSTEnd(const BST_t *tree)
{
    assert(tree);

    return(tree->dummy);
}

/*----------------------------------------------------------------------------*/

BST_iter_t BSTNext(BST_iter_t element)
{
    assert(element);

    /* has a right child */
    if(NULL != element->children[RIGHT])
    {
        /* the leftiest child of the right node */
        element = element->children[RIGHT];
        while(NULL != element->children[LEFT])
        {
            element = element->children[LEFT];
        }
    }

    else
    {
        /* the first appearance of a parent that is bigger than the element */
        while(!IsLeftChild(element))
        {
            element = element->parent;
        }
        element = element->parent;
    }
    return(element);
}

/*----------------------------------------------------------------------------*/

BST_iter_t BSTPrev(BST_iter_t element)
{
    assert(element);

    /* has a left child */
    if(NULL != element->children[LEFT])
    {
        /* the rightest child of the right node */
        element = element->children[LEFT];
        while(NULL != element->children[RIGHT])
        {
            element = element->children[RIGHT];
        }
    }
    else 
    {
        /* the first appearance of a parent that is bigger than the element */
        while(!IsRightChild(element))
        {
            element = element->parent;
        }
        element = element->parent;
    }

    return(element);
}

/*----------------------------------------------------------------------------*/

void * BSTGetData(BST_iter_t element)
{
    if(NULL == element)
    {
        return(NULL);
    }
    return(element->data);
}

/*----------------------------------------------------------------------------*/

int BSTIsSameIter(const BST_iter_t first_iter, const BST_iter_t second_iter)
{
    assert(first_iter);
    assert(second_iter);

    return(first_iter == second_iter);
}

/*============================================================================*/

static node_t *CreateNode(void * data)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));

    if(!new_node)
    {
        return(NULL);
    }

    new_node->data = data;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;

    return (new_node);
}

static int IsLeaf(const BST_iter_t element)
{
    assert(element);
    return(NULL == element->children[LEFT] && NULL == element->children[RIGHT]);
}

static int IsRoot(const BST_iter_t element)
{
    assert(element);
    return(element->parent->children[LEFT] == element->parent->children[RIGHT]);
}

static int IsLeftChild(const BST_iter_t element)
{
    assert(element);
    if(NULL == element->parent)
    {
        return (0);
    }
    return(element->parent->children[LEFT] == element);
}

static int IsRightChild(const BST_iter_t element)
{
    assert(element);
    if(NULL == element->parent)
    {
        return (0);
    }
    return(element->parent->children[RIGHT] == element);
}

static int HasOnlyLeftChild(const BST_iter_t element)
{
    assert(element);
    return(NULL == element->children[RIGHT] && NULL != element->children[LEFT]);
}

static int HasOnlyRightChild(const BST_iter_t element)
{
    assert(element);
    return(NULL != element->children[RIGHT] && NULL == element->children[LEFT]);
}


