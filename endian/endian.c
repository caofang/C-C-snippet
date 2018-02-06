#include <stdio.h>
int main() 
{
   unsigned int i;
   unsigned int _a = 0x0a0b0c0d;
   unsigned char *_c = (unsigned char*)&_a;
   if (*_c) printf("Little endian\n");
   else printf("Big endian\n");

   for (i=0;i<4;i++)
   {
      printf("i: %x, c: %x\n",i, *(_c+i));
   }
}
