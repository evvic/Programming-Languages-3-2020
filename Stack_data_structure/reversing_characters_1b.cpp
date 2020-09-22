#include <stack>
#include <iostream>

using namespace std;

int main()
/* Pre: The user supplies an integer n and n decimal numbers.
Post: The numbers are printed in reverse order.
Uses: The STL class stack and its methods */
{
	int n;
	char item;
	stack<char> letters; // declares and initializes a stack of numbers
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
	while (!letters.empty()) {
		cout << letters.top() << " ";
		letters.pop();
	}
	cout << endl;
}