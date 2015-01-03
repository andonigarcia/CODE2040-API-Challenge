// Andoni Garcia. 2015.
// A terminal interface for the CODE2040 API Challenge

#include "CODE2040.h"

#define domain "challenge.code2040.org"
#define port 80
char *token, *getMessage;
int passes = 0;

// Utility function to check if the code passed the stage
void didPass(char *msg, char *stage)
{
	char *pass = "PASS";
	int chck = 1;
	int i;
	for(i = 0; i < 4; i++){
		if(pass[i] != msg[i]){
			chck = 0;
			break;
		}
	}
	if(chck){
		msg_pass(stage);
		passes++;
	} else {
		msg_notPass(msg);
	}
	return;
}

// Function to complete Stage I
void stageI()
{
	char *string;
	msg_stageIWelcome();
	grabInfo(domain, port, "getstring", getMessage, &string, NULL, 1, 0);
	printf("\nYour string is: %s\n", string);

	// Reverse the String
	if(string){
		int len = strlen(string);
		if(len > 1){
			int midpoint = ((int) len--/2) + 1;
			int i;
			for(i = 0; i < midpoint; i++){
				char tmp = string[i];
				string[i] = string[len -i];
				string[len - i] = tmp;
			}
		}
	}
	printf("Your reversed string is: %s\n\n", string);

	char *sIMsg = sendMsg("token", token, "string", string, 1);
	free(string);
	char *resp;
	grabInfo(domain, port, "validatestring", sIMsg, &resp, NULL, 1, 0);
	didPass(resp, "Stage I");
	return;
}

// Function to complete Stage II
void stageII()
{
	char *needle, *haystack, strIndex[4];
	int index = -1;
	msg_stageIIWelcome();
	grabInfo(domain, port, "haystack", getMessage, &needle, &haystack, 2, 0);
	printf("\nYour needle is: %s\n", needle);
	printf("Your haystack is: [%s]\n", haystack);

	// Find the needle
	if(needle && haystack){
		char *curr = strtok(haystack, ",\"");
		index++;
		while(strcmp(curr, needle)){
			index++;
			curr = strtok(NULL, ",\"");
		}
	}
	printf("The index of the needle is: %d\n\n", index);

	sprintf(strIndex, "%d", index);
	char *sIIMsg = sendMsg("token", token, "needle", strIndex, 0);
	free(needle);
	free(haystack);
	char *resp;
	grabInfo(domain, port, "validateneedle", sIIMsg, &resp, NULL, 1, 0);
	didPass(resp, "Stage II");
	return;
}

// Function to complete Stage III
void stageIII()
{
	char *prefix, *array, filteredArray[1024];
	int i;
	for(i = 0; i < 1024; i++)
		filteredArray[i] = '\0';
	msg_stageIIIWelcome();
	grabInfo(domain, port, "prefix", getMessage, &prefix, &array, 2, 0);
	printf("\nYour prefix is: %s\n", prefix);
	printf("Your array is: [%s]\n", array);

	// Filter the array
	int count = 0;
	if(prefix && array){
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
	}
	printf("The filtered array is: %s\n\n", filteredArray);

	char *sIIIMsg = sendMsg("token", token, "array", filteredArray, 0);
	free(prefix);
	free(array);
	char *resp;
	grabInfo(domain, port, "validateprefix", sIIIMsg, &resp, NULL, 1, 0);
	didPass(resp, "Stage III");
	return;
}

// Function to complete Stage IV
void stageIV()
{
	char *datestamp, *tmpInt, newTime[1024];
	long long int interval;
	int i, year, month, day, hour, min;
	float sec;
	for(i = 0; i < 1024; i++)
		newTime[i] = '\0';
	msg_stageIVWelcome();
	grabInfo(domain, port, "time", getMessage, &tmpInt, &datestamp, 2, 0);
	printf("\nYour datestamp is: %s\n", datestamp);
	printf("Your interval is: %s\n", tmpInt);
	interval = atoi(tmpInt);

	// Adding the two times
	// Broken on Cygwin. See: http://stackoverflow.com/questions/310363/how-to-add-one-day-to-a-time-obtained-from-time
	if(datestamp && tmpInt && (interval > 0)){
		sscanf(datestamp, "%d-%d-%dT%d:%d:%fZ", &year, &month, &day, &hour, &min, &sec);
		time_t initialize;
		time(&initialize);
		struct tm *givenTime = localtime(&initialize);
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
			addTime->tm_mon + 1, addTime->tm_mday, addTime->tm_hour, addTime->tm_min,
			addTime->tm_sec);
	}
	printf("Your new datestamp is: %s\n\n", newTime);

	char *sIVMsg = sendMsg("token", token, "datestamp", newTime, 1);
	free(datestamp);
	free(tmpInt);
	char *resp;
	grabInfo(domain, port, "validatetime", sIVMsg, &resp, NULL, 1, 0);
	didPass(resp, "Stage IV");
	return;
}

int main(int argc, char **argv)
{
	if(argc > 1){
		err_multArgs1(argv[0]);
	}

	char tmpEmail[256], tmpGithub[256], *email, *github;

	// Initializations
	msg_welcome();
	msg_register();
	msg_registerEmail();
	scanf("%s", tmpEmail);
	msg_registerGithub();
	scanf("%s", tmpGithub);
	email = strdup(tmpEmail);  // For some reason can't free
	github = strdup(tmpGithub);  // See above comment
	if(!strcmp(email, "a"))
		email = "andoni@uchicago.edu";
	if(!strcmp(github, "a"))
		github = "https://github.com/andonigarcia/CODE2040-API-Challenge";
	
	// Get token
	char *registerMessage = sendMsg("email", email, "github", github, 1);
	grabInfo(domain, port, "register", registerMessage, &token, NULL, 1, 0);
	msg_token(token);
	getMessage = getMsg(token);

	// Go through the Stages
	stageI();
	stageII();
	stageIII();
	stageIV();

	// Endings
	if(passes == 4)
		msg_success();
	else
		msg_failure();
	return 0;
}