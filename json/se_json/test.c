// #include <json-c/json.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LOG(int line)
{
	printf("=== line ===: %d\n", line);
}

typedef struct _json
{
	char* key;
	char* value;

	struct _json* next;
	struct _json* head;
} JsonObject;

JsonObject *NewJsonObject()
{
	JsonObject* json = NULL;
	return json;
}

JsonObject *NewJsonItem(char* key, char* value)
{
	JsonObject* json = malloc(sizeof(JsonObject));
	json->key = key;
	json->value = value;
	return json;
}

JsonObject* AddJsonItem(JsonObject* dest, JsonObject* src)
{
	if(dest == NULL)
	{
		dest = src;
		dest->head = src;
		dest->next = NULL;
		return src;
	}

	dest->next = src;	
	return dest;
}

void JsonToString(JsonObject* obj, char* result)
{
	if(obj->head == obj)
	{
		strcpy(result, "{\"");
	}
	else{
		strcat(result, "\",\"");
	} 

	strcat(result, obj->key);
	strcat(result, "\":\"");
	strcat(result, obj->value);	

	if(obj->next)
	{
		JsonToString(obj->next, result);
		return;
	}

	strcat(result, "\"}");
}

int main() 
{
    char* result = malloc(512);

    JsonObject *item1 = NewJsonItem("str1","hello");
    JsonObject *item2 = NewJsonItem("str2","world");

    JsonObject *obj = AddJsonItem(obj, item1);
    AddJsonItem(obj, item2);
	JsonToString(obj,result);

    printf("%s\n", result);

    return 0;
}