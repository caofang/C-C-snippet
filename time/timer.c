#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // ===== time stamp =====
    time_t ltime; // calendar time
    ltime=time(NULL); // get current cal time
    printf("%s\n",ctime(&ltime));
    // _____ time stamp _____

    // ===== timer =====
    int pause = 10000;
    struct timeval start, end, start1, end1;

    printf("start\n");
    gettimeofday(&start, NULL);

    printf("pause for %d us\n", pause);
    usleep(pause);
    
    gettimeofday(&end, NULL);
    long int duration_us = ((end.tv_sec-start.tv_sec ) * 1000000 + end.tv_usec - start.tv_usec);
    double duration_ms = (double)duration_us/1000;
    printf("\nduration: %gms\n", duration_ms);

    printf("end\n");
    // _____ timer _____

    return 0;   
}