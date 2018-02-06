#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(int argc, char **argv) 
{
    unsigned char *udp_header= malloc(16384);
    unsigned short active_points=0;

    unsigned int i, max_cnt = 10000000; //<<28; //(unsigned int)(-1);
    unsigned short var;

    time_t ltime; /* calendar time */
    struct timezone *tzp;
    ltime=time(NULL); /* get current cal time */
    struct timeval start, end, start1, end1;

    gettimeofday(&start, NULL);

    for(i=0;i<max_cnt;i++){
        var = (unsigned short)i;
        memcpy(udp_header+(i&1023), &var,2);
    }
    gettimeofday(&end, NULL);  
    
    // gettimeofday(&start1, NULL);  

    for(i=0;i<max_cnt;i++){
        *(unsigned short *)(udp_header+(i&1023)) = (unsigned short)i;
    }
    gettimeofday(&end1, NULL);  

    printf("point1: %ld:%ld\n", start.tv_sec, start.tv_usec);
    printf("point2: %ld:%ld\n", end.tv_sec, end.tv_usec);
    printf("point3: %ld:%ld\n", end1.tv_sec, end1.tv_usec);

    // unsigned long long duration = ((end.tv_sec-start.tv_sec ) * 1000000 + end.tv_usec - start.tv_usec);
    // printf("duration: %ldms\n",duration );


    // unsigned long long duration1 = ((end1.tv_sec-start1.tv_sec ) * 1000000 + end1.tv_usec - start1.tv_usec);
    // printf("duration1: %ldms\n",duration1 );
 
    return 0;
}
