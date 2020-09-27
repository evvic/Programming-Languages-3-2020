#include <iostream>
//#include "stack.h"
#include <stack>

using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};


/*
template <class swag>  //compiler can tell what datatype to use
Error_code copy_stack(stack<swag>& dest, stack<swag>& source) {
	dest = source;
	return success;
}
*/

template <class swag>  //compiler can tell what datatype to use
Error_code copy_stack(stack<swag>& dest, stack<swag>& source) {
	stack<swag> temp;

	while (!source.empty()) { 
		temp.push(source.top());
		source.pop();
	}
	
	while (!temp.empty()) {
		dest.push(temp.top());
		source.push(temp.top());
		temp.pop();
	}

	return success;
}



int main()
{
	int item;
	stack<int> enlarge; // declares and initializes a stack of numbers

	cout << " Type an integer. Continue adding numbers that are increasing."
		<< endl
		<< " To stop, enter an integer lower than the previous."
		<< endl
		<< " The numbers will be printed in reverse order."
		<< endl;

	cout << "> ";
	cin >> item;

	do {
		enlarge.push(item);
		cout << "> ";
		cin >> item;
	} while (item > enlarge.top());

	stack<int> paste;

	//        (dest, source)
	copy_stack(paste, enlarge); //calling template class but compiler can tell which datatype to use

	cout << endl << endl;

	cout << "Reverse order..." << endl;
	while (!enlarge.empty()) {
		cout << enlarge.top() << " ";
		enlarge.pop();
	}
	cout << endl;

	cout << "Reverse order... [WITH DESTINATION STACK]" << endl;
	while (!paste.empty()) {
		cout << paste.top() << " ";
		paste.pop();
	}
	cout << endl;
}
