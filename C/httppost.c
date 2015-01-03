// Andoni Garcia. 2014.
// A simple HTTP POST Request function

#include "CODE2040.h"

// Sends an HTTP POST Request and returns the response
char *HTTPPOSTRequest(char *domain, int port, char *directory, char *message, char *content)
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
	sprintf(request, "POST %s HTTP/1.1\r\nHost: %s\r\nContent-type: %s\r\nContent-length: %d\r\n\r\n%s",
		directory, domain, content, (int) strlen(message), message);
	if(send(newSocket, request, strlen(request), 0) < 0){
		fprintf(stderr, "ERROR: Problem sending request.\n");
		exit(0);
	}

	// Gets the response
	if(recv(newSocket, request, 5120, 0) < 0){
		fprintf(stderr, "ERROR: Could not get response.\n");
		exit(0);
	}
	char *response = strstr(request, "\r\n\r\n");
	if(response == NULL){
		fprintf(stderr, "ERROR: Cannot parse response.\n");
		exit(0);
	}

	close(newSocket);
	response += 4;
	return strdup(response);
}

// Handles Getting/Sending info to the CODE2040 Challenge
void grabInfo(char *domain, int port, char *page, char *message, char **Option1, char **Option2, int levels, int print){
	if(domain == NULL || port < 1 || page == NULL || message == NULL){
		fprintf(stderr, "An HTTP POST request cannot be made without a proper "
			    "domain, port, page, and message input. Please check your input"
			    " to grabInfo().\n");
		exit(0);
	}
	if(levels != 1 && levels != 2){
		fprintf(stderr, "This function only supports jsonParsing 1 or 2 levels "
			   "deep. Please check your input to grabInfo().\n");
		exit(0);
	}
	if(print != 0 && print != 1){
		fprintf(stderr, "The print argument acts as a boolean. Please enter "
			    "either 0 or 1 for the answer corresponding to false or true.");
		exit(0);
	}
	// Sets up the HTTP Request
	char directory[512];
	sprintf(directory, "/api/%s", page);

	char *response = HTTPPOSTRequest(domain, port, directory, message, "application/json");
	
	jsonObjList *respList = jsonParse(response);
	jsonObjList *jsonList = respList;
	if(levels == 2){
		jsonList = jsonParse(respList->object->value);
	}
	if(Option1 != NULL)
		*Option1 = strdup(jsonList->object->value);
	if(jsonList->next != NULL && Option2 != NULL)
		*Option2 = strdup(jsonList->next->object->value);
	if(print)
		print_jsonObjList(jsonList);
	free(respList);
	if(levels == 2)
		free(jsonList);
	return;
}

// Makes the get message
char *getMsg(char *token){
	char message[1024];
	sprintf(message, "{\"token\":\"%s\"}", token);
	return strdup(message);
}

// Makes the typical json-encoded message for sending answers
char *sendMsg(char *key1, char *value1, char *key2, char *value2, int quotes){
	char message[2048];
	if(quotes)
		sprintf(message, "{\"%s\":\"%s\",\"%s\":\"%s\"}", key1, value1, key2, value2);
	else
		sprintf(message, "{\"%s\":\"%s\",\"%s\":%s}", key1, value1, key2, value2);
	return strdup(message);
}