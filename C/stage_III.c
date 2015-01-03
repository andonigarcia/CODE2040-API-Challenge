// Andoni Garcia. 2014.
// My source code for Stage III: Prefix.

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
	char *prefix = "";
	char *array = "";
	char filteredArray[1024];
	int i;
	for(i = 0; i < 1024; i++)
		filteredArray[i] = '\0';

	// Get the Prefix/Array
	char *getMessage = "{\"token\":\"yicZ5DfAT6\"}";
	grabInfo(domain, port, "prefix", getMessage, &prefix, &array, 2);

	// Filter the Array
	int count = 0;
	filteredArray[count++] = '[';
	char *curr = strtok(array, ",\"");
	while(curr != NULL){
		int isEqual = 1;
		for(i = 0; i < strlen(prefix); i++){
			if(prefix[i] != curr[i]){
				isEqual = 0;
				break;
			}
		}
		if(!isEqual){
			filteredArray[count++] = '\"';
			for(i = 0; i < strlen(curr); i++)
				filteredArray[count++] = curr[i];
			filteredArray[count++] = '\"';
			filteredArray[count++] = ',';
		}
		curr = strtok(NULL, ",\"");
	}
	filteredArray[--count] = ']';
	printf("Filtered Array is: %s\n\n", filteredArray);

	// Send the Array
	char sendMessage[2048];
	sprintf(sendMessage, "{\"token\":\"yicZ5DfAT6\",\"array\":%s}", filteredArray);
	//free(prefix);
	//free(array);
	grabInfo(domain, port, "validateprefix", sendMessage, NULL, NULL, 1);

	return 0;
}