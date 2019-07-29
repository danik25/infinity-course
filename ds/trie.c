/****************************************************************
*                <<<<<<<< TRIE >>>>>>>>                         *
* Related files: trie.c, trie.h                                 *
* #Version: V 1                                                 *
* Writer: Michal Adler                                          *
* Reviewer: Ofer Tauber                                         *
* Last update: 16/06/19                                         *
****************************************************************/ 
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcmp */

#include "bit_array.h"
#include "trie.h"


 /* FAIL_CODE - 1 - allocation memory FAIL 
  *             2 - no address available */ 
enum FAIL_CODE {ALLOC_FAIL = 1, ADDRESS_FAIL};
enum STATUS {SUCCESS = 0, FAIL};
enum DATA {FREE = 0, STOP};
enum CHILDREN {LEFT, RIGHT};
 
typedef struct node
{
	size_t data;
	struct node *parent;
	struct node *children[2];
}node_t;

struct trie
{
	node_t *root;
	size_t capacity; /* max num of IPs */
	size_t size; /* current num of IPs in the trie */
	size_t max_levels_num; /* maximum levels in the trie */
};


/****************************************************************************/
/*                    Declerations Of Help(Node) Functions                  */
/****************************************************************************/
static node_t *NodeCreate(size_t data, node_t *parent);
static void NodeDestroy(node_t *node);
static void NodeDestroyRec(node_t *node);
static void NodeUpdateDataRec(node_t *node);


/****************************************************************************/
/*                          Trie Functions                                  */
/****************************************************************************/
trie_t *TrieCreate(size_t capacity, size_t max_levels_num)
{
	trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
	if (NULL == trie)
	{
		return (NULL);
	}

	trie->root = NodeCreate(FREE, NULL);
	if (NULL == trie->root)
	{
		free(trie);
		trie = NULL;

		return (NULL);
	}
	trie->capacity = capacity;
	trie->size = 0;
	trie->max_levels_num = max_levels_num;

	return (trie);
}


void TrieDestroy(trie_t *trie)
{
	assert(trie);
	
	NodeDestroyRec(trie->root);
	free(trie);
	trie = NULL;
}


int TrieAllocIP(trie_t *trie,  ulong *ip_ptr)
{
	node_t *node = NULL;
	size_t i = 0, index = 0, len = 0, k = 0;

	assert(trie);
	assert(trie->root);

	node = trie->root;
	if (STOP == node->data)
	{
	    *ip_ptr = 0;
		return (ADDRESS_FAIL);
	}	
	
	i = 0;
	len = trie->max_levels_num;
	while (i < len)
	{
		index = IsOn(*ip_ptr, len - 1 - i);

		/* child is NULL : */
		if (NULL == node->children[index])
		{
			node->children[index] = NodeCreate(FREE, node);	
			if (NULL == node->children[index])	
			{
				return (ALLOC_FAIL);
			}	
		}

		/* child's data is FREE : */
		if (FREE == node->children[index]->data)
		{
			node = node->children[index];	
			++i;
			continue;		
		}

		/* child's data is STOP : */
			
		for (k = 0; k < i; ++k)
		{
			if (IsOff(*ip_ptr, len - 1 - k))
			{
				break;
			}
		} 
		if ((k == i) && IsOn(*ip_ptr, len - 1 - i))
		{
			*ip_ptr = 0;
		    return (ADDRESS_FAIL);
		}
		
		*ip_ptr += 1; 
		return (TrieAllocIP(trie,  ip_ptr));
	}

	node->data = STOP;
	NodeUpdateDataRec(node->parent);

	trie->size += 1;
	
	return (SUCCESS);
}
	

int TrieFreeIP(trie_t *trie,  ulong *ip_ptr)
{
	node_t *node = NULL;
	size_t i = 0, index = 0, len = 0;

	assert(trie);
	assert(trie->root);

	node = trie->root;
	len = trie->max_levels_num;
	for (i = 0; i < len; ++i)
	{
		index = IsOn(*ip_ptr, len - 1 - i);

		if (NULL == node->children[index])
		{
			return (FAIL);	
		}
		node = node->children[index];
	}

	node = node->parent;
	NodeDestroy(node->children[index]);
	node->children[index] = NULL;
	NodeUpdateDataRec(node);

	trie->size -= 1;
	
	return (SUCCESS);
}


size_t TrieCountFree(const trie_t *trie)
{
	assert (trie);

	return (trie->capacity - trie->size);
}


/****************************************************************************/
/*                          Help(Node) Functions                                  */
/****************************************************************************/
static node_t *NodeCreate(size_t data, node_t *parent)
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->parent = parent;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;

	return (node);
}


static void NodeDestroy(node_t *node)
{
	free(node);
	node = NULL;
}


static void NodeDestroyRec(node_t *node)
{
	assert(node);

	if ((NULL == node->children[LEFT]) && (NULL == node->children[RIGHT]))
	{
		NodeDestroy(node);
		return;
	}

	if (NULL != node->children[LEFT])
	{
		NodeDestroyRec(node->children[LEFT]);
		node->children[LEFT] = NULL;
	}
	if (NULL != node->children[RIGHT])
	{
		NodeDestroyRec(node->children[RIGHT]);
		node->children[RIGHT] = NULL;
	}
	NodeDestroy(node);
}


static void NodeUpdateDataRec(node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	if (((NULL != node->children[LEFT]) && 
		(STOP == node->children[LEFT]->data)) && 
	   ((NULL != node->children[RIGHT]) && 
	    (STOP == node->children[RIGHT]->data)))
	{
		node->data = STOP;
	}
	else
	{
		node->data = FREE;
	}	
	
	NodeUpdateDataRec(node->parent);
}