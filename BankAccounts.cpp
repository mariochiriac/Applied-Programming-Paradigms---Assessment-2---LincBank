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

void Account::withdraw(double amount) {
	if (amount < balance) {
		balance -= amount;
		history.push_back(Transaction("withdraw", amount));
	}
	else cout << "Insufficient Balance! Current Balance:" << balance << endl;
}

// Outputs account details
void Account::toString() {
	cout << "Account | Balance: " << char(156) << balance << endl;
	for (auto i : history) {
		// Output all transactions
		i.toString();
	}
}

void Current::deposit(double amount) {
	// Check if account is in overdraft
	if (overdraft > 0) { 
		if (amount <= overdraft) {
			// If the deposit does not fully cover the overdraft
			overdraft -= amount;
			history.push_back(Transaction("deposit", amount));
		} 
		else {
			// If the deposit exceeds the overdraft
			double remaining = amount - overdraft; // amount needed to pay overdraft
			overdraft = 0; // Overdraft is fully paid
			balance += remaining; // Add the remaining amount to balance
			history.push_back(Transaction("deposit", amount));
		}
	} 
	else {
		// If not in overdraft, simply add to balance
		balance += amount;
		history.push_back(Transaction("deposit", amount));
	}
}

void Current::withdraw(double amount) {
	if (amount <= balance) {
		// Sufficient balance in the account to cover the withdrawal
		balance -= amount;
		history.push_back(Transaction("withdraw", amount));
	}
	else {
		// Withdrawal requires overdraft but does not exceed the overdraft limit
		if (amount <= ((500 - overdraft) + balance)) {
			double remaining = amount - balance; // // Calculate the amount needed from overdraft
			balance = 0; // Deplete balance
			overdraft += remaining; // Add the rest to overdraft
			history.push_back(Transaction("withdraw", amount));
		}
		else {
			cout << "Insufficient balance!" << endl;
		}
	}
}

void Current::toString() {
	if (overdraft > 0) {
		cout << "Current Account | Balance: -" << char(156) << overdraft << endl;
	}
	else cout << "Current Account | Balance: " << char(156) << balance << endl;
	for (auto i : history) {
		i.toString();
	}
}

void Savings::deposit(double amount) {
	balance += amount;
	history.push_back(Transaction("deposit", amount)); // Adds transaction to list
}

void Savings::withdraw(double amount) {
	if (amount < balance) {
		balance -= amount;
		history.push_back(Transaction("withdraw", amount));
	}
	else cout << "Insufficient Balance! Current Balance:" << balance << endl;
}

void Savings::toString() {
	cout << (isa ? "ISA" : "Savings" ) << " | Balance: " << char(156) << balance << endl;
	for (auto i : history) {
		// Output all transactions
		i.toString();
	}
}

void Savings::computeInterest(int years) {
	const int n = 12;
	double A = balance * pow(1 + (interestRate / n), n * years);
	cout << "Projected Balance: " << char(156) << A << endl;
}

// Operator Overload for Transfer (Withdrawal)
Account& Account::operator-(double amount) {
	if (balance >= amount) {
		balance -= amount;
		cout << "Transfer successful!" << endl;
	} 
	else {
		cout << "Insufficient funds for transfer!" << endl;
	}
	return *this;
}

// Operator Overload for Deposit
Account& Account::operator+(double amount) {
	balance += amount;
	return *this;
}