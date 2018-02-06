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

int play_flag;
int data;
int main(int argc, char *argv[])
{
	// timer
    struct timeval start, end;


    pthread_t threads[total_clients];
    int rc;
    int i;
    play_flag=1;
    for(i=0;i<total_clients;i++){
	    printf("In main: creating thread %d\n", i);
	    rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
        
    }
    for (data=0;data<4;data++){
    	usleep(1000);
    }
    char buff[32]="";
    fgets(buff,32,stdin);
    
	printf("kill thread \n");
	play_flag=0;
 //    for (i=0;i<total_clients;i++){
	//     pthread_cancel(threads[i]);
	//     sleep(1);
	// }
    


	/* Last thing that main() should do */
	pthread_exit(NULL);
	return 0; /* we never get here */
}

void *PrintHello(void *threadid)
{
    int th_id;
    th_id = (int)threadid;
    printf("thread #%d created\n", th_id);

    while(play_flag){
    	printf("thread %d running, data: %d\n",th_id,data);
    	sleep(1);

    }
    printf("thread ended\n");
    pthread_exit(NULL);
}



















