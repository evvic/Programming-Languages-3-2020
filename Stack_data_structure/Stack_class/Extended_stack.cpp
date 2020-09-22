#include "Extended_stack.h"

#include <system_error>
#include <iostream>

Extended_stack::Extended_stack() { count = 0; }

Error_code Extended_stack::push(const Stack_entry &item) {
	Error_code outcome = success;
	if (count >= maxstack) {
		outcome = overflow;
	}
	else {
		entry[count++] = item;
	}
	return outcome;
}

Error_code Extended_stack::pop() {
	Error_code outcome = success;
	if (count == 0) {
		outcome = underflow;
	}
	else --count;
	return outcome;		
}

Error_code Extended_stack::top(Stack_entry& item) const {
	Error_code outcome = success;
	if (count == 0) {
		outcome = underflow;
	}
	else {
		item = entry[count - 1];
	}
	return outcome;
}

bool Extended_stack::empty() const { return (count <= 0) ? true : false; }

void Extended_stack::clear() { memset(entry, 0, sizeof entry); count = 0; } //clearing all chars in entry

bool Extended_stack::full() const { return (count >= maxstack) ? true : false; } 

int Extended_stack::size() const { return count; }

