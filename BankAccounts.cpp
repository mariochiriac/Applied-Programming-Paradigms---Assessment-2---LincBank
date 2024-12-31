#include <iostream>
#include <string>
#include <ctime>

// Header
#include "BankAccounts.h"

using namespace std;

// Method to add deposit
void Account::deposit(double amount, const string&date) {
	balance += amount;
	history.push_back({ "deposit", date, amount });
	history[0].toString();
}

void Account::toString() {
	cout << "--- Current Account ---" <<
		"\nBalance: " << balance << endl;
}