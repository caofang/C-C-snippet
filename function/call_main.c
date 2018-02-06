#include <stdio.h>

int main(int argc, char **argv) 
{
	printf("check %d\n", argc);
	if(argc != 2) main(2, NULL);

	return 0;
}
