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
    Node();
    Node(Node_entry, Node<Node_entry>* link_back = NULL,
        Node<Node_entry>* link_next = NULL);
};


template <class List_entry>
class List {
public:
    List() {
        current_position = count = 0;
        current = head = NULL;
    }

    Error_code insert(int position, const List_entry& x);
    Error_code remove(int position, List_entry& x);
    Error_code median(List_entry& x);
    Error_code interchange(int pos1, int pos2);
    Error_code traverse(int start, int end);

    List& operator = (const List& rhs) {
        const Node<List_entry>* cpcurrent = rhs.head;
        Node<List_entry>* lscurrent = new Node<List_entry>;
        lscurrent = NULL;

        if (cpcurrent != NULL) {
            this->head = new Node<int>;
            head->entry = cpcurrent->entry;
            lscurrent = head;
            cpcurrent = cpcurrent->next;
        }

        while (cpcurrent != NULL) {
            Node<List_entry>* new_node = new Node<List_entry>;
            new_node->entry = cpcurrent->entry;
            lscurrent = lscurrent->next;
            cpcurrent = cpcurrent->next;
        }

        return *this;
    }



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