#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Struct to represent a transaction
class Transaction {
private:
	string desc; // Nature of transaction
	string timestamp; // date, e.g. "2025-01-01, 00:00"
	double value; // amount
public:
	// Default Constructor
	Transaction() {
		desc = "invalid";
		timestamp = getTime();
		value = 0;
	}

	// Constructor
	Transaction(const string& description, double val) : desc(description), value(val) { 
		timestamp = getTime();
	}

	void toString();
	string getTime();

};