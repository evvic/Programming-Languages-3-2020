#ifndef QUEUE_CHAIN_INCLUDED
#define QUEUE_CHAIN_INCLUDED

#include <iostream>

//queue_chain<datatype> name

template <class flux>
class queue_chain
{
private:
	struct node {
		node* previous;
		flux data;
	};

	node* head;
	node* tail;
	int count = 0;

public:
	queue_chain() { head = tail = NULL;	} //constructor

	//copy constructor
	queue_chain(const queue_chain<flux> &f) 
	{
		node* temp = new node;
		temp = f.head;

		for (int tcount = f.count; tcount > 0; tcount--) {
			push(temp->data);
			temp = temp->previous;
		}

		this->count = f.count;
	}

	~queue_chain() { while (count-- > 0) pop(); } //deletes node chain & decrements count to 0

	//pops head off, moves to previous node
	bool pop() 
	{
		if (count <= 0)  return false;
		else {
			node* temp = head;
			head = head->previous;
			delete temp;
			count--;
			return true;
		}
	} 

	//pushes data onto queue tail
	void push(flux d) 
	{
		node* temp = new node;
		temp->data = d;
	
		switch (count) {
		case 0:
			head = tail = temp;
			break;
		case 1:
			head->previous = temp;
			tail = temp;
			break;
		default:
			tail->previous = temp;
			tail = temp;
			break;
		}
		tail->previous = NULL;
				
		count++;
	}

	int size() { return count; }

	bool empty() { return (count == 0) ? true : false; }

	flux front() { return head->data; }
	
	queue_chain& operator = (const queue_chain<flux> &f) {
		while (--this->count > 0) pop(); //destructor
		this->count = 0;

		node* temp = f.head;

		for (int tcount = f.count; tcount > 0; tcount--) {
			push(temp->data);
			temp = temp->previous;
		}

		this->count = f.count;

		return* this;
	}
};

#endif