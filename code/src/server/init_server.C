#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void start_server(){
    system("gnome-terminal -e 'sh -c \"cd server && g++ server.C -o server && ./server\"'");
    // printf("hi\n");
    // system("gnome-terminal -e 'sh -c \"ls\"'");
    // while(1);
	// sleep(10);
}
