// Andoni Garcia. 2014.
// Header file for my CODE2040 API Challenge submission in C.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
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
// THE MESSAGE MUST BE JSON ENCODED (I guess I could remove this feature later...)
char *HTTPPOSTRequest(char *domain, int port, char *directory, char *message);