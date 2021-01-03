#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define netErr -1
#define MaxData 150

int sock;
int client_socks[5] = {0};
int clients_size = 0;
char close_string[] = {'c','l','o','s','e',' ','c','l','i','e','n','t','\0'};

/*
 * This method is closing the connection with clients connected to our port
 */
void closeConnection(int client,int clientN)
{
        printf("Closing connection with client %d\n", client);
        close(client);
        client_socks[clientN] = 0;
}

/*
 * This method handling the string that sends over the connection
 */
void stringHandler(fd_set *readfds) {
  int data_len;
  char data[MaxData];
  for (int i = 0; i < clients_size; i++)
 {
    int client_sock = client_socks[i];
    if (FD_ISSET(client_sock, readfds)) {
      data_len = recv(client_sock, data, MaxData, 0);

      if (data_len == 0) 
	closeConnection(client_sock, i);


      if (data_len) {
	data[data_len-2] = '\0';
  	if(strcmp(close_string, data) == 0)
  	{
		printf("comprasion worked\n");
		closeConnection(client_sock, i);    		
	}
	else
		printf("%s","here1");
		//runExec(client_sock, data, data_len);
      }
    }
  }
}

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
 * Interupt handler
 */

void signalHandler(int sig) 
{

  int closed_connections=0;

  for (int i=0; i<clients_size; i++)
  {
    if(client_socks[i]!=0)
    {
      closed_connections++;
      close(client_socks[i]);     
     }    
  }

  printf("number of client closed - %d \n",closed_connections);
  close(sock);
  printf("closed server\n");
  exit(-1);
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

  signal(SIGABRT,signalHandler);
  
  char * port = argv[1];
  sock = listnerSocket(port);

  if (sock != netErr) 
 {
	while (1) 
	{
		printf("%s","here");
		stringHandler(&readfds);
	}
  }
  close(sock);
}
