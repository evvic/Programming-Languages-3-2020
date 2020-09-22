#ifndef EXTENDED_STACK_H_INCLUDED
#define EXTENDED_STACK_H_INCLUDED

#include <iostream>

enum Error_code {
    success, fail, utility_range_error, underflow, overflow, fatal,
    not_present, duplicate_error, entry_inserted, entry_found,
    internal_error
};
typedef char Stack_entry;

const int maxstack = 100; //for testing reasons this is low

class Extended_stack {
public:
    Extended_stack();
    Error_code pop();
    Error_code push(const Stack_entry& item);
    Error_code top(Stack_entry& item) const;
    bool empty() const;
    void clear(); // Reset the stack to be empty.
    bool full() const; // If the stack is full, 
                         // return true; else return false.
    int size() const; // Return the number of entries 
                       // in the stack.

private:
    int count;
    Stack_entry entry[maxstack];
};

#endif