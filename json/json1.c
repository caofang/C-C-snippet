#include <json/json.h>
#include <stdio.h>

int main() {
    // Creating a json object
    json_object * jobj = json_object_new_object();
    json_object * sub_obj = json_object_new_object();


    // ===== write as json =====
    /*
    { 
        "string": 
        { 
            "str2": "fuck u" 
        }, 
        "int": 10, 
        "double": 3.140000 
    }
    */

    unsigned char str1[] = "hello world";
    unsigned char str2[] = "HELLO WORLD"; 
    unsigned char str3[] = "Test Test";

    // Creating a json string
    json_object *jstring1 = json_object_new_string(str1);
    json_object *jstring2 = json_object_new_string(str2);

    // Creating a json integer
    json_object *jint = json_object_new_int(10);

    // Creating a json double
    json_object *jdouble = json_object_new_double(3.14);

    // Form the json object
    json_object_object_add(jobj,"string", jstring1);
    json_object_object_add(sub_obj,"str2", jstring2);
    json_object_object_add(jobj,"string", sub_obj);

    json_object_object_add(jobj,"int", jint);
    json_object_object_add(jobj,"double", jdouble);
    // Now printing the json object
    printf ("object1: \n%s\n",json_object_to_json_string(jobj));
    printf ("object2: \n%s\n",json_object_to_json_string(sub_obj));

    json_object_object_add(sub_obj,"str2", json_object_new_string(str3));
    printf ("object2 new: \n%s\n",json_object_to_json_string(sub_obj));
    printf ("object1 new: \n%s\n",json_object_to_json_string(jobj));


/*
    json_object_object_add(jobj,"str1", json_object_new_string(str1));
    json_object_object_add(jobj,"int", json_object_new_int(10));
    json_object_object_add(jobj,"double", json_object_new_double(3.14));

    printf ("The json object created: \n%s\n",json_object_to_json_string(jobj));
*/
    return 0;
}