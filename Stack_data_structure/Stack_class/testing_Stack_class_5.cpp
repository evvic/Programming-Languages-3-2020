//#include <stack>
#include <iostream>

#include "Extended_stack.h"

using namespace std;

int main()
{
	int n;
	char item;
	Extended_stack letters; // declares and initializes a stack of numbers
	cout << " Type in an integer (n) followed by (n) characters."
		<< endl
		<< " The characters will be printed in reverse order."
		<< endl
		<< "number of items: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "> ";
		cin >> item;
		letters.push(item);
	}
	cout << endl << endl;

	
	//testing member class functions
	cout << "Is stack empty: ";
	if (letters.empty()) { cout << "true" << endl; }
	else { cout << "false" << endl; }
	cout << "Is stack full at max stack (" << maxstack << "): ";
	if (letters.full()) { cout << "true" << endl; }
	else { cout << "false" << endl; }
	cout << "Size of stack: " << letters.size() << endl;
	cout << "Clearing stack..." << endl;
	letters.clear();
	cout << endl << "NOW" << endl;
	cout << "Is stack empty: ";
	if (letters.empty()) { cout << "true" << endl; }
	else { cout << "false" << endl; }
	cout << "Is stack full at max stack (" << maxstack << "): ";
	if (letters.full()) { cout << "true" << endl; }
	else { cout << "false" << endl; }
	cout << "Size of stack: " << letters.size() << endl << endl;


	while (!letters.empty()) {
		cout << letters.top(item) << " ";
		letters.pop();
	}
	cout << endl;
}