#include <iostream>
#include <string>
#include <ctime>

// Header
#include "BankAccounts.h"

using namespace std;

// Method to add deposit
void Account::deposit(double amount) {
	// Check if amount to be deposited is positive
	if (amount <= 0) cout << "Invalid amount entered. You can only deposit amounts of positive integers." << endl;
	else {
		balance += amount;
		history.push_back(Transaction("deposit", amount)); // Adds transaction to list
		toString();
	}
}

void Account::withdraw(double amount) {
	// Check if amount to be withdrawn is positive
	if (amount <= 0) cout << "Invalid amount entered. You can only withdraw amounts of positive integers." << endl;
	else {
		if (amount <= balance) {
			balance -= amount;
			history.push_back(Transaction("withdraw", amount));
			toString();
		}
		else cout << "Insufficient Balance! Current Balance: " << char(156) << balance << endl;
	}
}

// Outputs account details
void Account::toString() {
	cout << "Account | Balance: " << char(156) << balance << endl;
	for (auto i : history) {
		// Output all transactions
		i.toString();
	}
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
	Account* recipient = accounts[destIndex];

	if (*this - amount) {
		// If the amount is withdrawn from the account, it will proceed with the deposit in the recipient's account
		this->history.push_back(Transaction("transfer to account " + to_string(destIndex + 1), -amount));
		*recipient + amount;
		recipient->history.push_back(Transaction("transfer from account " + to_string(srcIndex + 1), amount));
		this->toString();
		recipient->toString();
	}
	else cout << "Insufficient funds. Could not complete transfer." << endl;;
}
