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
    List(List_entry& x) {
        current_position = count = 0;
        current = head = NULL;

        head->entry = x;
        count++;
    }

    Error_code insert(int position, const List_entry& x);
    Error_code median(List_entry& x);
    bool clear();
    bool empty();
    bool full();
    Error_code retrieve(int pos, List_entry& x);
    Error_code replace(int pos, const List_entry& x);



    void setHead(Node<List_entry>* h);
    Node<List_entry>* getHead();
    int getCount();

    Error_code remove(int position, List_entry& x) {
        /*
    * position 0 -> count
    * current_position 0 -> count
    */
        if (count > MAXSIZE) return overflow;
        if (position < 0) return underflow;
        if (position > count) return overflow;

        Node<List_entry>* temp = new Node<List_entry>;

        temp = head;

        if (position == 0) {
            if (head->next == NULL) return overflow;
            head = head->next;
        }
        else {
            for (int i = 0; i < position; i++) {
                temp = temp->next;
            }

            Node<List_entry>* nearhead = new Node<List_entry>;
            Node<List_entry>* neartail = new Node<List_entry>;

            nearhead = temp->back;
            neartail = temp->next;

            nearhead->next = neartail;
            neartail->back = nearhead;
        }

        x = temp->entry;

        current = temp->next;

        delete temp;
        count--;

        return success;
    }

    Error_code traverse(int start, int end) {
        if (start == end) return duplicate_error;
        if (count < 1) return underflow;
        if (start > count || end > count) return overflow;
        if (start < 0 || end < 0) return underflow;

        Node<List_entry>* temp = new Node<List_entry>;
        temp = head;

        for (int i = 0; i < start; i++) {
            temp = temp->next;
        }

        if (start < end) {
            //traverse forward
            for (int i = 0; i < end - start; i++) {
                std::cout << temp->entry << ' ';
                temp = temp->next;
            }
        }
        else if (end < start) {
            //trverse backward
            for (int i = 0; i < start - end; i++) {
                std::cout << temp->entry << ' ';
                temp = temp->back;
            }
        }
        else { return fail; }

        current = temp;

        delete temp;

        return success;
    }

    Error_code reverse() {
        if (count == 0 || count == 1) return underflow;

        /*while (head->next != NULL) {
            head = head->next;
            std::cout << " head " << head->entry << ' ';
        }*/

        List<List_entry> tlist;
        Node<List_entry>* temp = new Node<List_entry>;
        temp = head;

        List_entry buffer;
        for (int i = 0; remove(0, buffer) == success; i++) {
            tlist.insert(i, buffer);
        }

        for (int i = 0; tlist.remove(0, buffer) == success; i++) {
            insert(0, buffer);  
        }

        return success;
    }

    Error_code interchange(int pos1, int pos2) {
        if (pos1 > count || pos2 > count) return overflow;
        if (pos1 == pos2) return duplicate_error;
        if (pos1 < 0 || pos2 < 0) return underflow;
        if (count < 2) return underflow;

        Node<List_entry>* switcher = new Node<List_entry>;
        Node<List_entry>* temp1 = new Node<List_entry>;
        Node<List_entry>* temp2 = new Node<List_entry>;

        temp1 = temp2 = head;

        for (int i = 0; i < pos1; i++) {
            temp1 = temp1->next;
        }
        for (int i = 0; i < pos2; i++) {
            temp2 = temp2->next;
        }

        switcher->entry = temp1->entry;
        temp1->entry = temp2->entry;
        temp2->entry = switcher->entry;

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

            new_node->back = this->current;
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