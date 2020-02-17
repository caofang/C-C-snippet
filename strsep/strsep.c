#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

int main() 
{ 
	char *token;
	char string[]="1,2,3,,4";
	char *s = malloc(strlen(string));
	strcpy(s, string);

	while ((token = strsep(&s, ",")) != NULL)
	    printf("token=%s\n", token);

	
	free(s);

	return (0); 
} 