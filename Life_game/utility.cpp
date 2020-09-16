#include <iostream>
#include <string>

using namespace std;


//not really a utiliy but temp here
bool checkFax(char c) {
	if (c == 'X' || c == ' ') {
		return true;
	}
	else {
		cout << "you don fucked up";
		return false;
	}
}

string spaceToScore(string formerRow) {
	for (int i = 0; i < formerRow.size(); i++) {
		if (formerRow.at(i) == ' ') {
			formerRow.at(i) = '_';
		}
	}
	return formerRow;
}

bool user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
			cout << " (y,n)? " << flush;

		else
			cout << "Respond with either y or n: " << flush;

		do { //  Ignore white space.
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}
