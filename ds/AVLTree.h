#ifndef  _AVL_H_
#define  _AVL_H_

#include <stddef.h> /* size_t */

#include "dl_list.h"

/****************************************************************
*                       AVL Binary Search Tree
*                       =====================
* File Name: AVLTree.h
* Related files: AVLTree.c, AVLTree_test.c
* #Version: V 1.1
* Writer: Dani Benjamin      
* Reviewer: Moshe Greenberg     
* Last update: 02/06/19
****************************************************************/

/* API Design:
 * An AVL Binary Search Tree, Following the same restrictions as a BST
 * With an added feature of self balancing.
 * this structures is guarenteed to be always balanced as per conventional 
 * definition of a balanced tree structure.
 *
 * This AVL Tree DOES NOT support duplicate data.
 * In our structure the Height of an empty tree, as will be returned from
 * AVLHeight, will be 0. Height of a leaf will be 1.
 * 
 */

/*** Services and Auxiliaries: ***/

/* compare_t  DESCRIPTION:
 *
 * return values: an integer "num" such that:
 *
 *  num < 0 if data1 < data2
 *  num = 0 if data1 = data2
 *  num > 0 if data1 > data2
*/

typedef int (*compare_t)(const void *data1, const void *data2, void *param);
typedef int (*is_match_t)(void *data, void *param);

 /* action function DESCRIPTION:
 *
 * a function that perform user action on each data.
 * return val : 0 = success, otherwise failure according to it's failure code.
 */
typedef int (*action_func_t)(void *data, void *param);

typedef struct AVL AVL_t;


/* Description:
 * Creates a new binary search tree .
 *
 * Params: CompareFunc - A pointer to a function to determine the order in which
 *                     key are sorted in the structure.
 *        param - parameter for Compare function.
 *
 * Return Value: A pointer to the tree data structure.
 *               NULL if failed.
 */
AVL_t *AVLCreate(compare_t CompareFunc, void *param);


/* Description: destroys the given tree .
 *
 * Params: tree - A pointer to the tree data structure.
 *
*/
void AVLDestroy(AVL_t *tree);


/* Description: insert new data to the tree.
 * 
 * Params: tree - A pointer to the tree data structure.
 *         data - data to insert.
 *
 * Return Value: Success (0) or:
 *               1 -  memeory allocation failure;
 *               2 -  element duplication failure;
 * 
*/
int AVLInsert(AVL_t *tree, void *data);


/* Description: remove data from the tree. 
 *
 * Params: tree - the tree from which the data is to be removed.
 *         data - data to be removed.
*/
void AVLRemove(AVL_t *tree, void *data);


/* Description: find specific data in the tree.
 *
 * Params: tree - A pointer to the tree in which to find data.
 *         data - A pointer to data to find.
 *
 * Return Value: pointer to data supplied by the user.
 *               NULL if data not found.
 *
 * Time complexity: O(log(n)).
*/
void *AVLFind(const AVL_t *tree, const void *data);


/* Description: Counts the number of elements in the tree.
 *
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: number of elements in the tree.
 *
 * Time complexity: O(n).
 *
*/
size_t AVLCount(const AVL_t *tree);


/* Description: A Boolean function designed to indicate presence or lack thereof
 *              of elements in the tree.
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: Boolean.
 *
*/
int AVLIsEmpty(const AVL_t *tree);


/* Description: A service set to indicate the height of the tree
 *
 * Params: tree - A pointer to the tree structure.
 *
 * Return Value: Height of the tree.
 *
*/
size_t AVLHeight(const AVL_t *tree);


/* Description:apply a function to each element in the given range.
 *
 * Params:
 *         tree    - A pointer to the tree structure.
 *         ActionFunc - A pointer to an action function to be performed on each
 *                      element in the tree.
 *
 *         param - a parameter for the action function.
 *
 * Return Value: Success (0) or return value of ActionFunc on failure.
 *
*/
int AVLForEach(AVL_t *tree, action_func_t ActionFunc, void *param);


/* Description: Finds all occurences of data by key, via is_match function.
                A user supplied doubly linked list will contain all of these 
                instances.
 *
 * Params: tree    - A pointer to the tree structure.
 *         dl_list - user supplied list to contain found cases.
 *         IsMatch - a user function to determine the key by which FindAll 
 *                   determines whether or not a certain element is valid.
 *         arg     - an argument or IsMatch.   
 * Return Value: Boolean.
 *
*/
int AVLFindAll(const AVL_t *tree, is_match_t IsMatch, void *arg, dll_t *list);


/* Description: Removes all occurences of data by key, via is_match function.
                A user supplied doubly linked list will contain all of these 
                instances.
 *
 * Params: tree    - A pointer to the tree structure.
 *         IsMatch - a user function to determine the key by which FindAll 
 *                   determines whether or not a certain element is valid.
 *         arg     - an argument or IsMatch.   
 *
*/
void AVLRemoveAll(AVL_t *tree, is_match_t IsMatch, void *arg);

#endif /* _AVL_H_  */