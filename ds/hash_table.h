#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stddef.h>

/****************************************************************
*                Data Structures - Hash Table`
* file: hash_table.h
* Related files: hash_table.c, hash_table_test.c
* #Version: V 1.2
* Writer: Dani Benjmain
* Reviewer: Idan Argaman
* Last update: 04/06/19
****************************************************************/
/* API DESCRIPTION
 * Hash table is an associative container that contains key-value pairs
 * with unique keys. Search, insertion, and removal of elements have
 * average constant-time complexity.
 *
 * Internally, the elements are not sorted in any particular order,
 * but organized into buckets. Which bucket an element is placed
 * into depends entirely on the hash of its key. This allows fast
 * access to individual elements, since once the hash is computed,
 *  it refers to the exact bucket the element is placed into.
*/


typedef struct hash_table hash_t;


/* Description: function that receives a key and returns the index
 *              of it in the hash table.
 *
 * Params: data - a pointer to the key of the data from the user.
 *
 * Return Value: index associated to the key in the hash table.
 *
 */
typedef size_t (hash_func_t)(const void *data);

/* Description: function that receives two pointers of data to be
 *              compared and compares them.
 *
 * Params: data1, data2 - pointers to the data to be compared.
 * 
 *
 * Return Value: Boolean - TRUE (1) - items match.
 *                         FALSE (0) - items do not match.
 */

#ifndef _DL_LIST_
typedef int (compare_function_t)(void *data1, void* data2);
#endif /* _DL_LIST_ */

/* Description: function that executes a certain action on the given
 *              data.
 *
 * Params: data - a pointer to the data to be processed.
 *         param - users parameter as necessary.
 *
 * Return Value: status - success (0), otherwise as determined by the user.
 *
 */
typedef int (action_func_t)(void *data, void *param);

/* Description: creates the hash table and its handle.
 *
 * Params: capacity - the number of entries in the table.
 *         HashFunc - the function that provides the hash.
 *         IsMatch - the function for comparisons in the hash table.
 *
 * Return Value: a pointer to the handle.
 *              NULL in case of failure.
*/
hash_t *HashCreate(size_t capacity, hash_func_t HashFunc, 
                                    compare_function_t CompareFunc);

/* Description: frees the hash table and its handle.
 *              If table is NULL, no operation is performed.
 *
 * Params: table - pointer to the handle.
 *
*/
void HashDestroy(hash_t *table);


/* Description: inserts  a key to the hash table.
 *             in case of duplicate data - overwrite the old data with new data
 * Params: table - pointer to the handle.
 *          data - pointer to the key to be inserted.
 *
 *
 * Return Value: status  - success (0) or failure (1).
 *
*/
int HashInsert(hash_t *table, const void *data);


/* Description: removes a key from the hash table.
 *
 * Params: table - pointer to the handle.
 *          data - pointer to the key to be removed.
 *
*/
void HashRemove(hash_t *table, void *data);

/* Description: retreives a key (and associated data) from the hash table.
 *
 * Params: table - pointer to the handle.
 *          data - pointer to the key to be found.
 *
 *
 * Return Value: pointer to the data associated to the key.
 *               NULL if data not found.
*/
void *HashFind(const hash_t *table, const void *data);


/* Description: provides the amount of the used entries in the array.
 *
 * Params: table - pointer to the handle.
 *
 * Return Value: the amount of used entries.
 *
 * complexity: O(1).
 *
*/
size_t HashSize(const hash_t *table);


/* Description: apply action function. to each key in the array.
 *
 * Params: table - pointer to the handle.
 *         ActFun - action_func_t supplied by user.
 *         param - users parameter as necessary.
 *
 * Return Value: status - success (0) or action function fail status.
 *
*/
int HashForEach(hash_t *table, action_func_t ActFunc, void *param);





#endif /* _HASH_TABLE_H_ */