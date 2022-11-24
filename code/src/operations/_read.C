#include <bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#define SIZE 1024

//function to send files
void send_file(FILE *fp, int sockfd, const char *filename,int size)
{
	int n;
	char data[SIZE] = {0};
	sleep(1);
	send(sockfd, filename, size, 0);
	sleep(4);
	while (fgets(data, SIZE, fp) != NULL)
	{
		if (send(sockfd, data, sizeof(data), 0) == -1)
		{
			perror("Error in sending file.");
			exit(1);
		}
		bzero(data, SIZE);
	}
}
