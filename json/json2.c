#include <json/json.h>
#include <stdio.h>
#include <string.h>


#define Json_object_object_foreach(obj,key,val)\
	char *key; \
	struct json_object *val;\
	struct lh_entry *entry;\
	for(entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k; val = (struct json_object*)entry->v; } ; entry; }); entry = entry->next )



void json_parse(json_object * jobj) {
    enum json_type type;
    Json_object_object_foreach(jobj, name, val) 
    {
        type = json_object_get_type(val);
        switch (type) 
        {
            case json_type_null: 
                // printf("json_type_null\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
            case json_type_boolean: 
                // printf("json_type_boolean\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
            case json_type_double: 
                // printf("json_type_double\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
            case json_type_int: 
                // printf("json_type_int\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
            case json_type_object: 
                printf("===json_type_object===\n");
                printf("%s:%s\n",name, json_object_get_string(val));
                json_parse(val);
            break;
            case json_type_array: 
                // printf("json_type_array\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
            case json_type_string: 
                // printf("json_type_string\n");
                printf("%s:%s\n",name, json_object_get_string(val));
            break;
        }
    }
}

/*
void json_parse(json_object * jobj) 
{
	enum json_type type;
	// char *key; struct json_object *val;
	json_object_object_foreach(jobj, key, val) 
	{
		type = json_object_get_type(val);
		switch (type) 
		{
			case json_type_null: 
				// printf("json_type_null\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
			case json_type_boolean: 
				// printf("json_type_boolean\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
			case json_type_double: 
				// printf("json_type_double\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
			case json_type_int: 
				// printf("json_type_int\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
			case json_type_object: 
				printf("===json_type_object===\n");
				printf("%s:%s\n",key, json_object_get_string(val));
				json_parse(val);
			break;
			case json_type_array: 
				// printf("json_type_array\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
			case json_type_string: 
				// printf("json_type_string\n");
				printf("%s:%s\n",key, json_object_get_string(val));
			break;
		}
	}
}
*/
int main() 
{
	unsigned char jString[1024] = "";
	FILE *jsonFile = fopen("file.json", "r");
	printf ("JSON\n\n");
    fgets(jString, 1024, jsonFile);

	json_object * jobj = json_tokener_parse(jString);
	if(jobj != NULL) json_parse(jobj);
	else printf("JSON format error\n");
	fclose(jsonFile);
}
