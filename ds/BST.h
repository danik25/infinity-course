#ifndef  _BST_H_
#define  _BST_H_

#include <stddef.h>

/****************************************************************
*                         Binary Search Tree
*                       =====================
* File Name: BST.h
* Related files: BST.c, BST_test.c
* #Version: V 2.3
* Writer: Dani Benjamin                         
* Reviewer: Lev Shubert    
* Last update: 20/05/19
****************************************************************/

typedef struct BST BST_t;
typedef struct node *BST_iter_t;

/* API Design:
 * Binary search tree keep it's keys in sorted order,
 * so that lookup and other operations can use the principle of binary search:
 * when looking for a key in a tree (or a place to insert a new key),
 * they traverse the tree from root to leaf,
 * making comparisons to keys stored in the nodes of the tree and deciding,
 * on the basis of the comparison,
 * to continue searching in the left or right subtrees .
 *
 * -insertions of equals element is undefind and may not be supported !!!.
 * -user may insert any kind of data pointers including NULL
 * 
 *
 *
 *
 *
 */




/* compare_t  DESCRIPTION:
 *
 * return values: an integer "num" such that:
 *
 *  num < 0 if data1 < data2
 *  num = 0 if data1 = data2
 *  num > 0 if data1 > data2
 *
 *
*/
typedef int (*compare_t)(const void *data1, const void *data2, void *param);


 /* action function DESCRIPTION:
 *
 * a function that perform user action on each data.
 * return val : status flag 0 = success, 1 = failure
 *
 *
 *
 *
 */
typedef int (*action_func_t)(void *data, void *param);


/* Description:
 * Creates a new binary search tree .
 *
 *
 * Params:
 *        CompareFunc - A pointer to a function to determine the order in which
 *                     key are sorted in the structure.
 *        param - parameter for IsBefore function.
 *
 * Return Value: A pointer to the tree data structure.
 *               NULL if failed.
*/
BST_t* BSTCreate(compare_t CompareFunc, void *param);



/* Description: destroys the given tree .
 *
 * Params: tree - A pointer to the tree data structure.
 *
*/
void BSTDestroy(BST_t *tree);


/* Description:insert a new data to the tree.
 *
 * Params: tree - A pointer to the tree data structure.
 *         data - data to insert.
 *
 * Return Value: A pointer to the inserted element.
 *               NULL if failed.
*/
BST_iter_t BSTInsert(BST_t *tree, void *data);


/* Description:removed a specific element from the tree.
 *
 * Params: element - element to remove.
 *
 * Return Value: void
 * ***** WARNNING: REMOVE MAY INVALDATE ITERS TO TREE NODES******
*/
void BSTRemove(BST_iter_t element);


/* Description: try to find the specific data in the tree.
 *
 * Params: tree - A pointer to the tree in which to find data.
 *         data - A pointer to data to find.
 *
 * Return Value: first occurence of the data supplied by the user.
 *               dummy node if data not found.
 *

 * Time complexity: O(n).
*/
BST_iter_t BSTFind(const BST_t *tree, const void *data);


/* Description: get the size of the data structure.
 *
 * Time complexity: O(n).
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: number of elements in the tree.
 *
*/
size_t BSTCount(const BST_t *tree);


/* Description: checks if the tree contains any data.
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: true = 1, false = 0.
 *
*/
int BSTIsEmpty(const BST_t *tree);


/* Description:apply a function to each element in the given range.
 *
 * Params:
 *         ActionFunc - A pointer to an action function to be performed on each
 *                      element in the tree. The action will apply to each node
 *                      between from and to (exclusive).
 *         param - a parameter for the action function.
 *         from  - pointer to the start iter
 *         to    - pointer to the end iter
 *
 *
 * Return Value: Success (0) or Failure (1).
 *
*/
int BSTForEach(BST_iter_t from, BST_iter_t to, action_func_t ActionFunc,
                                                                   void *param);


/* Description: get an iter to the first element.
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: A pointer to the element that holds the minimal value data in
 *               the tree. dummy node if tree is empty. 
*/
BST_iter_t BSTBegin(const BST_t *tree);


/* Description: get iter to the last element.
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: pointer to the dummy node
*/
BST_iter_t BSTEnd(const BST_t *tree);


/* Description:get iter to next element
 *
 * Params: element - A pointer to an element in the tree.
 *
 * Return Value: Pointer to the element the holds the next value in the
 *               tree. Pointer to dummy node iter if element contains the
 *               <max value> given as input.
 *               if element is the dummy node then the return val is undefined. 
 *               
*/
BST_iter_t BSTNext(BST_iter_t element);


/* Description: get iter to previous element.
 *
 * Params: element - A pointer to an element in the tree.
 *
 * Return Value: A pointer to the element the holds the previous value in the
 *               tree. 
 *               the beaviour is undifined if input is BSTBegin 
*/                  
BST_iter_t BSTPrev(BST_iter_t element);


/* Description: get data stored in element
 *
 * Params: element - A pointer to an element from which to extract data.
 *
 * Return Value: A Pointer to the extracted data.
 *               undefined if dummy node whas given as an argument.
 *
*/
void * BSTGetData(BST_iter_t element);


/* Description: checks if the two given iters are the same.
 *
 * Params: first_iter, second iter - iterators to be compared.
 *
 * Return Value: Boolean.
 *
*/
int BSTIsSameIter(const BST_iter_t first_iter, const BST_iter_t second_iter);


#endif /* _BST_H_  */