#include <stdio.h>
#include <string.h>

int main()
{
	char buff[16];
	int size=16;
	int a=0;
	int b=0;
	printf("number1:");
	fgets(buff,size,stdin);
	a=atoi(buff);
	bzero(buff,size);
	printf("number2:");
	fgets(buff,size,stdin);
	b=atoi(buff);
	printf("sum:%d\n",a+b);
	return 0;
}
