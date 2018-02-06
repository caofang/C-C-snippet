#include <stdio.h>
int main() 
{
	unsigned int i;
	unsigned int a = 0x12345678;
	// printf("before: %x\tafter: %x\n", a, (a >> 24) | ((a >> 8) & 0x0000ff00) | ((a << 8) & 0x00ff0000) | (a << 24));


	unsigned char packet[16];
	memcpy(&packet[6], &a, 4);
	printf("before:\t[6]: %x\t[7]: %x\n", packet[6], packet[7]);
	unsigned char tmp = *(packet + 7);
	*(packet + 7) = *(packet + 6);
	*(packet + 6) = tmp;

	printf("after:\t[6]: %x\t[7]: %x\n", packet[6], packet[7]);

}
