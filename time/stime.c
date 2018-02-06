#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // int i,x,y,z;
    // if (argc < 2){

    //     printf("USAGE: %s loop-iterations\n", argv[0]);
    //     return 1;
    // }

    // unsigned long rawtime=1234567890;
    // unsigned long rawtime=1399390000; // 2014/05/06
    unsigned long rawtime=atoi(argv[1]);
    time_t current_time; /* calendar time */
    struct timeval ltime1;

    current_time=time(NULL); /* get current cal time */
    gettimeofday(&ltime1, NULL);

    printf("rawtime: %lu, ctime: %s\n",rawtime,ctime(&rawtime));
    stime(&rawtime);
    current_time=time(NULL); /* get current cal time */
    gettimeofday(&ltime1, NULL);
    printf("rawtime: %lu, ctime: %s\n",current_time,ctime(&current_time));
    
    unsigned long tmp = (unsigned long)ltime1.tv_sec;
    printf("ltime--unsigned long: %lu, ctime: %s\n",tmp,ctime(&tmp));
    

    
    

    printf("gettimeofday: %lu. %lx us\n",(unsigned long)ltime1.tv_sec,(unsigned long)ltime1.tv_usec);

    return 0;   
}