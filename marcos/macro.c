#include <stdio.h>

#define SWAP(a,b)\
({\
	a ^= b;\
	b ^= a;\
	a ^= b;\
})

// with return
#define SQUARE(x) (x*x)
#define BIT_SET(x,b)(x | (1<<b))
#define BIT_CLR(x,b)(x & ~(1<<b))
#define BIT_TOG(x,b)(x ^ (1<<b))
#define BIT_CHK(x,b)((x>>b) & 1)




// without return
#define ADD(a,b)(a+=b)

#define BIT_WRITE(a,b,c)\
({\
	if(c==0) a &= ~(1<<b);\
	else if(c==1) a |= (1<<b);\
	else printf("error format: c:%x\n",c);\
})

#define TEST(a,s)((a>>s)<<s)
#define TEST1(s)(sizeof(s))

#define TRACE_LOG(fmt, args...) fprintf(stdout, fmt, ##args);


int main(void)
{
	int a=0xff;
	int b=2;
	int c=0;

	printf("BIT_WRITE: a:%x, b:%x, c:%x\n",a,b,c);
	BIT_WRITE(a,b,c);
	printf("BIT_WRITE: a:%x, b:%x, c:%x\n",a,b,c);


	// printf("Original Data:\na:%d, b:%d,c:%d\n",a,b,c);
	// TRACE_LOG("%s", "print macro\n");
	// TRACE_LOG("%s", "SWAP macro\n");
	// SWAP(a,b);
	// printf("a:%d, b:%d\n",a,b);
	// TRACE_LOG("%s", "SQUARE macro:\n");
	
	// c=SQUARE(c);
	// printf("c:%d\n",c);

	int bit=3;
	printf("BIT_SET: bit: %d, a:%x, a:%x\n",bit,a,BIT_SET(a,bit));
	printf("BIT_CLR: bit: %d, a:%x, a:%x\n",bit,a,BIT_CLR(a,bit));

	// printf("BIT_TOG: bit: %d, a:%x, a:%x\n",bit,a,a=BIT_TOG(a,bit));
	// printf("BIT_TOG: bit: %d, a:%x, a:%x\n",bit,a,BIT_TOG(a,bit));
	// printf("BIT_CHK: bit: %d, a:%x, %x\n",bit,a,BIT_CHK(a,bit));

	// ADD(a,b);
	// printf("ADD: a:%d\n",a);

	// a=1;
	// printf("test:%x,%x\n",a,TEST(a,1));
	// char x=0;
	// printf("test1:%x\n",TEST1(x));

    return 0;
}