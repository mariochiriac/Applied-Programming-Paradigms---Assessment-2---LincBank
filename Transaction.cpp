#include <iostream>
#include <ctime>

// Header File
#include "Transaction.h"

// Method that outputs to console details of transaction
void Transaction::toString() {
	std::cout << "-- " << desc << ": " << char(156) << value << " on " << timestamp << endl;
}

// Method, gets current time when transaction struct is called, adds it to timestamp member
string Transaction::getTime() {
	// Get current time
	time_t timestamp = time(nullptr);
	char buf[80]; // Buffer to store the formatted time

	// Use ctime_s for safer time formatting
	ctime_s(buf, sizeof(buf), &timestamp);
	return string(buf);
}