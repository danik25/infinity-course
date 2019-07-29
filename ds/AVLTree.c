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
#include <assert.h> /*assert */
#include <stdlib.h> /* malloc, abs */

#include "AVLTree.h"

enum CHILDREN {LEFT, RIGHT};
#define MAX(x, y) (((x) > (y)) ? (x) : (y));

typedef struct node
{
    void *data;
    struct node *children[2];
    size_t height;
}AVL_node_t;

struct AVL
{
    AVL_node_t *root;
    compare_t CompareFunc;
    void *param;
};

/* lut for rotation cases, used in balance function */
typedef AVL_node_t *(*rotation_case_func)
                    (AVL_node_t *root, AVL_node_t *pivot, int direction);


/********************** assistance functions for remove **********************/

static AVL_node_t* RecFindParent(AVL_node_t *node, compare_t CompareFunc, 
                                        const void *data, void* param);
static AVL_node_t* RecFindNodeToRemove(AVL_node_t *node, compare_t CompareFunc, 
                                        const void *data, void* param);
static void RecRemoveOneChildNode(AVL_node_t *parent_node, 
                                        void *data, AVL_t *tree);
static void RecRemoveRoot(AVL_node_t *root, AVL_t *tree);
static AVL_node_t* FindTheNextNode(AVL_node_t *node);
static void RecHeightUpdate(AVL_node_t *root, AVL_node_t *removed_parent, 
                                        compare_t CompareFunc, void *param);
static AVL_node_t* ComplicatedCase(AVL_node_t *root, AVL_node_t *pivot, 
                                                        int rot_direction);

/******************************************************************************/


/************************ general assistance functions ************************/

static int HasOneChild(AVL_node_t *node);
static int ChildDirection(AVL_node_t *node);
static int Isleaf(AVL_node_t *node);
static int HasTwoChildren(AVL_node_t *node);
static AVL_node_t* NodeCreate(void *data);

/*****************************************************************************/


/********************** recursive assistance functions **********************/

static AVL_node_t* RecDestroy(AVL_node_t *node);
static int RecInsert(AVL_node_t *tree_node, AVL_node_t *new_node, AVL_t *tree);

static AVL_node_t* RecFind(AVL_node_t *node, compare_t CompareFunc, 
                                    const void *data, void* param);
static int RecCount(AVL_node_t *node);
static int RecForEach(AVL_node_t *node, action_func_t ActionFunc, void* param);

/*****************************************************************************/


/****************************** balancing functions ***************************/

static AVL_node_t* Rotate(AVL_node_t *root, AVL_node_t *pivot, int direction);
static int HeightGap(AVL_node_t *node);
static void Balance(AVL_t *tree, AVL_node_t *sub_root, int balance_factor);
static void HeightUpdate(AVL_node_t *node);
static size_t GetNodeHeight(AVL_node_t *node);

/*****************************************************************************/

/******************************************************************************

                        ************* API *****************

******************************************************************************/

AVL_t *AVLCreate(compare_t CompareFunc, void *param)
{
    AVL_t * tree_handle = NULL;

    assert(CompareFunc);

    tree_handle = (AVL_t*)malloc(sizeof(AVL_t));

    if(NULL == tree_handle)
    {
        return (NULL);
    }

    tree_handle->CompareFunc = CompareFunc;
    tree_handle->param = param;
    tree_handle->root = NULL;

    return(tree_handle);
}

void AVLDestroy(AVL_t *tree)
{
    assert(tree);

    RecDestroy(tree->root);

    free(tree);
    tree = NULL;   
}

int AVLInsert(AVL_t *tree, void *data)
{
    AVL_node_t * new_node = NULL;

    assert(tree);

    new_node = NodeCreate(data);

    /* failure in creating new node */
    if(!new_node)
    {
        return (1);
    }

    if(AVLIsEmpty(tree))
    {
        tree->root = new_node;
    }
    else
    {
        return(RecInsert(tree->root, new_node, tree));
    }

    return (0);    
}

void AVLRemove(AVL_t *tree, void *data)
{
    AVL_node_t *node = NULL;
    AVL_node_t *next_node = NULL;
    AVL_node_t * remove_parent = NULL;
    void *data_to_replace = NULL;
    int balance_factor = 0;

    assert(tree);

    /* if the data inserted for removal doesnt exists */
    if(!AVLFind(tree, data))
    {
        return ;
    }

    node = RecFindNodeToRemove(tree->root, tree->CompareFunc, data, 
                                                        tree->param);
    /* has two children */
    if(HasTwoChildren(node))
    {
        /* finding the next node and saving it's data */
        next_node = FindTheNextNode(node->children[RIGHT]);
        data_to_replace = next_node->data;

        /* finding the parent of the "next node", 
                                the next node needs to be removed now */
        remove_parent = RecFindParent(tree->root, 
                            tree->CompareFunc, next_node->data, tree->param);

        /* removing the node that it's data was copied */
        RecRemoveOneChildNode(remove_parent, next_node->data, tree);

        node->data = data_to_replace;    

        RecHeightUpdate(tree->root, remove_parent, tree->CompareFunc, 
                                                            tree->param);
        return ;
    }

    /* if the node to be removed is the root */
    if(0 == tree->CompareFunc(tree->root->data, data, tree->param))
    {
        if(Isleaf(node))
        {
            free(node);
            node = NULL;
            tree->root = NULL;
            return ;
        }
        RecRemoveRoot(tree->root, tree);
        return ;
    }

    /* in case the node to be removed has an only child or no children at all */
    if(Isleaf(node) || HasOneChild(node))
    {
        remove_parent = RecFindParent(tree->root, 
                        tree->CompareFunc, data, tree->param);
        RecRemoveOneChildNode(remove_parent, data, tree);
    }

    balance_factor = HeightGap(tree->root);
    if(abs(balance_factor) > 1)
    {
        Balance(tree, tree->root, balance_factor);
        HeightUpdate(tree->root);
    }
}


void *AVLFind(const AVL_t *tree, const void *data)
{
    assert(tree);

    if(!AVLIsEmpty(tree))
    {
        return(RecFind(tree->root, tree->CompareFunc, data, tree->param));
    }
    
    return(NULL);
}


size_t AVLCount(const AVL_t *tree)
{
    assert(tree);

    if(AVLIsEmpty(tree))
    {
        return(0);
    }
    return(RecCount(tree->root));
}

int AVLIsEmpty(const AVL_t *tree)
{
    assert(tree);

    return(NULL == tree->root);
}

size_t AVLHeight(const AVL_t *tree)
{
    assert(tree);

    if(AVLIsEmpty(tree))
    {
        return(0);
    }

    return(tree->root->height);
}

int AVLForEach(AVL_t *tree, action_func_t ActionFunc, void *param)
{
    assert(tree);
    assert(ActionFunc);

    if(AVLIsEmpty(tree))
    {
        return(1);
    }

    return(RecForEach(tree->root, ActionFunc, param));
}



/******************************************************************************

            ************* balancing functions *****************

******************************************************************************/

static AVL_node_t* Rotate(AVL_node_t *root, AVL_node_t *pivot, int direction)
{
    assert(root);
    assert(pivot);

    root->children[direction] = pivot->children[!direction];
    pivot->children[!direction] = root;

    HeightUpdate(root);
    HeightUpdate(pivot);

    return(pivot);
}

static int HeightGap(AVL_node_t *node)
{
    /* the difference between the height of the 
                        right node and the left node is greater than 1 */
    return(GetNodeHeight(node->children[RIGHT]) - 
                        GetNodeHeight(node->children[LEFT]));
}

static AVL_node_t* ComplicatedCase(AVL_node_t *root, AVL_node_t *pivot, 
                                                        int rot_direction)
{
    /* left rotation */
    pivot = Rotate(root->children[rot_direction], 
                root->children[rot_direction]->children[!rot_direction], 
                                            !rot_direction);
    root->children[rot_direction] = pivot;

    pivot = Rotate(root, pivot, rot_direction);

    HeightUpdate(root);
    HeightUpdate(pivot);

    return (pivot);
}

static void Balance(AVL_t *tree, AVL_node_t *sub_root, int balance_factor)
{
    AVL_node_t *pivot = NULL;
    AVL_node_t *root_parent = NULL;
    int direction = 0;
    int rotate_direction = 0;
    int height_gap = 0;

    /*
        _|_______|_______0__________|__________1___________|  
         |       |  height_gap < 0  |   height_gap > 0     |
      ___|_______|__________________|______________________|
       0 |gap < 0| Rotate           | ComplicatedCase      |
         |       | (left left)      | (left right)         |
      ___|_______|__________________|______________________|
       1 |gap > 0| ComplicatedCase  | Rotate               |
         |       | (right left)     | (right right)        |
      ___|_______|__________________|______________________|
    
    */

    rotation_case_func rot_lut[2][2] = 
    {
        {Rotate, ComplicatedCase},
        {ComplicatedCase, Rotate}
    };

    rotate_direction = (balance_factor > 0);
    height_gap = (HeightGap(sub_root->children[rotate_direction]) > 0);

    pivot = (*rot_lut[rotate_direction][height_gap])
            (sub_root, sub_root->children[rotate_direction], rotate_direction);
 

    /* if the balancing is happening on the root */
    if(sub_root->data == tree->root->data)
    {
        tree->root = pivot;
    }

    else
    {
        root_parent = RecFindParent(tree->root, 
                        tree->CompareFunc, sub_root->data, tree->param);
        direction = tree->CompareFunc(sub_root->data, 
                            root_parent->data, tree->param) > 0 ? RIGHT : LEFT;
        root_parent->children[direction] = pivot;
    }

    HeightUpdate(pivot); 
}

static void HeightUpdate(AVL_node_t *node)
{
    node->height = 1 + MAX(GetNodeHeight(node->children[LEFT]), 
                GetNodeHeight(node->children[RIGHT]));
}
/******************************************************************************

            ************* general assistance functions *****************

******************************************************************************/

static AVL_node_t* NodeCreate(void *data)
{
    AVL_node_t *node = (AVL_node_t*)malloc(sizeof(AVL_node_t));
    if(!node)
    {
        return (NULL);
    }
    node->data = data;
    node->height = 1;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;

    return(node);
}

static int HasOneChild(AVL_node_t *node)
{
    return((NULL != node->children[LEFT] && NULL == node->children[RIGHT]) ||
           (NULL == node->children[LEFT] && NULL != node->children[RIGHT]));
}

static int ChildDirection(AVL_node_t *node)
{
    /* if the left child is NULL, returns 1, which is "right". and vise versa */
    return(NULL == node->children[LEFT]);
}

static int Isleaf(AVL_node_t *node)
{
    return(NULL == node->children[LEFT] && NULL == node->children[RIGHT]);
}

static int HasTwoChildren(AVL_node_t *node)
{
    return(NULL != node->children[LEFT] && NULL != node->children[RIGHT]);
}

static size_t GetNodeHeight(AVL_node_t *node)
{
    if(NULL == node)
    {
        return (0);
    }
    return(node->height);
}

/******************************************************************************

              ************* static recursive functions *****************

******************************************************************************/

static int RecInsert(AVL_node_t *tree_node, 
                    AVL_node_t *new_node, AVL_t *tree)
{
    int direction = tree->CompareFunc(new_node->data, tree_node->data, 
                                                                tree->param); 
    int ans = 0;  
    int balance_factor = 0;              
    if(0 == direction)
    {
        return (1);
    }

    direction = (direction > 0) ? RIGHT : LEFT;

    if(NULL == tree_node->children[direction])
    {
        tree_node->children[direction] = new_node;
        if(NULL == tree_node->children[!direction])
        {
            tree_node->height += 1;
        }
        return(0) ;
    }
    ans = RecInsert(tree_node->children[direction], new_node, 
                                                    tree);
    HeightUpdate(tree_node);

    balance_factor = HeightGap(tree_node);
    if(abs(balance_factor) > 1)
    {
        Balance(tree, tree_node, balance_factor);
    }

    return(ans);

}

static AVL_node_t* RecFind(AVL_node_t *node, compare_t CompareFunc, 
                                                const void *data, void* param)
{
    int direction = CompareFunc(data, node->data, param);
                                                                       
    if(direction == 0)
    {
        return(node->data);
    }
    direction = (direction > 0);

    if(NULL == node->children[direction])
    {
        return (NULL);
    }

    return(RecFind(node->children[direction], CompareFunc, data, param));
}

static int RecForEach(AVL_node_t *node, action_func_t ActionFunc, void* param)
{
    if(NULL == node)
    {
        return(0);
    }
    
    if(RecForEach(node->children[LEFT], ActionFunc, param))
    {
        return(1);
    }
    if(ActionFunc(node->data, param))
    {
        return(1);
    }
    if(RecForEach(node->children[RIGHT], ActionFunc, param))
    {
        return(1);
    }
    return(0);
}

static AVL_node_t * RecDestroy(AVL_node_t *node)
{
    if(NULL != node)
    {
        RecDestroy(node->children[LEFT]);    
        RecDestroy(node->children[RIGHT]);

        free(node);
    }

    return(node);   
}

static int RecCount(AVL_node_t *node)
{
    if(NULL == node)
    {
        return(0);
    }
    
    return (1 + RecCount(node->children[LEFT]) + 
                                    RecCount(node->children[RIGHT]));
}

/*****************************************************************************/

                        /* remove assistance functions */

/*****************************************************************************/

static AVL_node_t* RecFindParent(AVL_node_t *node, 
                        compare_t CompareFunc, const void *data, void* param)
{
    int direction = (CompareFunc(data, node->data, param) > 0) ? RIGHT : LEFT;
                                                                       
    if(0 == CompareFunc(data, node->children[direction]->data, param))
    {
        return(node);
    }

    return(RecFindParent(node->children[direction], 
                                            CompareFunc, data, param));
}

static AVL_node_t* RecFindNodeToRemove(AVL_node_t *node, compare_t CompareFunc, 
                                                const void *data, void* param)
{
    int direction = (CompareFunc(data, node->data, param) > 0) ? RIGHT : LEFT;
                                                                       
    if(0 == CompareFunc(data, node->data, param))
    {
        return(node);
    }

    return(RecFindNodeToRemove(node->children[direction], CompareFunc, 
                                                            data, param));
}

static void RecRemoveOneChildNode(AVL_node_t *parent_node, 
                                                    void *data, AVL_t *tree)
{
    int gap = 0;
    /* the direction of the node to be removed from the parent */
    int remove_direction = 
        (tree->CompareFunc(data, parent_node->data, tree->param)) > 0 ? 
                                                                RIGHT : LEFT;

    /* the direction of the child of the node to be removed */
    int child_direction = 
                    ChildDirection(parent_node->children[remove_direction]); 

    /* the child of the node to be removed */
    AVL_node_t *new_child = 
            parent_node->children[remove_direction]->children[child_direction];

    free(parent_node->children[remove_direction]);
    parent_node->children[remove_direction] = new_child;
    
    HeightUpdate(parent_node);

    RecHeightUpdate(tree->root, parent_node, tree->CompareFunc, tree->param);

    gap = HeightGap(parent_node);
    if(abs(gap) > 1)
    {
        Balance(tree, parent_node, gap);
        HeightUpdate(parent_node);
    }
    
}

static void RecRemoveRoot(AVL_node_t *root, AVL_t *tree)
{
    /* if the root has only one child */
    if(HasOneChild(root))
    {
        tree->root = root->children[ChildDirection(root)];
        free(root);
    }
}

static AVL_node_t* FindTheNextNode(AVL_node_t *node)
{
    AVL_node_t *ret_node = NULL;

    if(NULL != node->children[LEFT])
    {
        ret_node = FindTheNextNode(node->children[LEFT]); 
        return(ret_node);
    }
    return(node);
}

static void RecHeightUpdate(AVL_node_t *root, AVL_node_t *removed_parent, 
                                        compare_t CompareFunc, void *param)
{
    int direction = CompareFunc(removed_parent->data, root->data, param) > 0 
                                                            ? RIGHT : LEFT;
    if(root->data == removed_parent->data)
    {
        return ;
    }

    RecHeightUpdate(root->children[direction], removed_parent, CompareFunc, 
                                                                    param);

    HeightUpdate(root);
}
