// udp server 
// it sends "go" command to multiple ip address, and receive a 512 packet from them
// helloworld
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

#define total_clients 5

void *PrintHello(void *threadid);

int play_flag;
int main(int argc, char *argv[])
{
    // timer
    struct timeval start, end, start1, end1;
    // socket
    socklen_t foreign_addr_len;
    struct sockaddr_in my_addr, foreign_addr;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    int my_addr_len = sizeof(my_addr);
    bzero(&my_addr,my_addr_len);
    my_addr.sin_family = AF_INET; // Internet address family 
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd,(struct sockaddr *)&my_addr,my_addr_len) < 0) perror("binding");

    // ============== initialization ===========
    char *ip_table[16];
    int ip_counter=0;
    ip_table[0] = "192.168.0.101";
    ip_table[1] = "192.168.0.102";
    ip_table[2] = "192.168.0.103";
    ip_table[3] = "192.168.0.104";
    ip_table[4] = "192.168.0.105";

    bzero(&foreign_addr, sizeof(foreign_addr));
    foreign_addr.sin_family = AF_INET;
    foreign_addr.sin_port = htons(clientPort);
    foreign_addr_len = sizeof(struct sockaddr_in);
    unsigned int packet_counter=0;
    unsigned int loss_counter=0;

    char client_buffer[1024]="";
    for(ip_counter=0;ip_counter<total_clients;ip_counter++){
        foreign_addr.sin_addr.s_addr=inet_addr(ip_table[ip_counter]);
        int send_len = sendto(sockfd,"run", sizeof("run"),0,(struct sockaddr *)&foreign_addr, foreign_addr_len);
        int recv_len = recvfrom(sockfd,client_buffer,64,0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);

        char client_ip[16];
        int client_port;
        inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), client_ip, INET_ADDRSTRLEN);
        client_port = foreign_addr.sin_port;
        printf("Client: %s:%d, msg: %s\n",client_ip,ntohs(foreign_addr.sin_port),client_buffer);

    }
    //______________________________________________________
    

    // ============== listening threads for each client ==================
    int port[total_clients];
    port[0]=3101;
    port[1]=3102;
    port[2]=3103;
    port[3]=3104;
    port[4]=3105;
    int tmp;

    pthread_t threads[total_clients];
    int rc;
    int th_id;
    play_flag=1;
    for(th_id=0;th_id<total_clients;th_id++){
        tmp = port[th_id];
        printf("Creating thread %d\n", th_id);
        rc = pthread_create(&threads[th_id], NULL, PrintHello, (void *)tmp);   
    }

    // terminating thread
    char terminal_buff[32];
    // fgets(terminal_buff,32,stdin);
    play_flag=0;
    // for(th_id=0;th_id<total_clients;th_id++){
    //     printf("terminating thread: %d\n",th_id);
    //     pthread_cancel(threads[th_id]);
    // }
    /* Last thing that main() should do */
    pthread_exit(NULL);
    //_________________________________________________________________
//
    close(sockfd);
return 0;
}

void *PrintHello(void *threadid)
{
    int port;
    port = (int)threadid;
    // timer
    struct timeval start, end;
    // socket
    socklen_t foreign_addr_len;
    struct sockaddr_in my_addr, foreign_addr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    int my_addr_len = sizeof(my_addr);
    bzero(&my_addr,my_addr_len);
    my_addr.sin_family = AF_INET; // Internet address family 
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd,(struct sockaddr *)&my_addr,my_addr_len) < 0) perror("binding");

    char client_ip[16];
    int client_port;

    int count=10000;
    char client_buffer[1024];
    int recv_len = recvfrom(sockfd,client_buffer,512,0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);
    gettimeofday(&start, NULL);
    while(count--){
        // char client_buffer[1024];
        // bzero(client_buffer,strlen(client_buffer));
        recv_len = recvfrom(sockfd,client_buffer,512,0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);
        inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), client_ip, INET_ADDRSTRLEN);
        client_port = ntohs(foreign_addr.sin_port);
        //printf("Client: %s:%d, packet len: %d\n",client_ip,client_port,recv_len);

    }
    gettimeofday(&end, NULL);

    foreign_addr.sin_port=htons(5000);
    int send_len = sendto(sockfd,"kill", sizeof("kill"),0,(struct sockaddr *)&foreign_addr, foreign_addr_len);


    long int duration = ((end.tv_sec * 1000000 + end.tv_usec)-(start.tv_sec * 1000000 + start.tv_usec));
    //printf("thread port: %d\n", port);
    printf("\n%ld ms\n",duration/1000 );
    printf("Client: %s:%d\n",client_ip,client_port);

    pthread_exit(NULL);
}



















