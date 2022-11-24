#include <bits/stdc++.h>
#include "classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define PORT 5200
using namespace std;

void Utilities::welcomeMenu(){
	for(auto x: Utilities::readFileLineByLine("decorate.txt")){
		cout<<x<<endl;
	}
}



vector<string> Utilities::readFileLineByLine(const char *filename){
	vector<string> v;
	ifstream openFile(filename);
	
	string temp;
	while (getline(openFile, temp)){
		v.push_back(temp);
	}
	openFile.close();
	
	return v;
}
void Utilities::authenticationMenu(Authenticate &auth){
	int option;
	do{
		string username;
	cout<<"Enter username to register: ";
	cin>>username;
	if(auth.isUserExist(username)){
		cout<<"\nUser is already Registered.\n\t\t1. Try again with different username\n\t\t2. Goto login\n";
		cout<<"Enter your option: ";
		cin>>option;
		if(option==1) continue;
		if(option==2) this->loginMenu(auth); cout<<auth.activUser<<endl; break; continue;
	}
	else{
		string password;
		cout<<"Enter password to register: ";
		cin>>password;
		bool result = auth.Register(new User(username, password, 2));
		if(result){
			cout<<"Hurreh! user registered sucessfully\n";
			cout<<"\n\t\t\t1. To login\n\t\t\t2. To exit\n";
			cout<<"Enter your choice: ";
			int op;
			cin>>op;
			if(op==1) this->loginMenu(auth);
			else if(op==2) this->Exit();
		}
	}
	}while(option==1);
}

Client::Client(){
	int clientSocket , serverSocket , receiveMsgSize;
	clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if(clientSocket < 0)
        {
		cout << "Creation of client socket failed" << endl;
		
        }
	struct sockaddr_in serverAddr , clientAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(PORT);
	if(connect(clientSocket ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0)
	{
		cout << "Connection Error..." << endl;
		
	}
	else
	{
		cout << "\t\tConnection Established..." << endl;
	}

	this->clientSocket = clientSocket;

}


void clientOperationsMenu(){
	cout<<"1. Upload file\n2. Show files\n3.Delete file\n";
	cout<<"Enter option: ";
	int option;
	cin>>option;

	if(option==1){
		//upload the file
		
	}
	else if(option==2){
		//List the files
	}
	else if(option==3){
		//Delete the file
	}else{
		cout<<"invalid input\n";
	}

}



void Utilities::Exit(){
	cout<<"Thank you for choosing us!\nHave a nice day!!\n";
	exit(0);
}

bool Utilities::loginMenu(Authenticate &auth){
	cout<<"\n***************************  Welcome to Login  ******************************\n\n";
	bool validUser=false, validPassword=false;
		string _username, username;
		int count=0;
		int pcount=0;
	do{
		cout<<"\nEnter username: ";
		cin>>_username;
		if(auth.isUserExist(_username)){
			validUser = true;
		}
		else{
			cout<<"Opps! user not exist. Please enter a valid username"<<endl;
		}
		count++;
	}while(!validUser && count<5);
	if(count==5)
		goto skip_password;
	do{
		string _password, password;
		cout<<"Enter password: ";
		cin>>_password;
		
		ifstream fin("users.txt",ios::in);
		string userType;
		while(fin>>username>>password>>userType){
			if(_password==password and _username==username){
				validPassword=true;
			}
		}
		if(!validPassword){
			cout<<"Wrong Password, Try again"<<endl;
		}
	}while(!validPassword && pcount++<4);
skip_password:
	if(validUser and validPassword){
		cout<<"logged in sucessfully"<<endl;
		cout<<endl;
		cout<<"*****************************************************************************"<<endl;
		auth.activUser = _username;
		auth.setLoggedIn();
		//User authentcated
		return true;
	}
	else{
		cout<<"Too many attempts,Try again later!"<<endl;
		exit(0);
	}
	return false;
}
Authenticate::Authenticate(){

}

void Authenticate::setLoggedIn(){
	this->loggedIn = true;
}
void Authenticate::logout(){
	this->loggedIn = false;
	this->activUser= "";

}

bool Authenticate::isLoggedIn(){
	return this->loggedIn;
}

User *Authenticate:: getUserDetails(string username){
	return NULL;
}

void splitString(string str, string delimiter = " ")
{
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        cout << str.substr(start, end - start) << endl;
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    cout << str.substr(start, end - start);
}

bool Authenticate::isUserExist(string username){
	ifstream openFile2("users.txt");
	string line;
	while(!openFile2.eof()){
		getline(openFile2, line);
		string _username;
		for(auto x: line){
			if(x==' ') break;
			else _username += x;
		}
		if(username==_username){
			return true;
		}
	}
	openFile2.close();

	return false;
}

bool Authenticate:: Register(User *urs){
	
	ofstream writeFile("users.txt", ios::app);
	if(!writeFile) return false;
	writeFile<<urs->userName<<" "<<urs->password<<" "<<urs->userType<<"\n";
	writeFile.close();
	return true;
}


bool Authenticate:: login(){
	
	this->loggedIn = true;
	return "true";
}

