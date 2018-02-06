#include <stdio.h>
int main() 
{
	int i,j;
	int sw_size;
	sw_size = sizeof(unsigned long long);

	// ===== long =====
	printf("===== Before Swap =====\n");
	unsigned long long ln = 0x1122334455667788;
	printf("sw_size: %d\n", sw_size);
	printf("ln: %llx\n",ln);

	unsigned char *ln_tmp;
	ln_tmp = (unsigned char *)&ln;


	for(i=0; i<sw_size; i++) printf("ln_tmp: %x\n",*(ln_tmp+i));


	printf("===== After Swap =====\n");
	for(i=0; i<sw_size/2; i++)
	{
		// *ln_tmp = (unsigned char)ln[i];
		*(ln_tmp+i) = *(ln_tmp+i) ^ *(ln_tmp + sw_size-i-1);
		*(ln_tmp + sw_size-i-1) = *(ln_tmp+i) ^ *(ln_tmp + sw_size-i-1);
		*(ln_tmp+i) = *(ln_tmp+i) ^ *(ln_tmp + sw_size-i-1);
	}
	printf("ln: %llx\n",ln);
	for(i=0; i<sw_size; i++) printf("ln_tmp: %x\n",*(ln_tmp+i));
	// _____ long _____

}
