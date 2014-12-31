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
	while(list != NULL){
		free_jsonObj(list->object);
		jsonObjList *tmp = list;
		list = list->next;
		free(tmp);
	}
	return;
}

// Very simple JSON parser solely for use in the responses of the CODE2040 API Challenge
jsonObjList *jsonParse(char *jsonData)
{
	jsonObjList *list;
	int isFirstObj = 1;

	char *dataToParse = strdup(jsonData);
	dataToParse += 1;  //Removes the first bracket ghetto-ly
	dataToParse[strlen(dataToParse)-2] = ',';  //Makes last bracket a comma to parse easier
	dataToParse[strlen(dataToParse)-1] = '\0';
	
	char *currentToken = strtok(dataToParse, ",");
	while(currentToken != NULL){
		int len = strlen(currentToken);
		char key[len], val[len];
		int isKey = 1;
		int ct = 0;
		int i;
		for(i = 0; i < len; i++){
			char c = currentToken[i];
			if(c == '\"')
				continue;
			if(c == ':'){
				ct = 0;
				isKey = 0;
				continue;
			}
			if(isKey){
				key[ct++] = c;
			} else {
				val[ct++] = c;
			}
		}

		jsonObj *parsedObj = new_jsonObj(key, val);
		if(isFirstObj){
			list = new_jsonObjList(parsedObj, NULL);
			isFirstObj = 0;
		} else {
			list = new_jsonObjList(parsedObj, list);
		}

		currentToken = strtok(NULL, ",");
	}
	return list;
}