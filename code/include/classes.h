#ifndef CLASSES_HEADER
#define CLASSES_HEADER

#include <bits/stdc++.h>
using namespace std;

class User
{
	// Data members
	string userName;
	string password;
	int userType;

	//Friend Class Authenticate
	friend class Authenticate;

public:
	// Constuctor
	User(string userName, string password, int userType)
	{
		this->userName = userName;
		this->password = password;
		this->userType = userType;
	}
	string getType(string username);
	string getUsername()
	{
		return userName;
	}
};
class Authenticate
{
	string userName;
	string password;
	// static Authenticate *instance;
public:
	bool loggedIn = false;
	string activUser;
	// Authenticate *init();
	Authenticate(); // Default Constructor
	bool Register(User *);
	bool login();
	bool isLoggedIn();
	void setLoggedIn();
	void logout();
	bool createUser(string userName, string password);
	int checkUserExistence(string userName);
	bool isUserExist(string userName);
	User *getUserDetails(string userName);
};

class Utilities
{
public:
	Utilities();	//Default Constructor
	void welcomeMenu();
	bool loginMenu(Authenticate &auth);
	void authenticationMenu(Authenticate &auth);
	vector<string> readFileLineByLine(const char *filename);
	void Exit();
};

class Client
{
public:
	int clientSocket;	//Socket id
	Client();	//Default Constructor
};
#endif