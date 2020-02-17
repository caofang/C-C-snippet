#include <stdio.h>
#define SWAP(a,b)\
({\
	a ^= b;\
	b ^= a;\
	a ^= b;\
	a;\
})

int main() 
{
	int x=1;
	int y=2;
	int z=3;
	printf("%d\n",SWAP(x,y));
	
	unsigned int i=1;
	unsigned int _a = 0x0a0b0c0d;
	unsigned char *_c = (unsigned char*)&_a;

	if ((unsigned char)i==1) printf("Little endian\n");
	else printf("Big endian\n");

	for (i=0;i<4;i++)
	{
	  printf("i: %x, c: %x\n",i, *(_c+i));
	}
}
