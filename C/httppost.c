// Andoni Garcia. 2014.
// A simple HTTP POST Request function

#include "CODE2040.h"

// Sends an HTTP POST Request and returns the response
// THE MESSAGE MUST BE JSON ENCODED (I guess I could remove this feature later...)
char *HTTPPOSTRequest(char *domain, int port, char *directory, char *message)
{
	char request[5120];
	struct hostent *server;
	struct sockaddr_in serveraddr;

	// Creates a new socket
	int newSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(newSocket < 0){
		fprintf(stderr, "ERROR: Socket did not open.\n");
		exit(0);
	}

	// Finds the host
	server = gethostbyname(domain);
	if(server == NULL){
		fprintf(stderr, "ERROR: Server not found.\n");
		exit(0);
	}
	
	// Establishes the server address
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
	serveraddr.sin_port = htons(port);

	// Makes a connection to the server
	if(connect(newSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
		fprintf(stderr, "ERROR: Could not connect to server.\n");
		exit(0);
	}

	// Writes the HTTP POST Request using JSON
	bzero(request, 5120);
	sprintf(request, "POST %s HTTP/1.1\r\nHost: %s\r\nContent-type: application/json\r\nContent-length: %d\r\n\r\n%s", directory, domain, (int) strlen(message), message);
	if(send(newSocket, request, strlen(request), 0) < 0){
		fprintf(stderr, "ERROR: Problem sending request\n");
		exit(0);
	}

	// Gets the response
	recv(newSocket, request, 5120, 0);
	char *response = strstr(request, "\r\n\r\n");
	if(response == NULL){
		fprintf(stderr, "ERROR: Bad response\n");
		exit(0);
	}
	close(newSocket);
	response += 4;
	return strdup(response);
}