/* itoa example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
  unsigned int i_int=6800;
  unsigned char i_char[8];

  sprintf(i_char, "%u", i_int);
  // itoa(i_int, i_char, 4);	// no library
  printf("%s\n",i_char);
  return 0;
}
