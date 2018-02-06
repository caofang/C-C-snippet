#include <stdio.h>

#define GDT_ENTRY_DEFAULT_USER_DS 0
#define GDT_ENTRY_INIT(flags, base, limit) { { { \
	.a = ((limit) & 0xffff) | (((base) & 0xffff) << 16), \
	.b = (((base) & 0xff0000) >> 16) | (((flags) & 0xf0ff) << 8) | \
	((limit) & 0xf0000) | ((base) & 0xff000000), \
	} } }

int main()
{
	printf("hello world\n");
	[GDT_ENTRY_DEFAULT_USER_DS] = GDT_ENTRY_INIT(0xc092, 0, 0xfffff);

}