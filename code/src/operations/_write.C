#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

#define SIZE 1024

//function to write files
void write_file(int sockfd){
  int n;
  FILE *fp;
  char buffer[SIZE];
  bzero(buffer, SIZE);
  n = recv(sockfd, buffer, SIZE, 0);
  printf("%s\n", buffer);
  sleep(5);
  fp = fopen(buffer, "w");
  bzero(buffer, SIZE);

  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}
