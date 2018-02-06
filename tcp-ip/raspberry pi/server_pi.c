/* TCP server running on Raspbrry Pi
    
    run server: 
        /usr/tcpip server_pi 7000

    run client: ./client_pi server_pi 7000

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    char str[INET_ADDRSTRLEN];    

    if (argc < 2) {
     fprintf(stderr,"ERROR, no port provided\n");
     exit(1);
    }    
    //bzero((char *) &serv_addr, sizeof(serv_addr));
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // create the socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    // bind socket with ip and port
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    printf("server addr: %u\n",serv_addr.sin_addr.s_addr);

    listen(sockfd,5);

    clilen = sizeof(cli_addr);
    // establish connection; blocking code
    while(1){
        printf("before accept\n");
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR on accept");
        printf("connection made\n");
        // store this IP address in sa:
        //inet_pton(AF_INET, INADDR_ANY, &(serv_addr.sin_addr));
        // now get it back and print it
        inet_ntop(AF_INET, &(cli_addr.sin_addr.s_addr), str, INET_ADDRSTRLEN);
        printf("cln addr: %s\n", str); // prints "client ip"

        /*
        printf("%d.%d.%d.%d\n", 
            (int)(cli_addr.sin_addr.s_addr&0xFF),
            (int)((cli_addr.sin_addr.s_addr&0xFF00)>>8),
            (int)((cli_addr.sin_addr.s_addr&0xFF0000)>>16),
            (int)((cli_addr.sin_addr.s_addr&0xFF000000)>>24));
        */
        
        
        bzero(buffer,256);
        printf("before read\n");
        n = read(newsockfd,buffer,255);
        printf("Here is the message: %s\n",buffer);
        if(buffer == "stop") 
        n = write(newsockfd,"I got your message",18);
        if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}