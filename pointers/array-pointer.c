// more pointers
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int i,x,y;
	int size = 8;
	unsigned char array[]={0,1,2,3,4,5,6,7};
	unsigned char * array_p = &array[0];

	for(x=0;x<size;x++){
		printf("before: array[%d]=%u; *array_p=%u\n",x,array[x],*array_p);
		*array_p = *array_p << 1;
		printf("after : array[%d]=%u; *array_p=%u\n\n",x,array[x],*array_p);
		array_p++;
	}

	return ;
}