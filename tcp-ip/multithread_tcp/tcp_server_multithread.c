// tcp multithread server 
// helloworld
// listens to a specific address and port
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
#include <sys/time.h>
#include <pthread.h>

// #define myport 5000
#define total_clients 2

void *TaskCode(void *sock);

int main(int argc, char *argv[])
{
    int myport = atoi(argv[1]);
    // struct timeval tv;
    // tv.tv_sec = 2;
    // tv.tv_usec= 0;

    pthread_t threads[total_clients];
    int thread_count=0, thread_result;

    int sockfd, portno;
    socklen_t addr_len;
    struct sockaddr_in my_addr, foreign_addr;
    addr_len = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");

    int my_addr_len = sizeof(my_addr);
    bzero(&my_addr,addr_len);

    // my computer information
    my_addr.sin_family = AF_INET; // Internet address family 
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd,(struct sockaddr *)&my_addr,addr_len) < 0) perror("binding");
    listen(sockfd,5);


    while (1) 
    {
        printf("wait for connection...\n");
        int newsockfd = accept(sockfd, (struct sockaddr *) &foreign_addr, &addr_len);

        // create all threads one by one
        printf("new connection, creating thread %d\n",thread_count++);
        thread_result = 
            pthread_create(&threads[thread_count], NULL, TaskCode, &newsockfd);

    } /* end of while */
    close(sockfd);
return 0; /* we never get here */
}

void *TaskCode(void *sock)
{
    int socket = *((int *) sock);
    char client_buffer[99999];
    bzero(client_buffer,strlen(client_buffer));

    printf("receiving\n");
    int recv_len = recv(socket,client_buffer,99999,0);
    if(recv_len >= 0) printf("%s\n",client_buffer);
    else {
        printf("nothing received \n");
        close(socket);
    }

    int send_len = send(socket,"HTTP/1.0 200 OK\n\n", 17,0);

    // send(socket, "Content-type: text/html\n\n", strlen("Content-type: text/html\n\n"), 0);

    // printf("meg: %s, len: %d\n",client_buffer,recv_len);
    close(socket);
    // exit(0);
}








