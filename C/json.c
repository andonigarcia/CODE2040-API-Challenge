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
/* I tried using library functions like strtok, but it became a bitch. Definitely not
 * the most efficient parser, but it works for what I am doing. I tried to not rely on
 * external libraries like jsonc.
*/
jsonObjList *jsonParse(char *jsonData)
{
	if(strlen(jsonData) == 0){
		fprintf(stderr, "There is no response to parse...Check request status\n");
		exit(0);
	}

	jsonObjList *list;
	char *dataToParse = strdup(jsonData);
	int isFirstObj = 1;
	int i;
	for(i = 0; i < strlen(dataToParse); i++){
		char key[1024];
		char value[1024];
		// There was a bug with rewriting the memory space of key and value. Must flush on each cycle
		int j;
		for(j = 0; j < 1024; j++){
			key[j] = '\0';
			value[j] = '\0';
		}
		int count = 0;

		char c = dataToParse[i];
		if(c == '\"'){
			// Grab the key
			i++;
			char curr;
			while((curr = dataToParse[i++]) != '\"')
				key[count++] = curr;
			count = 0;
			// Skip the colon
			while((curr = dataToParse[i++]) != ':');
			// Grab the value
			curr = dataToParse[i++];
			char next;
			if(curr == '{'){
				while((next = dataToParse[i++]) != '}')
					value[count++] = next;
			} else if(curr == '['){
				while((next = dataToParse[i++]) != ']')
					value[count++] = next;
			} else if(curr == '\"'){
				while((next = dataToParse[i++]) != '\"')
					value[count++] = next;
			} else {
				while((next = dataToParse[i++]) != ',' && next != '}')
					value[count++] = next;
			}
			// Add to list
			jsonObj *parsedObj = new_jsonObj(key, value);
			if(isFirstObj--){
				list = new_jsonObjList(parsedObj, NULL);
			} else{
				list = new_jsonObjList(parsedObj, list);
			}
		}
	}
	free(dataToParse);
	return list;
}