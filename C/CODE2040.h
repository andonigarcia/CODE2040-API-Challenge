// Andoni Garcia. 2014.
// Header file for my CODE2040 API Challenge submission in C.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

/*  ================================================================
	================================================================
	======================== JSON STRUCTURES =======================
	================================================================
	================================================================
*/

// Structure for JSON parser
typedef struct jsonObj jsonObj;
struct jsonObj{
  char *key;
  char *value;
};

// List of jsonObjects
typedef struct jsonObjList jsonObjList;
struct jsonObjList{
	jsonObj *object;
	jsonObjList *next;
};

/*  ================================================================
	================================================================
	============================= json.c ===========================
	================================================================
	================================================================
*/

// Allocates memory for a new jsonObj
jsonObj *new_jsonObj(char *key, char *val);

// Helper function to print a jsonObj
void print_jsonObj(jsonObj *obj);

// Helper function to free a jsonObj
void free_jsonObj(jsonObj *obj);

// Allocates memory for a new jsonObjList
jsonObjList *new_jsonObjList(jsonObj *obj, jsonObjList *nxt);

// Helper function to print a jsonObjList
void print_jsonObjList(jsonObjList *list);

// Helper function to free a jsonObjList
void free_jsonObjList(jsonObjList *list);

// Very simple JSON parser solely for use in the responses of the CODE2040 API Challenge
jsonObjList *jsonParse(char *jsonData);

/*  ================================================================
	================================================================
	=========================== httppost.c =========================
	================================================================
	================================================================
*/

// Sends an HTTP POST Request and returns the response
char *HTTPPOSTRequest(char *domain, int port, char *directory, char *message, char *content);

// Handles Getting/Sending info to the CODE2040 Challenge
void grabInfo(char *domain, int port, char *page, char *message, char **Option1, char **Option2, int levels, int print);

// Makes the get message
char *getMsg(char *token);

// Makes the typical json-encoded message for sending answers
char *sendMsg(char *key1, char *value1, char *key2, char *value2, int opt);

/*  ================================================================
	================================================================
	===================== interfacemessages.c ======================
	================================================================
	================================================================
*/

void err_multArgs1(char *argv);

void msg_welcome();

void msg_register();

void msg_registerEmail();

void msg_registerGithub();

void msg_token(char *token);

void msg_success();

void msg_failure();

void msg_pass(char *stage);

void msg_notPass(char *msg);

void msg_stageIWelcome();

void msg_stageIIWelcome();

void msg_stageIIIWelcome();

void msg_stageIVWelcome();