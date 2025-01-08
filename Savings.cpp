#include <iostream>
#include <string>
#include <ctime>

// Header
#include "BankAccounts.h"

using namespace std;

void Savings::deposit(double amount) {
	// Check if amount to be deposited is positive
	if (amount <= 0) cout << "Invalid amount entered. You can only deposit amounts of positive integers." << endl;
	else {
		balance += amount;
		history.push_back(Transaction("deposit", amount)); // Adds transaction to list
		toString();
	}
}

void Savings::withdraw(double amount) {
	// Check if amount to be withdrawn is positive
	if (amount <= 0) cout << "Invalid amount entered. You can only withdraw amounts of positive integers." << endl;
	else {
		if (amount < balance) {
			balance -= amount;
			history.push_back(Transaction("withdraw", amount));
			toString();
		}
		else cout << "Insufficient Balance! Current Balance:" << balance << endl;
	}
}

void Savings::toString() {
	cout << (isa ? "ISA" : "Savings") << " | Balance: " << char(156) << balance << endl;
	for (auto i : history) {
		// Output all transactions
		i.toString();
	}
}

void Savings::computeInterest(int years) {
	const int n = 12;
	float A = balance * pow(1 + (interestRate / n), n * years);

	cout << "Projected Balance: " << char(156) << A << endl;
}