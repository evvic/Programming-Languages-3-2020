#ifndef STACK_CHAIN_INCLUDED
#define STACK_CHAIN_INCLUDED

#include <iostream>

//stack_chain<datatype> name

template <class flux>
class stack_chain
{
private:
	struct node {
		node* previous;
		flux data;
	};
	node* head;
	int count = 0;

public:
	stack_chain() { head = NULL; } //constructor

	~stack_chain() {
		//delete head; //& all linked nodes
	} //destructor

	bool pop() {
		if (count <= 0)  return false;
		else {
			node* temp = head;
			head = head->previous;
			delete temp;
			count--;
			return true;
		}
	} //pops head off, moves to previous node

	void push(flux d) {
		node* temp = new node;
		temp->data = d;
		temp->previous = head;
		head = temp;
		count++;
	} //pushes data onto stack head

	int size() { return count; }

	bool empty() { return (count == 0) ? true : false; }

	flux top() { return head->data; }
};

#endif
