#include <stdio.h>


#ifdef LIB
	#include "lib.h"
#endif

int main()
{
	hello();
	for (int i=0; i<2; i++)
		printf("i:%d\n",i);


}