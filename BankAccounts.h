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
		history.push_back(Transaction("initial deposit", initialBalance));
	}

	// Deconstructor
	virtual ~Account() { }

	virtual void deposit(double amount);
	virtual void withdraw(double amount);
	virtual void toString();

	// Operator Overloading for transfers
	Account& operator-(double amount);
	Account& operator+(double amount);
};

class Current : public Account {
private:
	double overdraft;
public:
	Current(double initialBalance = 0) : Account(initialBalance) {
		cout << "Current account created!" << endl;
		overdraft = 0;
	}

	void deposit(double amount);
	void withdraw(double amount);
	void toString();
};

class InterestEarning {
public:
	virtual void computeInterest(int years) = 0;
};

class Savings : public Account, public InterestEarning {
private:
	double interestRate;
	bool isa;
public:
	Savings(double initialBalance, bool isISA = false) : Account(0), isa(isISA), interestRate(0.0) { // Default balance to 0 initially
		if (isa && initialBalance < 1000) {
			cout << "ISA initial balance must be >= " << char(156) << "1000." << endl;
			return; // Exit constructor if ISA requirements aren't met
		}

		balance = initialBalance; // Set balance if valid
		interestRate = isISA ? 0.0115 : 0.0085;
		cout << (isa ? "ISA" : "Savings") << " created!" << endl;

		// Add initial deposit transaction
		history.push_back(Transaction("initial deposit", balance));
	}

	void deposit(double amount);
	void withdraw(double amount);
	void toString();
	void computeInterest(int years);
};