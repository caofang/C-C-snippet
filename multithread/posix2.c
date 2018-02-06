/******************************************************************************
this program: the main thread passes unsigned char argument to the thread function

******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_THREADS  2

void *PrintHello(void *threadid)
{
    unsigned char *msg = (unsigned char *)threadid;
    while(*msg){
        printf("msg: %x\n",*(msg++));
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    unsigned char msg[]="12345";
    for(t=0;t<NUM_THREADS;t++){
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *)msg);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
