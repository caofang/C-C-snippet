#include <stdio.h>
 
int main()
{
	unsigned int a=0xaa;
	unsigned int b=0xbb;

	printf("===== Before Swap =====\n");
	printf("a = %x\nb = %x\n", a, b);


	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("===== After Swap =====\n");
	printf("a = %x\nb = %x\n", a, b);

	return 0;
}