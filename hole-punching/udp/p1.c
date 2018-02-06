#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <netdb.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#include <errno.h>
#include <arpa/inet.h>
#include <time.h> 
#include <signal.h>
#include <sys/wait.h>


void *listening(void *thread_arg);
int main(int argc, char *argv[])
{
    int my_port = atoi(argv[1]);
    printf("local port: %s\n", argv[1]);

    unsigned char client_ip[16];
    unsigned short client_port;
    unsigned char client_msg[512];
    unsigned char my_msg[512];
    bzero(client_msg, sizeof(client_msg));

    //===== socket =====
        int sockfd, send_len, recv_len;
        sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        // address and port
        socklen_t my_addr_len, foreign_addr_len;
        struct sockaddr_in my_addr, foreign_addr;
        foreign_addr_len = sizeof(foreign_addr);
        if (sockfd < 0) perror("ERROR opening socket");
        // about local 
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(my_port);
        my_addr.sin_addr.s_addr = INADDR_ANY;
        int bind_id = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

        // listening thread
        pthread_t threads;
        int rc = pthread_create(&threads, NULL, listening, (void *)sockfd);
    //_____ socket _____

    //===== running =====
        // 67.250.69.24 5000 ubuntu
        unsigned char cli_in[512];
        unsigned char target_ip[16];
        unsigned short target_port;
        while(1){
            bzero(cli_in, sizeof(client_ip));
            printf("\nenter \"192.168.xxx.xxx:8000\nhello\"\n");
            fgets(cli_in,128, stdin);
            fgets(my_msg, 512, stdin);
            strcpy(target_ip, strtok(cli_in, ":"));
            target_port = atoi(strtok(NULL, ":"));
            // strcpy(my_msg,strtok(NULL, " "));

            foreign_addr.sin_family = AF_INET;
            foreign_addr.sin_addr.s_addr=inet_addr(target_ip);
            foreign_addr.sin_port = htons(target_port);
                    
            send_len = sendto(sockfd, my_msg, strlen(my_msg), 0 ,(struct sockaddr *)&foreign_addr, sizeof(foreign_addr));
            printf("sent: %d, target: %s:%d, msg: %s\n",
                send_len, target_ip, target_port, my_msg);
        }
    //_____ running _____
}

void *listening(void *thread_arg)
{
    int sockfd = (int) thread_arg;
    unsigned char client_ip[16];
    unsigned short client_port;
    unsigned char client_msg[512];
    unsigned char my_msg[512];
    bzero(client_msg, sizeof(client_msg));

    int recv_len;
    socklen_t foreign_addr_len;
    struct sockaddr_in foreign_addr;
    foreign_addr_len = sizeof(foreign_addr);

    //===== running =====
    while(1){
        bzero(client_msg, sizeof(client_msg));
        bzero(my_msg, sizeof(my_msg));
        recv_len = recvfrom(sockfd,client_msg, sizeof(client_msg),0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);
        printf("new packet\n");
        // get client ip and port
        inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), client_ip, INET_ADDRSTRLEN);
        client_port = ntohs(foreign_addr.sin_port);
        printf("client:\nip: %s\nport:%d\nmsg: %s\n",client_ip, client_port, client_msg);
        
        // strcpy(my_msg, client_msg);
        // send_len = sendto(sockfd, my_msg, strlen(my_msg), 0 ,(struct sockaddr *)&foreign_addr, sizeof(foreign_addr));
    }
    //_____ running _____
}