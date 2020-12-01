#ifndef	LIST_INCLUDED
#define LIST_INCLUDED

#include "Utility.h"

//Singly linked list, head points next to tail

template <class Node_entry>
struct Node {
    //  data members
    Node_entry entry;
    Node<Node_entry>* next;
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
    List(List_entry& x) {
        current_position = count = 0;
        current = head = NULL;

        head->entry = x;
        count++;
    }
    List(List<List_entry>& x) {
        const Node<List_entry>* cpcurrent = x.head;
        Node<List_entry>* lscurrent = new Node<List_entry>;
        lscurrent = NULL;

        if (cpcurrent != NULL) {
            this->head = new Node<List_entry>;
            head->entry = cpcurrent->entry;
            lscurrent = head;
            cpcurrent = cpcurrent->next;
        }

        while (cpcurrent != NULL) {
            Node<List_entry>* new_node = new Node<List_entry>;
            new_node->entry = cpcurrent->entry;
            lscurrent->next = new_node;
            lscurrent = lscurrent->next;
            cpcurrent = cpcurrent->next;
        }
        current_position = 0;
        current = head;
        this->count = x.count;
    }

    ~List() {
        current = head;
        while (current != NULL) {
            Node<List_entry>* temp = new Node<List_entry>;
            temp = current->next;
            delete current;
            current = temp;
        }
        head = NULL;
    }
    
    int size();
    bool clear();
    bool empty();
    bool full();
    Error_code median(List_entry& x);
    Error_code retrieve(int pos, List_entry& x);
    Error_code replace(int pos, const List_entry& x);
    Error_code traverse(); //goes from head to tail
    Error_code interchange(int pos1, int pos2);
    Error_code remove(int position, List_entry& x);
    Error_code insert(int position, const List_entry& x); //template didn't work but in List.cpp

    void setHead(Node<List_entry>* h);
    Node<List_entry>* getHead();
    int getCount();

    //because of template this function must be in header (source)

    Error_code traverse(int start, int end) {
        if (start == end) return duplicate_error;
        if (count < 1) return underflow;
        if (start > count || end > count) return overflow;
        if (start < 0 || end < 0) return underflow;
        if (start > end) return entry_inserted; //since it can only go forward

        //traverse can only go forward because this is singly-linked

        current = head;

        //get to right position to start..
        for (current_position = 0; current_position < start; current_position++) {
            current = current->next;
        }

        //traverse forward
        for (; current_position < end; current_position++) {
            std::cout << current->entry << ' ';
            current = current->next;
        }

        return success;
    }

    //operator overloading, these templates must be in the header
    List& operator = (const List& rhs) {
        const Node<List_entry>* cpcurrent = rhs.head;
        Node<List_entry>* lscurrent = new Node<List_entry>;
        lscurrent = NULL;

        if (cpcurrent != NULL) {
            this->head = new Node<List_entry>;
            head->entry = cpcurrent->entry;
            lscurrent = head;
            cpcurrent = cpcurrent->next;
        }

        while (cpcurrent != NULL) {
            Node<List_entry>* new_node = new Node<List_entry>;
            new_node->entry = cpcurrent->entry;
            lscurrent->next = new_node;
            lscurrent = lscurrent->next;
            cpcurrent = cpcurrent->next;
        }

        this->count = rhs.count;

        return *this;
    }

    List& operator + (const List& rhs) {
        const Node<List_entry>* cpcurrent = rhs.head;

        this->current = this->head;
        while (current->next != NULL) {
            this->current = this->current->next;
            //cout << this->current->entry;
        }

        //this->current is now at this->tail

        while (cpcurrent != NULL) {
            this->count++;
            Node<List_entry>* new_node = new Node<List_entry>;
            this->current->next = new_node;

            new_node->entry = cpcurrent->entry;

            this->current = this->current->next;
            cpcurrent = cpcurrent->next; //incrememnt
        }

        return *this;
    }
    
protected:
    //  Data members for the doubly-linked list implementation follow:
    int count;
    const int MAXSIZE = 15;
    mutable int current_position;

    mutable Node<List_entry>* current;
    Node<List_entry>* head;

    //  The auxiliary function to locate list positions follows:
    void set_position(int position) const;
};


#endif