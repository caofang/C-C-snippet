// more pointers
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define size 4
int main ()
{
    unsigned int tmp;
    unsigned int *tmp1;
    unsigned short array_short[] = {19660,1,4095,15};
    unsigned short * array_short_p = &array_short[0];
    unsigned char * array_byte_p;

printf("//============================//\n");

    printf("*array_short_p: %x \n", *array_short_p);
    array_short_p++;
    printf("*array_short_p: %x \n", *array_short_p);
    // tmp = (unsigned int) 2
    tmp = (unsigned int)*array_short_p;
    // *tmp1 = 1*2^16 + 2 
    tmp1 = (unsigned int *)array_short;
    printf("tmp: %x, tmp1: %x \n",tmp,*tmp1);

printf("//============================//\n");

    array_byte_p = (unsigned char *)array_short;
    printf("*array_byte: %x\n",*array_byte_p);
    array_byte_p++;
    printf("*(array_byte+1): %x\n",*array_byte_p);

//__________


   
    return;

}
