/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/ioctl.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   int sockfd, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char cmd_buffer[1024];


    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }    
   
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) error("Opening socket");

    length = sizeof(server);
    bzero(&server,length);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(atoi(argv[1]));
    if (bind(sockfd,(struct sockaddr *)&server,length)<0) 
        error("binding");
    fromlen = sizeof(struct sockaddr_in);

    // Test if the socket is in non-blocking mode:
    if(fcntl(sockfd, F_GETFL) & O_NONBLOCK) {
        // socket is non-blocking
        printf("non-blocking\n");
    }
    
    // Put the socket in non-blocking mode:
    //fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);
    if(fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK) < 0) {
        // handle error
        printf("non-blocking error\n");
    }
    
    printf("test\n");
    int play=0;
    while (1) {
        n = recvfrom(sockfd,cmd_buffer,1024,0,(struct sockaddr *)&from,&fromlen);
        play = atoi(cmd_buffer);
        while(play>0){
            // communicate with ttyACM0, and send to Mex
            n = sendto(sockfd,"Got your message\n",17, 0,(struct sockaddr *)&from,fromlen);
            n = recvfrom(sockfd,cmd_buffer,1024,0,(struct sockaddr *)&from,&fromlen);
            play = atoi(cmd_buffer);
            printf("playing\n");
            /*
                ...
            */

        }
        printf("not playing\n");
    } // end while(1)
    return 0;
}
