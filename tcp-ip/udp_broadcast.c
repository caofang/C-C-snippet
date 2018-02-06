// udp broadcast server 
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

#define myport 3000
int main(int argc, char *argv[])
{
    int sockfd, portno;
    socklen_t foreign_addr_len;
    struct sockaddr_in my_addr, foreign_addr;

    // sockfd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");

    int my_addr_len = sizeof(my_addr);
    bzero(&my_addr,my_addr_len);

    my_addr.sin_family = AF_INET; // Internet address family 
    my_addr.sin_port = htons(myport);
    my_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    //my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd,(struct sockaddr *)&my_addr,my_addr_len) < 0) perror("binding");
    foreign_addr_len = sizeof(struct sockaddr_in);
    unsigned int packet_counter=0;
    unsigned int loss_counter=0;
    while (1) {
        char client_buffer[1024] = "hello everyone";
        // bzero(client_buffer,strlen(client_buffer));
        
        // printf("receiving...\n");
        // int recv_len = recvfrom(sockfd,client_buffer,1024,0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);
        // packet_counter++;        // printf("total packet: %d\n",packet_counter);
        // if(recv_len != 512) printf("loss: %d\n",loss_counter++);
        // if(packet_counter % 10 == 0) {
        //     printf("packet: %d\n",packet_counter);
        // }

        // printf("meg: %s\n",client_buffer);
        //printf("packet len: %d\n",recv_len);

        int send_len = sendto(sockfd,client_buffer, sizeof(client_buffer),0,(struct sockaddr *)&foreign_addr, foreign_addr_len);
        sleep(1);
        // char str[512];
        // inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), str, INET_ADDRSTRLEN);
        // printf("ip: %s\n", str);
        // printf("Client port: %d\n",ntohs(foreign_addr.sin_port));

    } /* end of while */
    close(sockfd);
return 0; /* we never get here */
}
