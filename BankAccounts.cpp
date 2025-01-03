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
	toString();
}

void Account::withdraw(double amount) {
	if (amount < balance) {
		balance -= amount;
		history.push_back(Transaction("withdraw", amount));
		toString();
	}
	else cout << "Insufficient Balance! Current Balance: " << char(156) << balance << endl;
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

void Current::withdraw(double amount) {
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
	toString();
}

void Savings::withdraw(double amount) {
	if (amount < balance) {
		balance -= amount;
		history.push_back(Transaction("withdraw", amount));
		toString();
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
bool Account::operator-(double amount) {
	if (balance >= amount) {
		balance -= amount;
		cout << "Transfer successful!" << endl;
		return true;
	} 
	else {
		cout << "Insufficient funds for transfer!" << endl;
		return false;
	}
}

// Operator Overload for Deposit
Account& Account::operator+(double amount) {
	balance += amount;
	return *this;
}

// Transfer method
void Account::transfer(vector<Account*> accounts, int srcIndex, int destIndex, double amount) {
	// Pointers to accounts within the vector
	Account* recipient = accounts[destIndex - 1];

	if (*this - amount) {
		// If the amount is withdrawn from the account, it will proceed with the deposit in the recipient's account
		this->history.push_back(Transaction("transfer to account " + to_string(destIndex), amount));
		*recipient + amount;
		recipient->history.push_back(Transaction("transfer from account " + to_string(srcIndex), amount));
		this->toString();
		recipient->toString();
	}
	else cout << "Insufficient funds. Could not complete transfer." << endl;;
}

// Overload Operator to ensure functionality for overdraft
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