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
