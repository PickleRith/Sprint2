#include <bits/stdc++.h>
#include "classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <string.h>
#define LOG_LEVEL DEBUG
#include "operations/_write.C"
#include "operations/_read.C"
#include "server/init_server.C"
#include <dirent.h>
#include <sys/types.h>
#include "logger/Logger_file.h"

#define SIZE 1024
#define FILEN_SIZE 20
using namespace std;

//list files
void list_files(const char* path=".") {
   DIR *dr;
   struct dirent *en;
   dr = opendir(path); //open all directory
   if (dr) {
      while ((en = readdir(dr)) != NULL) {
         cout<<" "<<en->d_name<<endl; //print all directory name
      }
      closedir(dr); //close all directory
   }
}


//driver code
int main()
{
	LOG_DEBUG("debug log");
	cout << "Hello, Welcome :) " << endl;
	Authenticate auth;
	Utilities u;

//create login menu
Login_menu:
	u.welcomeMenu();
	cout << "\n\n";
	cout << "\t\t\t1. -  Login\n\t\t\t2. -  Register\n\t\t\t3. -  Exit\n\n";
	int authOption;

	cout << "Enter your choice: ";
	cin >> authOption;
	cout << "\n\n";
	switch (authOption)
	{
	case 1: // login
		u.loginMenu(auth);
		break;
	case 2: // Register
		u.authenticationMenu(auth);
		break;
	case 3:
		u.Exit();
	default:
		LOG_ERROR("Invalid choice,Please try Again!");
		break;
	}
	cout<<endl;
	if (auth.loggedIn)
	{
		LOG_INFO("LOGIN SUCCESSFUL");
		// user authenticated
		cout << auth.activUser;
		// invoke the server
		start_server();
		// client creation
		sleep(10);
		Client c;
		int idx=0;
		char client_name[10]; 
		for(auto x: auth.activUser){
			client_name[idx++] = x;
		}
		client_name[idx]='\0';
		send(c.clientSocket, client_name, sizeof(client_name) + 1, 0);
		do 
		{
			cout << "\n\t\t\t1. Upload file\n\t\t\t2. Download file\n\t\t\t3. Show files\n\t\t\t4. Delete\n\t\t\t5. Exit\n";
			enum Operations { UPLOAD = 1, DOWNLOAD =2 , SHOW = 3, DELETE = 4, EXIT =5 };
			cout << "Enter choice: ";
			int option;
			cin >> option;
			switch (option)
			{
			case UPLOAD:
			{ // Uploading feature for files
				FILE *fp;
				char command[] = "upload";
				send(c.clientSocket, command, sizeof(command) + 1, 0);
				char filename[FILEN_SIZE];
				string fname;
				cout<<"Enter file name: ";
				cin>>fname;
				strcpy(filename,fname.c_str());
				if(access(filename,F_OK)==0){
				fp = fopen(filename, "r");
				if (fp == NULL)
				{
					perror("Error in reading file.");
					exit(1);
				}
				send_file(fp, c.clientSocket, filename,fname.length());
				fclose(fp);
				LOG_INFO("File uploading Completed!");
				}
				else
					LOG_ERROR("File does not exists!,Please try Again.");
			}

			break;
			case DOWNLOAD:
				// Downloading feature of files
				{

				FILE *fp;
				char command[] = "download";
				send(c.clientSocket, command, sizeof(command) + 1, 0);
				sleep(1);
					char buffer[SIZE];
					char filename[FILEN_SIZE];
					printf("Enter filename: ");
					
					scanf("%123s",filename);
					send(c.clientSocket, filename, sizeof(filename) + 1, 0);
					int response_code = recv(c.clientSocket, buffer, SIZE, 0);
        				if(strcmp(buffer,"File is downloading")==0){
					cout << "Downloading ";

					write_file(c.clientSocket);
					LOG_INFO("File Downloading Completed!");
					}
					else
						LOG_ERROR(buffer);
				cout<<endl;
				}
				break;
			case SHOW:
				{// show files
				cout<<"List of files at Server side:\n\n";
				system("cd server && ./display_file && cd ..");
				}
				break;
				
			//deletion of files
			case DELETE:
			{
				char command[] = "delete";
				send(c.clientSocket, command, sizeof(command) + 1, 0);
				cout<<"Enter file name: ";
        			char buf[SIZE];
        			scanf("%s",buf);
        			send(c.clientSocket, buf, sizeof(buf) + 1, 0);
        			int response_code = recv(c.clientSocket, buf, SIZE, 0);
        			printf("%s",buf);
        			cout<<endl;
        			break;
        		}
			case EXIT:
			{
				u.Exit();
				break;
			}
			default:
				LOG_ERROR("Invalid choice,Please try Again!");
				break;
			}
		} while (false);
	}
	else
	{
		// user is logged logged out or not authenticated
		LOG_ERROR("User is not logged in");
		goto Login_menu;
	}

	return 0;
}
