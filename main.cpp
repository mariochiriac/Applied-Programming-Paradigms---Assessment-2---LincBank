/* ------------------------------------------------------
CMP2811: Applied Programming Paradigms
Driver program for "LincBank" Assessment Item 2
Semester A 2024

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!

TO DO:

1. Fix transfer, when invalid index is input the program crashed with vector out of subscript range
2. Implement search
3. TEST TEST TESTING TEST TEST TESTING!!

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
		Savings* isa_account = nullptr; // pointer to isa account
		Account* viewedAccount = nullptr; // pointer to viewed account

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
				int accountType = stoi(parameters[1]);  // Convert account type to integer
				double initialDeposit = stod(parameters[2]);  // Convert initial deposit to double

				if (initialDeposit < 100) {
					cout << "You have entered an invalid initial deposit value. Please enter a valid amount." << endl;
					continue;
				}

				// Based on the account type, create account selected
				switch (accountType) {
				case 1:
					accounts.push_back(new Current(initialDeposit));
					break;
				case 2:
					accounts.push_back(new Savings(initialDeposit, 0));
					break;
				case 3:
					if (isa_account == nullptr) {
						if (initialDeposit < 1000) {
							// If initial deposit is smaller than 1000, output an error to console
							cout << "ISA initial balance must be >= " << char(156) << "1000." << endl;
							break;
						}
						else {
							// If ISA account is sucessfully created, appoint a pointer to a new ISA, and append to vector
							isa_account = new Savings(initialDeposit, 1);
							accounts.push_back(isa_account);
							break;
						}
					}
					else {
						cout << "ISA account already exists." << endl;
						break;
					}
				default:
					cout << "Invalid account type. Please choose 1 (Current), 2 (Savings), or 3 (ISA)." << endl;
					break;
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
					else {
						accounts[accountIndex - 1]->toString();
						viewedAccount = accounts[accountIndex - 1]; // set as viewed account
					}
				}
				else view_accounts(accounts);
			}
			else if (command.compare("withdraw") == 0)
			{
				// allow user to withdraw funds from an account
				// check input
				if (parameters.size() < 2) {
					cout << "Invalid input. Usage: withdraw <sum> after viewing an account. Alternative usage: withdraw <account_index> <sum>." << endl;
					continue;
				}

				int accountIndex;  // Convert account chosen to integer
				double amount;  // Convert deposit to double
				int parametersSize = parameters.size();

				switch (parametersSize)
				{
				case 2: // Input is deposit <sum>
					// Check if account has been viewed
					amount = stod(parameters[1]); // set second parameter as the amount

					if (viewedAccount != nullptr) {
						viewedAccount->withdraw(amount);
					}
					else cout << "You have not viewed an account yet. Please use view <account_index>. Alternative usage: withdraw <account_index> <sum>." << endl;
					break;
				case 3: // Input is deposit <account_index> <sum>
					accountIndex = stoi(parameters[1]);
					amount = stod(parameters[2]);
					if (accountIndex <= 0 || accountIndex > accounts.size()) {
						cout << "The selected account does not exist. Please select a valid account." << endl;
					}
					else {
						accounts[accountIndex - 1]->withdraw(amount);
					}
					break;
				default:
					cout << "Invalid usage. Please use withdraw <sum>. Alternative usage: withdraw <account_index> <sum>." << endl;
					break;
				}
			}
			else if (command.compare("deposit") == 0)
			{
				// allow user to deposit funds into an account
				// Input Check
				if (parameters.size() < 2) {
					cout << "Invalid input. Usage: deposit <sum> after viewing an account. Alternative usage: deposit <account_index> <sum>." << endl;
					continue;
				}

				int accountIndex;  // Convert account chosen to integer
				double amount;  // Convert deposit to double
				int parametersSize = parameters.size();

				switch (parametersSize)
				{
				case 2: // Input is deposit <sum>
					// Check if account has been viewed
					amount = stod(parameters[1]); // set second parameter as the amount

					if (viewedAccount != nullptr) {
						viewedAccount->deposit(amount);
					}
					else cout << "You have not viewed an account yet. Please use view <account_index>. Alternative usage: deposit <account_index> <sum>." << endl;
					break;
				case 3: // Input is deposit <account_index> <sum>
					accountIndex = stoi(parameters[1]);
					amount = stod(parameters[2]);
					if (accountIndex <= 0 || accountIndex > accounts.size()) {
						cout << "The selected account does not exist. Please select a valid account." << endl;
					}
					else {
						accounts[accountIndex - 1]->deposit(amount);
					}
					break;
				default:
					cout << "Invalid usage. Please use deposit <sum>. Alternative usage: deposit <account_index> <sum>." << endl;
					break;
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
				int sourceIndex = stoi(parameters[1]);  // Convert the source account chosen to an integer
				int destinationIndex = stoi(parameters[2]);  // Convert the destination account chosen to an integer
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
				// Check parameters
				if (parameters.size() < 2) {
					cout << "Invalid input. Usage: project <years>" << endl;
					continue;  // Skip to the next command
				}
				
				int years = stoi(parameters[1]);

				if (isa_account == nullptr) {
					// If ISA account does not exist, output to console
					cout << "ISA account does not exist. Unable to project balance." << endl;
					continue;
				}
				else isa_account->computeInterest(years);
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
		delete isa_account;
		delete viewedAccount;
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