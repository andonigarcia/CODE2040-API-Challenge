// Andoni Garcia. 2014.
// My source code for the Registration Phase.

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
	char *directory = "/api/register";
	char *message = "{\"email\":\"andoni@uchicago.edu\",\"github\":\"https://github.com/andonigarcia/CODE2040-API-Challenge\"}";
	char *response = HTTPPOSTRequest(domain, port, directory, message);
	jsonObjList *responselist = jsonParse(response);
	print_jsonObjList(responselist);
	free(responselist);
	return 0;
}