// this program is to exchange data
// and kill a forever running thread
// as the programming is running, type anything in the cmd and hit enter will terminate all threads
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include <time.h>
#include <sys/time.h>

#define myport 3000
#define clientPort 5000

#define total_clients 3

void *PrintHello(void *threadid);

unsigned char play_flag=0;
int main(int argc, char *argv[])
{
	// timer
    struct timeval start, end;


    pthread_t threads[total_clients];
    int rc;
    int i;    
    int start_id = 50;
    int end_id = start_id + total_clients;
    for(i=start_id;i<end_id;i++){
	    rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
        printf("In main: creating thread %d\n", (unsigned int)threads[i]);
    }

    char buff[32]="";
    unsigned char th_id=0;
    play_flag=1;

    while(1)
    {
        fgets(buff,32,stdin);
        th_id = atoi(buff);
        // check if thread is alive
        printf("before kill Thread status: %d\n", (unsigned int)threads[th_id]);
        if(threads[th_id] && pthread_kill(threads[th_id],0) == 0){
            printf("thread[%d] is alive\n",th_id);             
        }
        else{
            printf("thread[%d] is NOT alive\n",th_id); 
        }

        play_flag = th_id;
        printf("killing thread %d\n", th_id); 
        sleep(1);
        if(pthread_kill(threads[th_id],0) == 0){
            printf("thread[%d] is alive\n",th_id);           
        }
        else{
            printf("thread[%d] is NOT alive\n",th_id); 
        }
        printf("after kill Thread status: %d\n", (unsigned int)threads[th_id]);


        if(play_flag == 0) break;
    }
    
	printf("killing all thread \n");
	play_flag=0;


	/* Last thing that main() should do */
	pthread_exit(NULL);
	return 0; /* we never get here */
}

void *PrintHello(void *threadid)
{
    int th_id;
    th_id = (int)threadid;
    printf("thread #%d created\n", th_id);
    while(1){
    	// printf("thread %d running\n",th_id);
        if(play_flag == th_id || play_flag == 0)
        {
            break;
        }
    	// sleep(1);

    }

    printf("===== end thread %d, %d\n",th_id, (unsigned int)pthread_self());
    // pthread_exit(NULL);
}



















