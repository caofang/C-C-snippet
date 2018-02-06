#include <stdio.h>
 
int main()
{
	unsigned int x=0xaa;
	unsigned int y=0xbb;

	printf("===== Before Swap =====\n");
	printf("x = %x\ny = %x\n", x, y);


	printf("===== After Swap =====\n");
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;

	printf("x = %x\ny = %x\n", x, y);

	return 0;
}