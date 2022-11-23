#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

#define SIZE 1024


void write_file(int sockfd){
  int n;
  FILE *fp;
  //char filename[] = "received_";
  char buffer[SIZE];
  bzero(buffer, SIZE);
  n = recv(sockfd, buffer, SIZE, 0);
  //strcat(filename, buffer);
  printf("%s\n", buffer);
  sleep(5);
  fp = fopen(buffer, "w");
  bzero(buffer, SIZE);

  //printf("%s\n", buffer);
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
    //printf("Error in receiving");
      break;
      return;
    }
    //printf("%s\n",buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}
