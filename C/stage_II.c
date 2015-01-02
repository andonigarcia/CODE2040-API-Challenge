// Andoni Garcia. 2014.
// My source code for Stage II: Needle in a Haystack.

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
	char *needle;
	char *haystack;
	int index = -1;

	// Get the Needle/Haystack
	char *getDirectory = "/api/haystack";
	char *getMessage = "{\"token\":\"yicZ5DfAT6\"}";
	char *getResponse = HTTPPOSTRequest(domain, port, getDirectory, getMessage);
	jsonObjList *getResponseList = jsonParse(getResponse);
	jsonObjList *getValues = jsonParse(getResponseList->object->value);
	print_jsonObjList(getValues);
	needle = strdup(getValues->object->value);
	haystack = strdup(getValues->next->object->value);
	free_jsonObjList(getResponseList);
	free_jsonObjList(getValues);

	// Find the Index
	char *curr = strtok(haystack, ",\"");
	index++;
	while(strcmp(curr, needle) != 0){
		index++;
		curr = strtok(NULL, ",\"");
	}
	printf("Index is: %d\n\n", index);

	// Send the Index
	char *sendDirectory = "/api/validateneedle";
	char sendMessage[2048];
	sprintf(sendMessage, "{\"token\":\"yicZ5DfAT6\",\"needle\":%d}", index);
	char *sendResponse = HTTPPOSTRequest(domain, port, sendDirectory, sendMessage);
	free(needle);
	free(haystack);
	jsonObjList *sendResponseList = jsonParse(sendResponse);
	print_jsonObjList(sendResponseList);
	free_jsonObjList(sendResponseList);

	return 0;
}