#include <iostream>
#include <string>
#include <ctime>

// Header
#include "BankAccounts.h"

using namespace std;

// Method to add deposit
void Account::deposit(double amount) {
	balance += amount;
	history.push_back(Transaction("deposit", amount)); // Adds transaction to list
}

// Outputs account details
void Account::toString() {
	cout << "--- Current Account ---" <<
		"\nBalance: " << balance << endl;
}