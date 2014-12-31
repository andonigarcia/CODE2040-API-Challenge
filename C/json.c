// Andoni Garcia. 2014.
// Some json tools written in C.

#include "CODE2040.h"

// Allocates memory for a new jsonObj
jsonObj *new_jsonObj(char *key, char *val)
{
  jsonObj *newjsonObj = malloc(sizeof(jsonObj));
  if(newjsonObj == NULL){
    fprintf(stderr, "ERROR: Allocation failed for new jsonObj\n");
    exit(0);
  }

  newjsonObj->key = strdup(key);
  newjsonObj->value = strdup(val);
  return newjsonObj;
}

// Helper function to print a jsonObj
void print_jsonObj(jsonObj *obj)
{
	printf("Key: %s\nValue: %s\n", obj->key, obj->value);
	return;
}

// Helper function to free a jsonObj
void free_jsonObj(jsonObj *obj)
{
	free(obj->key);
	free(obj->value);
	free(obj);
	return;
}

// Allocates memory for a new jsonObjList
jsonObjList *new_jsonObjList(jsonObj *obj, jsonObjList *nxt)
{
	jsonObjList *newList = malloc(sizeof(jsonObjList));
	if(newList == NULL){
		fprintf(stderr, "ERROR: Allocation failed for new jsonObjList\n");
		exit(0);
	}

	newList->object = obj;
	newList->next = nxt;
	return newList;
}

// Helper function to print a jsonObjList
void print_jsonObjList(jsonObjList *list)
{
	while(list != NULL){
		print_jsonObj(list->object);
		list = list->next;
	}
	return;
}

// Helper function to free a jsonObjList
void free_jsonObjList(jsonObjList *list)
{
	if(list == NULL)
		return;
	free_jsonObj(list->object);
	free_jsonObjList(list->next);
	free(list);
	return;
}

// Very simple JSON parser solely for use in the responses of the CODE2040 API Challenge
// I think I have a memory leak with not freeing each strdup until the end.
jsonObjList *jsonParse(char *jsonData)
{
	if(strlen(jsonData) == 0){
		fprintf(stderr, "There is no response to parse...Check request status");
		exit(0);
	}

	jsonObjList *list;
	char *dataToParse = strdup(jsonData);
	// Tried using strtok or other library functions, but arrays have commas and keys have colons and it becomes a bitch.
	// Easier to implement, but less efficient (I'm sacrificing efficiency for comprehensiveness).
	int isFirstObj = 1;
	int isKey = 1;
	int i;
	char *key, *value;
	for(i = 0; i < strlen(dataToParse); i++){
		char tmpKey[1024];
		char tmpValue[1024];
		int count = 0;

		char c = dataToParse[i];
		if(c == '\"'){
			// Switch Key/Value selection
			if (isKey)
				isKey = 0;
			else
				isKey = 1;

			// Loop to go through rest of the selection
			i++;
			char curr;
			while ((curr = dataToParse[i]) != '\"'){
				// Backwards because I switched isKey at the top. Sorry.
				if (isKey){
					tmpValue[count++] = curr;
				} else {
					tmpKey[count++] = curr;
				}
				// Chose to increment at the end, so for loop isn't hindered
				i++;
			}
			if (isKey){
				value = strdup(tmpValue);
			} else {
				key = strdup(tmpKey);
			}
			count = 0;
			// Went through both key and value and is back
			if (isKey){
				jsonObj *parsedObj = new_jsonObj(key, value);
				if(isFirstObj){
					list = new_jsonObjList(parsedObj, NULL);
					isFirstObj = 0;
				} else {
					list = new_jsonObjList(parsedObj, list);
				}
			}
		}
	}
	free(key);
	free(value);
	return list;
}