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
	char *needle = "";
	char *haystack = "";
	int index = -1;

	// Get the Needle/Haystack
	char *getMessage = "{\"token\":\"yicZ5DfAT6\"}";
	grabInfo(domain, port, "haystack", getMessage, &needle, &haystack, 2);

	// Find the Index
	char *curr = strtok(haystack, ",\"");
	index++;
	while(strcmp(curr, needle) != 0){
		index++;
		curr = strtok(NULL, ",\"");
	}
	printf("Index is: %d\n\n", index);

	// Send the Index
	char sendMessage[2048];
	sprintf(sendMessage, "{\"token\":\"yicZ5DfAT6\",\"needle\":%d}", index);
	//free(needle);
	//free(haystack);
	grabInfo(domain, port, "validateneedle", sendMessage, NULL, NULL, 1);
	return 0;
}