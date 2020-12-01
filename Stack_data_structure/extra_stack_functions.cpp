#include <iostream>
#include <stack>

using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};

template <class swag> //a
bool full(stack<swag>& s) { return (!s.empty()) ? true : false; }

template <class swag> //b
Error_code pop_top(stack<swag> &s, swag &t) {
	t = s.top();
	s.pop();
	
	return success;
}

template <class swag> //c
void clear(stack<swag>& s) { while (!s.empty()) s.pop() ; }

template <class swag> //d
int size(stack<swag>& s) { return s.size(); }

template <class swag> //e
void delete_all(stack<swag>& s, swag x) {
	stack<swag> temp;

	while (!s.empty()) {
		if (s.top() != x) { temp.push(s.top()); }
		s.pop();
	}
	
	while(!temp.empty()) {
		s.push(temp.top());
		temp.pop();
	}
}

int main() {
	stack<char> bro;
	char duh;

	cout << "Enter 'Q' to stop adding chars." << endl;
	do {
		cout << "\t>";
		cin >> duh;
		bro.push(duh);
	} while (duh != 'Q');
	bro.pop(); //remove Q

	cout << "Enter a char to delete: ";
	cin >> duh;

	delete_all(bro, duh);

	cout << endl;
	while (!bro.empty()) { cout << bro.top() << ' '; bro.pop(); }
}
