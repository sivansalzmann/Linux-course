#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define netErr -1

int sock;
int client_socks[5] = {0};
int clients_size = 0;
char close_string[] = {'c','l','o','s','e',' ','c','l','i','e','n','t','\0'};

/*
 * This method is creating the listner socket
 */
int listnerSocket(char *p) {
  struct sockaddr_in server;
  int sockaddr_len = sizeof(struct sockaddr_in);
  int sock;
  int port = atoi(p);
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == netErr)
  {
    perror("server socket: ");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&server.sin_zero, 8);

  if ((bind(sock, (struct sockaddr *)&server, sockaddr_len)) == netErr ) {
    perror("bind: ");
    exit(-1);
  }

  if ((listen(sock, 5)) == netErr) {
    perror("listen:");
    exit(-1);
  }

  printf("Server bind port %d\n", port);
  return sock;
}

/*
 * MAIN()
 */
int main(int argc, char *argv[]) 
{

 if (argc <= 1) 
 {
    printf("missing port number\n");
    exit(-1);
  }

  fd_set readfds;
  
  char * port = argv[1];
  sock = listnerSocket(port);

  if (sock != netErr) 
 {
	printf("%d",1);
  }
  close(sock);
}
