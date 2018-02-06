// udp server for mex with non-blicking read
// the client side code is on c#
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <sys/ioctl.h>

int sttyConfig(){
    system("stty -F /dev/ttyACM0 cs8 4000000 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");

    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    //sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sockfd < 0) error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    // open ttyACM port
    int fd_ttyACM0;
    sttyConfig();
    fd_ttyACM0 = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(fd_ttyACM0 < 0) error("ERROR opening serial port");
    else printf("ttyACM0 opened\n");

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR on accept");
        int n;
        int ln=0,BytesRequired=50,timeout = 1000;

        int counter=0, counter1=0;

        unsigned char inData[1024];
        char cmd[256];
        bzero(cmd,256);
        printf("before reading\n");
        n = read(newsockfd,cmd,255);
        printf("after reading\n");
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the cmd: %s\n",cmd);

        write(fd_ttyACM0,cmd,strlen(cmd));// write command to ttyACM0, 
        do {
                usleep(timeout); 
                int ln = read(fd_ttyACM0,inData,1024);
                counter += ln;
                n = write(newsockfd,inData,ln);
                counter1 += n;
        }while(ln != 0);

        printf("done\n%d\n%d\n",counter,counter1);
        //n = write(newsockfd,"I got your message",18);
        //if (n < 0) error("ERROR writing to socket");
        //else 
        close(newsockfd);
    } /* end of while */
    close(sockfd);
    close(fd_ttyACM0);
return 0; /* we never get here */
}
