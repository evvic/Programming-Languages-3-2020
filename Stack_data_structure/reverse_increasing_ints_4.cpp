#include <stack>
#include <iostream>

using namespace std;

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

	cout << endl << endl;

	cout << "Reverse order..." << endl;
	while (!enlarge.empty()) {
		cout << enlarge.top() << " ";
		enlarge.pop();
	}
	cout << endl;
}