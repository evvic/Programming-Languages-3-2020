#include "List.h"
#include "Utility.h"
#include <iostream>

using namespace std;

Node<char>::Node() {
    entry = NULL;
    next = NULL;
}

Node<string>::Node() {
    entry = "";
    next = NULL;
}

template <class Node_entry>
Node<Node_entry>::Node() {
    entry = 0;
    next = NULL;
}

template <class List_entry>
bool List<List_entry>::clear() {
    List_entry buffer;
    while (remove(0, buffer) == success);
    return true;
}

template <class List_entry>
int List<List_entry>::size() {
    return count;
}

template <class List_entry>
bool List<List_entry>::empty() {
    return (count == 0) ? true : false;
}

template <class List_entry>
bool List<List_entry>::full() {
    return (MAXSIZE == count) ? true : false;
}

template <class List_entry>
void List<List_entry>::set_position(int position) const {
    if (current_position <= position)
        for (; current_position != position; current_position++)
            current = current->next;
    else {
        current = head;
        for (current_position = 1; current_position <= position; current_position++) {
            current = current->next;
        }
    }
};

template <class List_entry>
Error_code List<List_entry>::traverse() {
    if (count < 1) return underflow;
    //traverse can only go forward because this is singly-linked

    current = head;

    for (current_position = 0; current->next != NULL; current_position++) {
        std::cout << current->entry << ' ';
        current = current->next;
    }

    return success;
}

template <class List_entry>
Error_code List<List_entry>::interchange(int pos1, int pos2) {
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

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry& x) {
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
        for (current_position = 0; current_position < position - 1; current_position++) {
            temp = temp->next;
        }

        Node<List_entry>* nearhead = new Node<List_entry>;
        nearhead = temp;
        temp = temp->next;

        nearhead->next = temp->next;
    }

    x = temp->entry;

    current = temp->next;

    delete temp;
    count--;

    return success;
}



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
Error_code List<List_entry>::retrieve(int pos, List_entry& x) {
    if (x == 0) {
        x = head->entry;
        return success;
    }
    else {
        Node<List_entry>* temp = new Node<List_entry>;
        temp = head;

        for (int i = 0; i < pos;  i++) {
            temp = temp->next;
        }

        x = temp->entry;
        //delete temp;
        return success;
    }
    return fail;
}

template <class List_entry>
Error_code List<List_entry>::replace(int pos, const List_entry& x) {
    if (pos > count) return overflow;
    if (pos < 0) return underflow;
    if (count == 0) return underflow;

    Node<List_entry>* temp = new Node<List_entry>;
    temp = head;

    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    temp->entry = x;

    return success;

}



template <class List_entry>
Error_code List<List_entry>::median(List_entry& x) {
    Node<List_entry>* temp = new Node<List_entry>;
    temp = head;

    if (count == 0) return underflow;
    if (count == 1) {
        x = temp->entry;
        return success;
    }

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

// TEMPLATE DID NOT WORK SO MULTIPLE COPIES OF ~INSERT~ WITH DIFFERENT DATA TYPES
Error_code List<bool>::insert(int position, const bool& x) {
    if (count > MAXSIZE) return overflow;
    if (position < 0) return underflow;
    if (position > count || position > MAXSIZE) return overflow;

    Node<bool>* new_node = new Node<bool>;

    if (position == 0) {
        if (count == 0) {
            new_node->entry = x;
        }
        new_node->next = 0;
        // following = current;
        head = new_node;
    }
    else {
        set_position(position - 1);
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;

    current_position = position;
    count++;
    return success;
}

Error_code List<int>::insert(int position, const int& x)
{
    if (count > MAXSIZE) return overflow;
    if (position < 0) return underflow;
    if (position > count || position > MAXSIZE) return overflow;
    
    Node<int>* new_node = new Node<int>;

    if (position == 0) {
        if (count == 0) {
            new_node->entry = x;
        }
        new_node->next = 0;
        // following = current;
        head = new_node;
    }
    else {
        set_position(position - 1);
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
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
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
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
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
        new_node->next = 0;
        // following = current;

    }
    else {
        set_position(position - 1);
        new_node->next = current->next;
    }

    new_node->entry = x;

    current = new_node;
    current_position = position;
    count++;
    return success;
}

