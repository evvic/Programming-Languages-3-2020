#ifndef	LIST_INCLUDED
#define LIST_INCLUDED

#include "Utility.h"


template <class Node_entry>
struct Node {
    //  data members
    Node_entry entry;
    Node<Node_entry>* next;
    Node<Node_entry>* back;
    //  constructors
    Node() {
        next = NULL;
        back = NULL;
    }
    Node(Node_entry, Node<Node_entry>* link_back = NULL,
        Node<Node_entry>* link_next = NULL);
};


template <class List_entry>
class List {
public:
    List() { count = 0; }

    Error_code insert(int position, const List_entry& x);
    Error_code remove(int position, List_entry& x);
    Error_code median(List_entry& x);
    Error_code interchange(int pos1, int pos2);

    void setHead(Node<List_entry>* h);
    Node<List_entry>* getHead();
    int getCount();
protected:
    //  Data members for the doubly-linked list implementation follow:
    int count;
    mutable int current_position;
    mutable Node<List_entry>* current;

    Node<List_entry>* head;

    //  The auxiliary function to locate list positions follows:
    void set_position(int position) const;
};


#endif