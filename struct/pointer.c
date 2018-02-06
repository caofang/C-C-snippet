#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char str1[32];
    unsigned short len;
}String;

int main(){
    // String mystring;
    // printf("mystring: %p\n",&mystring);

    String *mystring1;
    printf("old mystring1: %p\n",mystring1);

    unsigned char *memory;
    memory = malloc(64);
    printf("memory: %p\n",memory);

    mystring1 = (String *)memory;

    printf("new mystring1: %p\n",mystring1);

    char str1[]="hello world";
    strcpy((*mystring1).str1, str1);
    (*mystring1).len=strlen(str1);

    bzero(mystring1, sizeof(*mystring1));
    printf("struct len: %d, string: %s, %d\n",
        sizeof(*mystring1),(*mystring1).str1, (*mystring1).len);



    free(memory);

    return 0;
}