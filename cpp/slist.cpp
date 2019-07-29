/****************************************************************
*                              Slist
*                       =====================
* File Name: slist.cpp
* Related files: slist.hpp slist_test.cpp
* #Version: V 1.0
* Writer: Dani Benjamin     
* Reviewer: Tom Valershtein     
* Last update: 22/07/19
****************************************************************/

#include "slist.hpp"

namespace hrd9
{
struct Slist::Node
{
    explicit Node(int data, Node* next = 0);

    int m_data;
    Node* m_next;
};

/* node constructor */
Slist::Node::Node(int data, Node* next) : m_data(data), m_next(next)
{
    ;
}


/* slist special functions */
Slist::Slist(): head(0)
{
    ;
}

Slist::~Slist()
{
    Node* runner = head;

    while(0 != head)
    {
        runner = head;
        head = head->m_next;
        delete(runner);
    }
}


/* functions members */
void Slist::push_front(int data)
{
    Node* new_node = new Node(data, head);
    head = new_node;
}


void Slist::pop_front()
{
    if(0 != head)
    {
        Node* tmp_node = head;
        head = head->m_next;
        delete tmp_node;
    }
}


int Slist::peek_head() const
{
    if(0 != head)
    {
        return(head->m_data);
    }

    return(0);
}


size_t Slist::size() const
{
    size_t size = 0;
    Node* runner = head;

    while(0 != runner)
    {
        runner = runner->m_next;
        ++size;
    }

    return(size);
}


bool hrd9::Slist::is_empty() const
{
    return(0 == head);
}

}//namespace hrd9



