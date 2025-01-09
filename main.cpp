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
#include <string>
#include <cstring>

// Headers
#include "BankAccounts.h"

using namespace std;

// Declare Methods
void view_accounts(vector<Account*> accounts);

int main()
{
		vector <string> parameters;
		string userCommand;
		// you may also want to store a collection of opened accounts here

		vector<Account*> accounts; // accounts created will be stored in vector
		Current* currentAccount = nullptr; // stores pointer to current account
		Savings* isaAccount = nullptr; // stores pointer to isa account
		Account* viewedAccount = nullptr; // stores viewed account

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
			try {
				// Error checking
				if (parameters.empty()) {
					throw invalid_argument("Invalid input. Please enter a valid command.");
				}
				// Throw argument that outputs to console instead of crashing program
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
						throw invalid_argument("Invalid input. Usage: open <account_type> <initial_deposit>");
					}

					// Extract account type (1 for Current, 2 for Savings, 3 for ISA) and initial deposit
					int accountType = stoi(parameters[1]);  // Convert the account type to an integer
					double initialDeposit = stod(parameters[2]);  // Convert the initial deposit to a double

					if (initialDeposit < 0) {
						throw invalid_argument("You have entered an invalid initial deposit value. Please enter a valid amount.");
					}

					// Based on the account type, create the appropriate account
					switch (accountType) {
					case 1: // open a current account
						if (currentAccount == nullptr) {
							// Open a Current account and add it to the accounts vector
							currentAccount = new Current(initialDeposit);
							accounts.push_back(currentAccount);
						}
						else {
							throw invalid_argument("Current account already exists. You can only create 1 Current Account.");
						}
						break;
					case 2: // open a savings account
						accounts.push_back(new Savings(initialDeposit, 0));
						break;
					case 3: // open a isa account
						if (isaAccount == nullptr) {
							if (initialDeposit < 1000) {
								// If initial deposit is smaller than 1000, output an error to console
								cout << "ISA initial balance must be >= " << char(156) << "1000." << endl;
							}
							else {
								// If ISA account is sucessfully created, appoint a pointer to a new ISA, and append to vector
								isaAccount = new Savings(initialDeposit, 1);
								accounts.push_back(isaAccount);
							}
						}
						else {
							throw invalid_argument("ISA account already exists.");
						}
						break;
					default:
						throw invalid_argument("Invalid account type. Please choose 1 (Current), 2 (Savings), or 3 (ISA).");
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
							throw invalid_argument("The selected account does not exist. Please select a valid account.");
						}
						else {
							accounts[accountIndex - 1]->toString();
							viewedAccount = accounts[accountIndex - 1];
						}
					}
					else view_accounts(accounts);
				}
				else if (command.compare("withdraw") == 0)
				{
					// allow user to withdraw funds from an account
					// Input Check
					if (parameters.size() < 2) {
						throw invalid_argument("Invalid input. Usage: withdraw <account_index> <withdraw_amount>");
					}

					// allow user to deposit funds into an account
					int accountIndex;  // Convert the account chosen to an integer
					double amount;  // Convert the deposit to a double
					int parametersSize = parameters.size();

					switch (parametersSize) {
					case 2: // Input is withdraw <sum>
						if (viewedAccount != nullptr) {
							// Check if account has been viewed
							amount = stod(parameters[1]); // Convert parameter 2 to amount
							viewedAccount->withdraw(amount); // Deposit to viewed account
						}
						else {
							throw invalid_argument("You have not viewed an account. Use view <account_index>. // Alternative Usage: withdraw <account_index> <amount>.");
						}
						break;
					case 3: // Input is withdraw <account_index> <amount>
						// Convert parameters 2 and 3 to account selected and amount
						accountIndex = stoi(parameters[1]);
						amount = stod(parameters[2]);

						// Check if account exists
						if (accountIndex < 0 || accountIndex > accounts.size()) {
							throw invalid_argument("The selected account does not exist. Please select a valid account.");
						}
						else {
							accounts[accountIndex - 1]->withdraw(amount);
						}
						break;
					default:
						throw invalid_argument("Invalid amount of parameters. Please use withdraw <sum>. // Alternative usage: withdraw <account_index> <amount>.");
						break;
					}
				}
				else if (command.compare("deposit") == 0)
				{
					// Input Check
					if (parameters.size() < 2) {
						throw invalid_argument("Invalid input. Usage: deposit <account_index> <deposit_amount>");
					}

					// allow user to deposit funds into an account
					int accountIndex;  // Convert the account chosen to an integer
					double amount;  // Convert the deposit to a double
					int parametersSize = parameters.size();

					switch (parametersSize) {
					case 2: // Input is deposit <sum>
						if (viewedAccount != nullptr) {
							// Check if account has been viewed
							amount = stod(parameters[1]); // Convert parameter 2 to amount
							viewedAccount->deposit(amount); // Deposit to viewed account
						}
						else {
							throw invalid_argument("You have not viewed an account. Use view <account_index>. // Alternative Usage: deposit <account_index> <amount>.");
						}
						break;
					case 3: // Input is deposit <account_index> <amount>
						// Convert parameters 2 and 3 to account selected and amount
						accountIndex = stoi(parameters[1]);
						amount = stod(parameters[2]);

						// Check if account exists
						if (accountIndex < 0 || accountIndex > accounts.size()) {
							throw invalid_argument("The selected account does not exist. Please select a valid account.");
						}
						else {
							accounts[accountIndex - 1]->deposit(amount);
						}
						break;
					default:
						throw invalid_argument("Invalid amount of parameters. Please use deposit <sum>. // Alternative usage: deposit <account_index> <amount>.");
						break;
					}
				}
				else if (command.compare("transfer") == 0)
				{
					// allow user to transfer funds between accounts
					// i.e., a withdrawal followed by a deposit!
					// Input Check
					if (parameters.size() < 4) {
						throw invalid_argument("Invalid input. Usage: transfer <source_index> <destination_index> <amount>");
					}

					// allow user to deposit funds into an account
					int sourceIndex = stoi(parameters[1]) - 1;  // Convert the source account chosen to an integer
					int destinationIndex = stoi(parameters[2]) - 1;  // Convert the destination account chosen to an integer
					double amount = stod(parameters[3]);  // Convert the deposit to a double

					if (amount <= 0) {
						throw invalid_argument("Invalid amount entered. You can only transfer amounts of positive integers.");
					}
					else if (sourceIndex < 0 || sourceIndex >= accounts.size() || destinationIndex < 0 || destinationIndex >= accounts.size()) {
						throw invalid_argument("One or both of the selected accounts do not exist. Please select valid accounts.");
					}

					// Check if source and destination accounts are the same
					else if (sourceIndex == destinationIndex) {
						throw invalid_argument("Cannot transfer money to the same account. Please enter a valid destination account.");
					}


					accounts[sourceIndex]->transfer(accounts, sourceIndex, destinationIndex, amount);
				}
				else if (command.compare("project") == 0)
				{
					// compute compound interest t years into the future
					// Check parameters
					if (parameters.size() < 2) {
						throw invalid_argument("Invalid input. Usage: project <years>");
					}

					int years = stoi(parameters[1]);

					if (isaAccount == nullptr) {
						// If ISA account does not exist, output to console
						throw invalid_argument("ISA account does not exist. Unable to project balance.");
					}
					else isaAccount->computeInterest(years);
				}
				//else if (command.compare("search"))
				//{
				//	allow users to search their account history for a transaction
				//  (this is a stretch task)
				//}
			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << endl;
			}
		}
		// Free up memory
		for (auto& account : accounts) {
			delete account;
		}
		currentAccount = nullptr;
		isaAccount = nullptr;
		viewedAccount = nullptr;

		cout << "Press ENTER to quit...";
		return 0;
}

// Implement Methods
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