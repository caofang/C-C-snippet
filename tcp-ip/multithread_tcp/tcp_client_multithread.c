// udp client connect to server and send() and recv()
// the server and client MUST under the same network to have the proper port
// 
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
#include <netdb.h>

#define my_port 5000
int main(int argc, char *argv[])
{
    int sockfd, length, portno;
    socklen_t addr_len;
    struct sockaddr_in my_addr, foreign_addr;
    addr_len = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");
    // about local 
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(5000);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    int bind_id = bind(sockfd, (struct sockaddr *)&my_addr, addr_len);

    // about the server
    portno = atoi(argv[2]);
    bzero(&foreign_addr, addr_len);
    foreign_addr.sin_family = AF_INET;
    foreign_addr.sin_addr.s_addr=inet_addr(argv[1]);
    foreign_addr.sin_port = htons(portno);

    connect(sockfd, (struct sockaddr *)&foreign_addr,addr_len);
    
    char client_buffer[512] = "";
    // 
    // strncpy(client_buffer,argv[3],strlen(argv[3]));
    char ser_buffer[1024];

    int i;
    for (;;){
        bzero(client_buffer,512);
        printf("type your msg: ");

        fgets(client_buffer,521,stdin);
        int send_len = send(sockfd,client_buffer,strlen(client_buffer),0);
        int recv_len = recv(sockfd,ser_buffer,64,0);
    
        printf("server msg: %s\n",ser_buffer);
        char str[512];
        inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), str, INET_ADDRSTRLEN);
        printf("server: %s:%d\n", str,ntohs(foreign_addr.sin_port));
    }
    
    close(sockfd);
return 0; /* we never get here */
}


