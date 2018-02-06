// more pointers
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main ()
{
    int i=0;
    unsigned char * p1 = malloc(64);
    unsigned char *tmpp;
    unsigned char ** pp1; 

    unsigned char var1 = 0;
    unsigned char var2 = 4;
    unsigned char var3 = 8;
    unsigned char var4 = 12;

    printf("p1: %p, pp1: %p, *pp1: %p\n", p1, pp1, *pp1 );

    // tmpp = p1 + 32;
    tmpp = p1;
    for(i=0; i<16; i++)
    {
        *tmpp = i;
        tmpp++;
    }

    *pp1 = p1;
    
    pp1++;
    *pp1 = p1+4;

    pp1++;
    *pp1 = p1+8;

    pp1++;
    *pp1 = p1+12;

    pp1 = pp1-3;    // back to original position


    
    printf("p1: %p, pp1: %p, *pp1: %p\n", p1, pp1, *pp1 );    
    printf("*p1  : %d, *(p1+4)  : %d, *(p1+8)  : %d, *(p1+12) : %d\n",*p1, *(p1+4), *(p1+8), *(p1+12));
    printf("**pp1: %d, **(pp1+1): %d, **(pp1+2): %d, **(pp1+3): %d\n",**pp1, **(pp1+1), **(pp1+2),**(pp1+3));


    free(p1);
    return 0;
}