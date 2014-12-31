// Andoni Garcia. 2014.
// My source code for Stage I: Reverse a String.

#include "CODE2040.h"

int main(int argc, char **argv)
{
	if(argc > 1){
		fprintf(stderr, "Please execute this without any additional arguments.\n");
		fprintf(stderr, "The information is baked into the main function...as such, re-run this:\n");
		fprintf(stderr, "./%s", argv[0]);
		exit(0);
	}

	char *domain = "challenge.code2040.org";
	int port = 80;
	char *string;

	// Get the String
	char *getDirectory = "/api/getstring";
	char *getMessage = "{\"token\":\"yicZ5DfAT6\"}";
	char *getResponse = HTTPPOSTRequest(domain, port, getDirectory, getMessage);
	jsonObjList *getResponseList = jsonParse(getResponse);
	print_jsonObjList(getResponseList);
	string = strdup(getResponseList->object->value);
	free_jsonObjList(getResponseList);

	// Reverse the String
	int len = strlen(string);
	int midpoint = ((int) len--/2) + 1;
	int i;
	for(i = 0; i < midpoint; i++){
		char tmp = string[i];
		string[i] = string[len -i];
		string[len - i] = tmp;
	}
	printf("Reversed: %s\n\n", string);

	// Send the Reversed String
	char *sendDirectory = "/api/validatestring";
	char sendMessage[2048];
	sprintf(sendMessage, "{\"token\":\"yicZ5DfAT6\",\"string\":\"%s\"}", string);
	char *sendResponse = HTTPPOSTRequest(domain, port, sendDirectory, sendMessage);
	free(string);
	jsonObjList *sendResponseList = jsonParse(sendResponse);
	print_jsonObjList(sendResponseList);
	free_jsonObjList(sendResponseList);

	return 0;
}