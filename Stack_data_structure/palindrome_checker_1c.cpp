#include <stack>
#include <iostream>

using namespace std;

int main()
/* Uses: The STL class stack and its methods */
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

	//SOLVING FOR  IF  PALINDROME

	stack<char> letters2;
	int i, mid = letters.size() / 2;
	bool odd, palindrome = false;

	odd = (letters.size() % 2 == 1) ? true : false; //set length beong odd to true or fasle

	for (int i = 0; i < mid; i++) {
		letters2.push(letters.top());
		letters.pop();
	}

	if (odd) { letters.pop(); } //remove middle letter


	for (int j = 0; j <= letters.size(); j++) {
		if (letters.top() != letters2.top()) {
			palindrome = false;
			break;
		}
		else { palindrome = true; }

		letters.pop();
		letters2.pop();
	}

	if (palindrome) {
		cout << "\nIS A PALINDROME!";
	}
	else {
		cout << "\nnot a palindrome.";
	}
}