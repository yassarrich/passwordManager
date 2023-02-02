//Name:Yassar Rich
//Date: 07/16/2022
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main()
{
	int capacity;
	char userchoice;
	char space;

	cout << "Enter hash table capacity: ";
	cin >> capacity;
	if (capacity <= 0)
	{
		cout << "Your input is too large for prime_below()." << endl;
		cout << "Set to default capacity: 11\n";
		capacity = 11;
	}
	PassServer passList(capacity);

	do
	{
		Menu();
		cin >> userchoice;

		if(userchoice == 'l' || userchoice == 'L')
		{
			string userfile;
			cout << "Enter password filename to load from: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userfile);

			if(!passList.load(userfile.c_str()))
				cout << "ERROR: Cannot open file " << userfile << '\n';
			
		}

		else if(userchoice == 'a' || userchoice == 'A')
		{
			string userName;
			string userPass;

			cout << "Enter username: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userName);

			cout << "Enter password: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userPass);

			pair<string, string> userPair(userName, userPass);

			if(passList.addUser(userPair))
			{
				cout << "\nUser " << userName << " added." << endl;
			}
			else
			{
				cout << "\nERROR: User already exists." << endl;
			}
		}

		else if(userchoice == 'r' || userchoice == 'R')
		{
			string userName;
			cout << "Enter username: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userName);

			if(passList.removeUser(userName))
				cout << "\nUser " << userName << " deleted." << endl;
			else
				cout << "\nERROR: User not found." << endl;
		}

		else if(userchoice == 'c' || userchoice == 'C')
		{
			string userName;
			string oldPass;
			string newPass;
			cout << "Enter username: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userName);

			cout << "Enter password: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, oldPass);

			cout << "Enter new password: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, newPass);

			pair<string, string> oldPair(userName, oldPass);
			if(passList.changePassword(oldPair, newPass))
				cout << "\nPassword changed for user " << userName << "." << endl;
			else
				cout << "\nERROR: Could not change user password." << endl;
		}

		else if(userchoice == 'f' || userchoice == 'F')
		{
			string userName;
			cout << "Enter username to find: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, userName);
			
			if(!passList.find(userName))
				cout << "\nUser " << "'" << userName << "'" << " not found." << endl;
			else
				cout << "\nUser " << "'" << userName << "'" << "  found." << endl;
		}
		
		else if(userchoice == 'd' || userchoice == 'D')
			passList.dump();

		else if(userchoice == 's')
			cout << "\nSize of hashtable is: " << passList.size() << endl;

		else if(userchoice == 'w' || userchoice == 'W')
		{
			string passFile;
			cout << "Enter password file to write to: ";
			while(isspace(cin.peek()) && !cin.eof())
				cin.get(space);
			getline(cin, passFile);
			passList.write_to_file(passFile.c_str());
		}

		else if(userchoice == 'x' || userchoice == 'X')
		{}

		else
			cout << "\nERROR: Invalid entry. Please try again.";
	}while(userchoice != 'x' && userchoice != 'X');


	return 0;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
