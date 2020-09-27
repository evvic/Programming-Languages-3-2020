#include <iostream>
#include <stack>

/*
This program asks the user for a number
Then the program finds the prime divisors
i.e. 2100 = 7 5 5 3 2 2 

...Don't input a number larger than an int can hold
*/

using namespace std;

template <class swag> //a
bool full(stack<swag>& s) { return (!s.empty()) ? true : false; }

template <class swag> //c
void clear(stack<swag>& s) { while (!s.empty()) s.pop() ; }

template <class swag> //d
int size(stack<swag>& s) { return s.size(); }


stack<int> returnPrimes(int num) {
	stack<int> record;

	int primes[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	for (int i = 0; num != 1; i++) {
		while (num % primes[i] == 0) {
			num = num / primes[i];
			record.push(primes[i]);
		}
	}

	return record;
}

int main() {
	stack<int> bro;
	int duh;

	cout << "Enter number: ";
	cin >> duh;

	bro = returnPrimes(duh);

	cout << endl << "It's prime divisors are: ";
	while (!bro.empty()) {
		cout << bro.top() << ' ';
		bro.pop();
	}
}