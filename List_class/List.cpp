#include "List.h"
#include "Utility.h"
#include <iostream>

using namespace std;



//template <class List_entry>
//List<List_entry>::List() {
//    count = 0;
//}


template <class List_entry>
void List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current Node pointer references the Node at position.
*/
{
    if (current_position <= position)
        for (; current_position != position; current_position++)
            current = current->next;
    else
        for (; current_position != position; current_position--)
            current = current->back;
};

template <class List_entry>
void List<List_entry>::setHead(Node<List_entry>* h) {
    head = h;
}

template <class List_entry>
Node<List_entry>* List<List_entry>::getHead() {
    return head;
}

template <class List_entry>
int List<List_entry>::getCount() {
    return count;
}

template <class List_entry>
Error_code List<List_entry>::median(List_entry& x) {
    Node<List_entry>* temp = new Node<List_entry>;
    temp = head;

    if (count % 2 == 0) {
        for (int i = 0; i < (count/2); i++) {
            temp = temp->next;
        }
        x = temp->entry;
    }
    else {
        for (int i = 0; i < (count / 2) + 1; i++) {
            temp = temp->next;
        }
        x = temp->entry;
    }

    return success;

}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry& x) {
    /*
    * position 0 -> count
    * current_position 0 -> count
    
    */
    if (count > 10) return overflow;
    if (position < 0) return underflow;
    if (position > count) return overflow;

    Node<List_entry>* temp = new Node<List_entry>;
    temp = head;

    if (position == 0) {
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


// TEMPLATE DID NOT WORK SO MULTIPLE COPIES OF INSERT WITH DIFFERENT DATA TYPES

Error_code List<int>::insert(int position, const int& x)
{
    if (count > 10/*temp max count*/) return overflow;
    if (position < 0) return underflow;
    if (position > count) return overflow;
    
    Node<int>* new_node = new Node<int>;

    if (position == 0) {
        if (count == 0) new_node->back = 0;
        new_node->next = 0;
        // following = current;
    }
    else {
        set_position(position - 1);
        new_node->back = current;
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;
    current_position = position;
    count++;
    return success;
}

Error_code List<double>::insert(int position, const double& x)
{
    if (count > 10) return overflow;
    if (position < 0) return underflow;
    if (position > count) return overflow;

    Node<double>* new_node = new Node<double>;

    if (position == 0) {
        if (count == 0) new_node->back = 0;
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
        new_node->back = current;
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;
    current_position = position;
    count++;
    return success;
}

Error_code List<char>::insert(int position, const char& x)
{
    if (count > 10) return overflow;
    if (position < 0) return underflow;
    if (position > count) return overflow;

    Node<char>* new_node = new Node<char>;

    if (position == 0) {
        if (count == 0) new_node->back = 0;
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
        new_node->back = current;
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;
    current_position = position;
    count++;
    return success;
}

Error_code List<string>::insert(int position, const string& x)
{
    if (count > 10) return overflow;
    if (position < 0) return underflow;
    if (position > count) return overflow;

    Node<string>* new_node = new Node<string>;

    if (position == 0) {
        if (count == 0) new_node->back = 0;
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
        new_node->back = current;
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;
    current_position = position;
    count++;
    return success;
}

