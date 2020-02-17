#include <json/json.h>
#include <stdio.h>
#include <string.h>


// #define Json_object_object_foreach(obj,key,val)\
// 	char *key; \
// 	struct json_object *val;\
// 	struct lh_entry *entry;\
// 	for(entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k; val = (struct json_object*)entry->v; } ; entry; }); entry = entry->next )

void json_parse(json_object * jobj, unsigned char *Name, unsigned char *Value) 
{
    enum json_type type;
    json_object_object_foreach(jobj, name, val) 
    {
    	if(json_object_get_type(val)== json_type_object) json_parse(val,Name,Value);
    	if(!strcmp(name, Name)) 
        {
            printf("%s:%s\n",name, json_object_get_string(val));
            strcpy(Value, json_object_get_string(val));
        }
    	printf("%s:%s\n",name, json_object_get_string(val));
    }
}

int main() 
{
	unsigned char jString[1024] = "";
	FILE *jsonFile = fopen("file.json", "r");
	printf ("JSON\n\n");
    fgets(jString, 1024, jsonFile);

    unsigned char Name[64], Value[64];
	json_object * jobj = json_tokener_parse(jString);
	Value[0]='\0';
	if(jobj != NULL) 
	{
		strcpy(Name, "n");
		json_parse(jobj,Name,Value);
		if(Value[0]!='\0')
		{
			printf("Name: %s, Value: %s\n",Name, Value);
		}
		else printf("No Name:%s\n",Name);

	}
	else printf("JSON format error\n");
	fclose(jsonFile);
}



















