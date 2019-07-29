#ifndef  _TRIE_H_  
#define  _TRIE_H_  


/****************************************************************
*                <<<<<<<< TRIE >>>>>>>>                         *
* Related files: trie.c, trie.h                                 *
* #Version: V 1                                                 *
* Writer: Michal Adler                                          *
* Reviewer: Ofer Tauber                                         *
* Last update: 16/06/19                                         *
****************************************************************/ 

#include <stddef.h> /* size_t */

typedef struct trie trie_t;
typedef unsigned long ulong;


trie_t *TrieCreate(size_t capacity, size_t max_levels_num);


void TrieDestroy(trie_t *trie);


int TrieAllocIP(trie_t *trie,  ulong *ip_ptr);
	

int TrieFreeIP(trie_t *trie,  ulong *ip_ptr);


size_t TrieCountFree(const trie_t *trie);


#endif /* _DHCP_H_ */