#include <stack>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	char item;
	stack<char> letters; // declares and initializes a stack of numbers

	cout << "Enter text to be reversed." << endl << "> ";
	getline(cin, s);
	cin.clear(); //just in case getline() does some weird stuff

	for (int i = 0; i < s.length(); i++) {
		letters.push(s[i]);
	}

	cout << endl << endl;
	while (!letters.empty()) {
		cout << letters.top();
		letters.pop();
	}
	cout << endl;
}