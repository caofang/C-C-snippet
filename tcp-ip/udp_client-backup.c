// udp client 
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
    socklen_t my_addr_len, foreign_addr_len;
    struct sockaddr_in my_addr, foreign_addr;

    foreign_addr_len = sizeof(foreign_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) perror("ERROR opening socket");
    // about local 
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(my_port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    int bind_id = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    // about the server
    portno = atoi(argv[2]);
    bzero(&foreign_addr, sizeof(foreign_addr));
    foreign_addr.sin_family = AF_INET;
    foreign_addr.sin_addr.s_addr=inet_addr(argv[1]);
    foreign_addr.sin_port = htons(portno);

    char client_buffer[512] = "";
    int i;
    for (i=0;i<512;i++){
        client_buffer[i] = 'a';
    }
    // bzero(client_buffer,512);
    // strncpy(client_buffer,argv[3],strlen(argv[3]));
    int maxPacket = atoi(argv[3]);
    for (i=0;i<maxPacket;i++){
        int send_len = 
            sendto(sockfd,client_buffer, sizeof(client_buffer),0,(struct sockaddr *)&foreign_addr, sizeof(foreign_addr));
            //printf("send_len: %d",send_len);
            usleep(5000);
        char ser_buffer[1024];
        length = sizeof(foreign_addr);
    }
    // int recv_len = recvfrom(sockfd,ser_buffer,64,0,(struct sockaddr *)&foreign_addr, &length);
    // printf("server msg: %d\n",atoi(ser_buffer));

    char str[512];
    inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), str, INET_ADDRSTRLEN);
    printf("server %s:%d\n", str,ntohs(foreign_addr.sin_port));  
    close(sockfd);
return 0; /* we never get here */
}


