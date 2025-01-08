#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <iomanip>

// Header File
#include "Transaction.h"

using namespace std;

// Method that outputs to console details of transaction
void Transaction::toString() {
	// Display positive and negative values accurately
	if (value >= 0) { // if value is positive
		cout << "-- " << desc << ": " << char(156)
			<< fixed << setprecision(2) << value << " on " << timestamp;
	}
	else { // if value is negative
		cout << "-- " << desc << ": -" << char(156) // place - sign before £ sign
			<< fixed << setprecision(2) << abs(value) << " on " << timestamp; // abs() -> converts to positive value
	}
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