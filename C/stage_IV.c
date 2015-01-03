// Andoni Garcia. 2014.
// My source code for Stage IV: The Dating Game.

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
	char *datestamp = "";
	char *tmpInt = "";
	long long int interval;
	char newTime[1024];
	int i;
	for(i = 0; i < 1024; i++){
		newTime[i] = '\0';
	}
	
	// Get the Time
	char *getDirectory = "/api/time";
	char *getMessage = "{\"token\":\"yicZ5DfAT6\"}";
	grabInfo(domain, port, "time", getMessage, &tmpInt, &datestamp, 2);
	interval = atoi(tmpInt);

	printf("%s\n%s\n%lld\n", datestamp, tmpInt, interval);

	// Add the Times
	// Currently have to use localtime - 1 for some reason
	int year, month, day, hour, min;
	float sec;
	sscanf(datestamp, "%d-%d-%dT%d:%d:%fZ", &year, &month, &day, &hour, &min, &sec);
	time_t initialize;
	time(&initialize);
	struct tm *givenTime = gmtime(&initialize);
	givenTime->tm_year = year - 1900;
	givenTime->tm_mon = month - 1;
	givenTime->tm_mday = day;
	givenTime->tm_hour = hour;
	givenTime->tm_min = min;
	givenTime->tm_sec = (int) sec;
	time_t unixTime = mktime(givenTime);
	unixTime += interval;
	struct tm *addTime = localtime(&unixTime);
	sprintf(newTime, "%04d-%02d-%02dT%02d:%02d:%02d.000Z", addTime->tm_year + 1900,
		addTime->tm_mon + 1, addTime->tm_mday, addTime->tm_hour - 1, addTime->tm_min,
		addTime->tm_sec);
	printf("New time is: %s\n\n", newTime);
	
	// Send the Time
	char sendMessage[2048];
	sprintf(sendMessage, "{\"token\":\"yicZ5DfAT6\",\"datestamp\":\"%s\"}", newTime);
	//free(datestamp);
	grabInfo(domain, port, "validatetime", sendMessage, NULL, NULL, 1);
	return 0;
}