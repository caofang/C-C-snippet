#include <stdio.h>

int main()
{
	const int size=8; 
	unsigned char buffer[8];
	printf("buffer size: %d\n", size);

	int i=0;

	printf("mod\n");
	for (i=0; i<16; i++)
	{
		int index = i % size;
		printf("index: %d\n", index);
	}

	printf("\nbits\n");
	for (i=0; i<16; i++)
	{
		int index = i & 0B00000111;
		printf("index: %d\n", index);
	}
}