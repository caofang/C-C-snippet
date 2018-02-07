#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int a=107; 
	int b=8;
	printf("a = %d, b = %d\n", a,b);
	printf("a%%b = %d\n", a%b);

	// a & ((1<<b)-1)
	printf("shift a%%b = %d\n", a&(b-1));


	// ===== timer =====
    int pause = 10000;
    struct timeval start, end, start1, end1;

    printf("start\n");
    gettimeofday(&start, NULL);

    int i=0;
    for(i=0;i<4096;i++)
    {
    	a=i&(b-1);
    	// a=i%b;
    }
    
    gettimeofday(&end, NULL);
    long int duration_us = ((end.tv_sec-start.tv_sec ) * 1000000 + end.tv_usec - start.tv_usec);
    double duration_ms = (double)duration_us/1000;
    printf("\nduration: %gms\n", duration_ms);

    printf("end\n");
    // _____ timer _____

    a=1;
    printf("a = %d\n", a);
    a^=1;
    printf("a = %d\n", a);
    a^=1;
    printf("a = %d\n", a);


	return 0;
}