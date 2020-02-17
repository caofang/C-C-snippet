#include <stdio.h> 
#include <string.h> 

int main() 
{ 
	char str[] = "Geeks,for,,Geeks"; 
	char* token; 
	char* rest = str; 

	int count = 0;
	while ((token = strtok_r(rest, ",", &rest)))
	{
		printf("%d, %s\n",count++, token); 
		
	} 

	return (0); 
} 