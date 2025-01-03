/* ------------------------------------------------------
CMP2811: Applied Programming Paradigms
Driver program for "LincBank" Assessment Item 2
Semester A 2024

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <ctime>

// Headers
#include "BankAccounts.h"

using namespace std;

// Declare Methods
void view_accounts(vector<Account*> accounts);

int main()
{
	try {
		vector <string> parameters;
		string userCommand;
		// you may also want to store a collection of opened accounts here

		vector<Account*> accounts; // accounts created will be stored in vector

		cout << "~~~ Welcome to LincBank! ~~~" << endl;
		cout << "open type initial_deposit: open a current (1), savings (2) or ISA (3) account" <<
			"\nview[index]: view balance and recent transactions" <<
			"\nwithdraw sum : withdraw funds from most recently viewed account"
			"\ndeposit sum : deposit funds into most recently viewed account"
			"\ntransfer src dest sum : transfer funds between accounts"
			"\nproject years : project balance forward in time"
			"\nexit : close this application"
			"\noptions : view these options again" << endl;

		while (userCommand != "exit")
		{
			parameters.clear(); // clear ready for next command
			cout << endl << ">>> ";

			getline(cin, userCommand);
			char* cstr = new char[userCommand.length() + 1];
			strcpy(cstr, userCommand.c_str());

			char* token;
			token = strtok(cstr, " ");

			while (token != NULL)
			{
				parameters.push_back(token);
				token = strtok(NULL, " ");
			}

			// Define all commands as per the brief
			string command = parameters[0];

			if (command.compare("options") == 0)
			{
				// display the various commands to the user
				cout << "open type initial_deposit: open a current (1), savings (2) or ISA (3) account" <<
					"\nview[index]: view balance and recent transactions" <<
					"\nwithdraw sum : withdraw funds from most recently viewed account"
					"\ndeposit sum : deposit funds into most recently viewed account"
					"\ntransfer src dest sum : transfer funds between accounts"
					"\nproject years : project balance forward in time"
					"\nexit : close this application"
					"\noptions : view these options again" << endl;
			}
			else if (command.compare("open") == 0)
			{
				// allow a user to open an account
				// e.g., Account* a = new Savings(...);
				// 
				// Ensure that the user has provided the correct parameters
				if (parameters.size() < 3) {
					cout << "Invalid input. Usage: open <account_type> <initial_deposit>" << endl;
					continue;  // Skip to the next command
				}

				// Extract account type (1 for Current, 2 for Savings, 3 for ISA) and initial deposit
				int accountType = stoi(parameters[1]);  // Convert the account type to an integer
				double initialDeposit = stod(parameters[2]);  // Convert the initial deposit to a double

				// Based on the account type, create the appropriate account
				if (accountType == 1) {
					// Open a Current account and add it to the accounts vector
					accounts.push_back(new Current(initialDeposit));
				}
				else if (accountType == 2) {
					accounts.push_back(new Savings(initialDeposit, 0));
				}
				else if (accountType == 3) {
					if (initialDeposit < 1000) {
						// If initial deposit is smaller than 1000, output an error to console
						cout << "ISA initial balance must be >= " << char(156) << "1000." << endl;
					}
					else accounts.push_back(new Savings(initialDeposit, 1));
				}
				else {
					// Invalid account type
					cout << "Invalid account type. Please choose 1 (Current), 2 (Savings), or 3 (ISA)." << endl;
				}

			}
			else if (command.compare("view") == 0)
			{
				// display an account according to an index (starting from 1)
				// alternatively, display all accounts if no index is provided
				if (parameters.size() > 1) {
					// Take parameter as account index
					int accountIndex = stoi(parameters[1]);

					// Check if account exists
					if (accountIndex < 0 || accountIndex > accounts.size()) {
						cout << "The selected account does not exist. Please select a valid account." << endl;
					} 
					else accounts[accountIndex - 1]->toString();
				}
				else view_accounts(accounts);
			}
			else if (command.compare("withdraw") == 0)
			{
				// allow user to withdraw funds from an account
				// Input Check
				if (parameters.size() < 3) {
					cout << "Invalid input. Usage: withdraw <account_index> <withdraw_amount>" << endl;
					continue;  // Skip to the next command
				}

				// allow user to deposit funds into an account
				int accountIndex = stoi(parameters[1]);  // Convert the account chosen to an integer
				double amount = stod(parameters[2]);  // Convert the deposit to a double

				if (accountIndex < 0 || accountIndex > accounts.size()) {
					cout << "The selected account does not exist. Please select a valid account." << endl;
				}
				else {
					accounts[accountIndex - 1]->withdraw(amount);
				}
			}
			else if (command.compare("deposit") == 0)
			{
				// Input Check
				if (parameters.size() < 3) {
					cout << "Invalid input. Usage: deposit <account_index> <deposit_amount>" << endl;
					continue;  // Skip to the next command
				}

				// allow user to deposit funds into an account
				int accountIndex = stoi(parameters[1]);  // Convert the account chosen to an integer
				double amount = stod(parameters[2]);  // Convert the deposit to a double

				if (accountIndex < 0 || accountIndex > accounts.size()) {
					cout << "The selected account does not exist. Please select a valid account." << endl;
				}
				else {
					accounts[accountIndex - 1]->deposit(amount);
				}
			}
			else if (command.compare("transfer") == 0)
			{
				// allow user to transfer funds between accounts
				// i.e., a withdrawal followed by a deposit!
				// Input Check
				if (parameters.size() < 4) {
					cout << "Invalid input. Usage: transfer <source_index> <destination_index> <amount>" << endl;
					continue;  // Skip to the next command
				}


				// allow user to deposit funds into an account
				int sourceIndex = stoi(parameters[1]);  // Convert the account chosen to an integer
				int destinationIndex = stoi(parameters[2]);  // Convert the account chosen to an integer
				double amount = stod(parameters[3]);  // Convert the deposit to a double

				if (sourceIndex && destinationIndex < 0 || sourceIndex && destinationIndex > accounts.size()) {
					cout << "The selected account does not exist. Please select a valid account." << endl;
					continue;
				}
				else if (sourceIndex == destinationIndex) {
					cout << "Cannot transfer money to the same account. Please enter a valid destination account." << endl;
					continue;
				}

				accounts[sourceIndex - 1]->transfer(accounts, sourceIndex, destinationIndex, amount);
			}
			else if (command.compare("project") == 0)
			{
				// compute compound interest t years into the future
			}
			//else if (command.compare("search"))
			//{
			//	allow users to search their account history for a transaction
			//  (this is a stretch task)
			//}

		}
		for (auto& account : accounts) {
			delete account;
		}
		cout << "Press ENTER to quit...";
		return getchar();
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}

void view_accounts(vector<Account*> accounts) {
	for (auto& i : accounts) {
		i->toString();
	}
}

// Implementation of functions

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file