#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Struct to represent a transaction
struct Transaction {
	string desc; // Nature of transaction
	string date; // date, e.g. "2025-01-01, 00:00"
	double value; //
	void toString() {
		std::cout << desc << ": " << char(156)  << value << " on " << date << endl;
	}
};