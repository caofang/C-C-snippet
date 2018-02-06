#include <stdio.h>

void simple_func(unsigned char * arg, int len)
{
	strcpy(arg, "123243456");
}

int main(int argc, char const *argv[])
{
	unsigned char res[1024];
	printf("1: %s\n", res);
	simple_func(res, sizeof(res));
	printf("2: %s\n", res);
	return 0;
}