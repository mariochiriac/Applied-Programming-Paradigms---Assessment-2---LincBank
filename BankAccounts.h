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
	virtual ~Account() {
		cout << "Account deleted." << endl; // Check if memory is freed 
	}

	virtual void deposit(double amount);
	virtual void withdraw(double amount);
	virtual void toString();
	virtual void transfer(vector<Account*> accounts, int srcIndex, int destIndex, double amount);

	// Operator Overloading for transfers
	virtual bool operator-(double amount); // Operator that will take money out of an account
	virtual Account& operator+(double amount); // Operator that will introduce money into an account
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

	// Overload Operator to ensure functionality for overdraft
	virtual bool operator-(double amount);
	virtual Account& operator+(double amount);
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
	Savings(double initialBalance, bool isISA = false) : Account(initialBalance), isa(isISA), interestRate(0.0) { // Default balance to 0 initially
		interestRate = isISA ? 0.0115 : 0.0085;
		cout << (isa ? "ISA" : "Savings") << " created!" << endl;
	}

	void deposit(double amount);
	void withdraw(double amount);
	void toString();
	void computeInterest(int years);
};