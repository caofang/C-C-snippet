#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("int: %d\nchar: %d\n unsigned char: %d\n pointer: %d\n long: %d\n"
        , sizeof(int), sizeof(char), sizeof(unsigned char), sizeof(unsigned char*), sizeof(long));
	return 0;
}