#include <iostream>
#include <string>
#include <ctime>

// Header
#include "BankAccounts.h"

using namespace std;

void Current::deposit(double amount) {
	if (amount <= 0) cout << "Invalid amount entered. You can only deposit amounts of positive integers." << endl;
	else {
		// Check if account is in overdraft
		if (overdraft > 0) {
			if (amount <= overdraft) {
				// If the deposit does not fully cover the overdraft
				overdraft -= amount;
			}
			else {
				// If the deposit exceeds the overdraft
				double remaining = amount - overdraft; // amount needed to pay overdraft
				overdraft = 0; // Overdraft is fully paid
				balance += remaining; // Add the remaining amount to balance
			}
		}
		else {
			// If not in overdraft, simply add to balance
			balance += amount;
		}
		history.push_back(Transaction("deposit", amount));
		toString();
	}
}

void Current::withdraw(double amount) {
	// Check if amount to be withdrawn is positive
	if (amount <= 0) cout << "Invalid amount entered. You can only withdraw amounts of positive integers." << endl;
	else {
		if (amount <= balance) {
			// Sufficient balance in the account to cover the withdrawal
			balance -= amount;
			history.push_back(Transaction("withdraw", amount));
			toString();
		}
		else {
			// Withdrawal requires overdraft but does not exceed the overdraft limit
			if (amount <= ((500 - overdraft) + balance)) {
				double remaining = amount - balance; // // Calculate the amount needed from overdraft
				balance = 0; // Deplete balance
				overdraft += remaining; // Add the rest to overdraft
				history.push_back(Transaction("withdraw", amount));
				toString();
			}
			else {
				cout << "Insufficient balance!" << endl;
			}
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

bool Current::operator-(double amount) {
	if (amount <= balance) {
		// Sufficient balance in the account to cover the withdrawal
		balance -= amount;
		return true;
	}
	else {
		// Withdrawal requires overdraft but does not exceed the overdraft limit
		if (amount <= ((500 - overdraft) + balance)) {
			double remaining = amount - balance; // // Calculate the amount needed from overdraft
			balance = 0; // Deplete balance
			overdraft += remaining; // Add the rest to overdraft
			return true;
		}
		// Insufficient Funds
		return false;
	}
}

Account& Current::operator+(double amount) {
	// Check if account is in overdraft
	if (overdraft > 0) {
		if (amount <= overdraft) {
			// If the deposit does not fully cover the overdraft
			overdraft -= amount; // Add full amount to overdraft
		}
		else {
			// If the deposit exceeds the overdraft
			double remaining = amount - overdraft; // amount needed to pay overdraft
			overdraft = 0; // Overdraft is fully paid
			balance += remaining; // Add the remaining amount to balance
		}
	}
	else {
		// If not in overdraft, simply add to balance
		balance += amount;
	}

	return *this;
}