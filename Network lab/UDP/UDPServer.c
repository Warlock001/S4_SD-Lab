// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> //main sockets header
#include <arpa/inet.h>  //definition for internet operations
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code starts

int main() {
	
	// file descriptor of socket to be binded
	int sockfd; 			
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr,cliaddr;

	// Creating socket file descriptor
	
	if( (sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	//void *memset(void *ptr, int x, size_t n);
	// ptr -> starting address of memory to be filled
	// x -> Value to be filled
	// n -> Number of bytes to be filled starting from ptr
	// to be filled.
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; //refers to IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address

	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
		sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len, n;
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
			 MSG_WAITALL,( struct sockaddr *) &cliaddr,
			 &len);
	buffer[n] = '\0';
	printf("Client :%s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("Hello message sent.\n");

	return 0;	
}