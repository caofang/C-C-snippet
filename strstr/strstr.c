#include <stdio.h>
#include <string.h>

int main()
{
	char *sent = "this is my sample example";
	char *word = "sample";

	

	if(strstr(sent, word))
	{
	    printf("true\n");
	}
	else{
		printf("false\n");
	}
}