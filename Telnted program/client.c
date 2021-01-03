#include <arpa/inet.h>
#include <error.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ERROR -1
#define MAX 100

int sock;
char close_string[] = {'c','l','o','s','e',' ','c','l','i','e','n','t','\0'};
struct sockaddr_in server;
struct sockaddr_in client;

/*
 * This method is sending message to the server
 */
void messgServer() {
  char buffer[MAX];
  int n;
  for (;;) {
    bzero(buffer, sizeof(buffer));
    printf("Enter the string : ");
    n = 0;
    while ((buffer[n++] = getchar()) != '\n')
      ;
  
   buffer[n-1] = '\0';
    if (write(sock, buffer, sizeof(buffer)) < 0) 
    {
    	printf("No response from server, closing client socket");
    	close(sock);
     	exit(-1);
    }

    if(strcmp(close_string, buffer) == 0)
    {
	printf("connection closed, bye bye\n");
	close(sock);
	exit(0);
    }
    bzero(buffer, sizeof(buffer));
    read(sock, buffer, sizeof(buffer));
    printf("From Server :\n%s\n", buffer);
  }
}


/*
 * Interupt handler
 */

void sigHandle(int sig) {
  printf("\nInterrupt- closing client socket\n");
  close(sock);
  exit(-1);
}

/*
 * MAIN()
 */
int main(int argc, char **argv) {
  signal(SIGINT, sigHandle);
  int port;

  if (argc <= 1) {
    printf("needs to provide port numer\n");
    exit(-1);
  }
}
