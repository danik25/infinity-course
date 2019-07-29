#ifndef ILHRD_SLIST_HPP
#define ILHRD_SLIST_HPP

/****************************************************************
*                              Slist
* 						=====================
* File Name: slist.hpp
* Related files: slist.cpp slist_test.cpp
* #Version: V 1.0
* Writer: Dani Benjamin     
* Reviewer: Tom Valershtein     
* Last update: 22/07/19
****************************************************************/


#include <cstddef> //size_t

namespace hrd9
{

class Slist //uncopyable
{
public:
	explicit Slist();
	~Slist();

	//May fail
	void push_front(int data);

	void pop_front();

	int peek_head() const;

	//O(n)
	size_t size() const;

	//O(1)
	bool is_empty() const;

private: 
	Slist(const Slist& other);
	Slist& operator=(const Slist& other);

	struct Node;
	Node* head;
};	
}//namespace hrd9

#endif //ILHRD_SLIST_HPP


