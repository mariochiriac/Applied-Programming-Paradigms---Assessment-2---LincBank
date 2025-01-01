#include <iostream>
#include <vector>
#include <string>

// Headers
#include "Transaction.h"

using namespace std;

// Abstract Class, Account
class Account {
// Protected Members
protected:
	double balance; // Balance of account
	vector<Transaction> history; // Vector holding transaction history
public:
	// Constructor
	Account(double initialBalance = 0) : balance(initialBalance) {
		cout << "Account has been created." << endl;
		history.push_back(Transaction("initial deposit", initialBalance));
	}

	// Deconstructor
	virtual ~Account()
	{

	}

	virtual void deposit(double amount);
	virtual void withdraw(double amount);
	virtual void toString();
	//virtual void withdraw(double amount);
};

class Current : public Account {
private:
	double overdraft;
public:
	Current(double initialBalance = 0) : Account(initialBalance) {
		cout << "Current account created!" << endl;
		overdraft = 500;
	}

	void deposit(double amount);
	void withdraw(double amount);
	void toString();
};