#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>

#include <dirent.h>

// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "type.c"

#include "query-with-hash.c"

#define MAX 80
#define SA struct sockaddr

int a = 30;
int sockfd, connfd, len;
struct sockaddr_in servaddr, cli;

static int PORT = 30000;
// Function designed for chat between client and server.
int func(int sockfd)
{

	char buff[100000];
	int n;
	// infinite loop for chat
	bzero(buff, MAX);

	// read the message from client and copy it in buffer
	read(sockfd, buff, sizeof(buff));

	char *queryU = strtok(buff, " ");
	// printf("1:  %ld \n", strlen(queryU));
	char qry[sizeof(queryU) + 1];
	strcpy(qry, queryU);
	qry[strlen(qry)] = '\0';
	// printf("2: %ld \n", strlen(qry));
	// qry[sizeof(queryU)] = '\0';
	char *top = strtok(NULL, " ");
	int htop = toInt(top);
	HEAPSIZE = htop;

	query(finvH, fnmeH, terms, qry, totalDocs, HEAPSIZE);

	return write(sockfd, output, strlen(output)); //LOCAL ONLY
}

// Driver function
int main(int a, char *args[])
{
	if (a == 2)
	{
		PORT = toInt(args[1]);
	}
	go();
	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0)
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");

flag:
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA *)&cli, &len);
	if (connfd < 0)
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");

	// Function for chatting between client and server
	while (func(connfd))
		goto flag;

	close(sockfd);
}