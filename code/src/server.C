#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include "../operations/_write.C"
#include "../operations/_read.C"
#include "../operations/_show_files.C"

using namespace std;

#define MAX 1024
#define SIZE 1024

#define PORT 5200

//driver code for server
int main()
{
	int serverSocketHandler = socket(AF_INET , SOCK_STREAM , 0);
	//creating a socket and assigning it to the socket handler
	if(serverSocketHandler < 0)
        {
       // socket methode return -1 if the creation was not successful
		//LOG_ERROR("Socket creation has failed");
		cout << "Socket creation has failed.";
		return 0;
	    }
	struct sockaddr_in serverAddr , clientAddr;
	//specifying address and type for the server to operate under
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bindStatus = bind(serverSocketHandler , (struct sockaddr*) & serverAddr , sizeof(serverAddr));
	if(bindStatus < 0)
    {
		//LOG_ERROR("Socket binding has failed");
		cout << "Socket binding has failed" << endl;
		return 0;
	}
	//listen to the client while others are waiting in queue of size 5
	int listenStatus = listen(serverSocketHandler , 5);
	if(listenStatus < 0)
        {	// when queue is full listen fails
		cout << "Listner has failed" << endl;
		return 0;
        }
	cout << "\t\t...Waiting for connections... \n\n";
	char buff[MAX];
	int clientSocketHandler;
	socklen_t len = sizeof(clientAddr);
	int connection;
	if((connection = accept(serverSocketHandler , (struct sockaddr*) & clientAddr , &len)) < 0)
    {
		cout << "Server didn't accept the request." << endl;
		return 0;
	}
	else
    {
		cout << "Server accepted the request. \n" ;
	}
	// write_file(connection);
	char buffer[SIZE];
		int response_code = recv(connection, buffer, SIZE, 0);
		if(response_code<=0){
			cout<<"Something went wrong\n";
			exit(0);
		}
	cout<<"User "<< buffer <<" is connected."<<endl;


	//while statement
	while(true){
		char buffer[SIZE];
		int response_code = recv(connection, buffer, SIZE, 0);
		if(response_code<=0){
			cout<<"Something went wrong\n";
			exit(0);
		}
		else if(strcmp(buffer, "upload")==0){
			cout<<"uploading....."<<endl;
			write_file(connection);
			system("make display_file");
			cout<<"File Uploaded to Server\n";
			break;
		}
		else if(strcmp(buffer, "download")==0){
		
				FILE *fp;
				string fname;
			 	response_code = recv(connection, buffer, SIZE, 0);
			 	if(access(buffer,F_OK)==0){
			 		send(connection, "File is downloading", 20, 0);
			 		//LOG_INFO("Downloading");
			 		cout<<"Downloading ";
			 		const char *filename = buffer;
					if(response_code<=0){
						cout<<"Something went wrong\n";
						exit(0);
					}
					fname=buffer;
					printf("%s",buffer);
			 		fp = fopen(buffer, "r");
			 		if (fp == NULL)
			 		{
			 			perror("Error in reading file.");
			 			break;
			 		}
				
			 		send_file(fp, connection, filename,fname.length());
			 		cout<<"File transfer completed!"<<endl;
			 		system("make display_file");
					fclose(fp);
				}
				else
				{
					send(connection, "File does not exits!", 20, 0);
					cout<<"FIle does not exist";
					exit(0);
				}
			break;
			
		}
		else if (strcmp(buffer, "show_files") == 0)
		{
			cout << buffer << endl;
			DIR *dr;
			struct dirent *en;
			dr = opendir("."); // open all directory
			if (dr)
			{
				while ((en = readdir(dr)) != NULL)
				{
					send(connection, en->d_name, sizeof(en->d_name), 0);
				}
				closedir(dr); // close all directory
			}
		}
		else if(strcmp(buffer, "delete")==0){
				response_code = recv(connection, buffer, SIZE, 0);
			if(access(buffer,F_OK)==0){
				int res=remove(buffer);
				send(connection, "File deleted.", 13, 0);
				cout<<"File deleted.\n";}
			else{
				send(connection, "File does not exits!", 20, 0);
				cout<<"File does not exit\n";}
			}
			system("make display_file");
	}

	sleep(20);
	close(serverSocketHandler);
	return 0;

}
