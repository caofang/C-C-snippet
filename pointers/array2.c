// more pointers
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	int i,x,y;
	unsigned char array[3][6] = {{1,2,3,11,12,13},{4,5,6,14,15,16},{7,8,9,17,18,19}};
	unsigned char * p = &array[0][0];

	//*p = array;
	for(y=0;y<3;y++){
		for(x=0;x<6;x++){
			printf("pointer: %p, *p: %i, array[%d][%d] =  %u\n",p,*p,y,x,array[y][x]);

		}
	}

	return ;
}