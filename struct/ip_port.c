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

#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#include <errno.h>
#include <arpa/inet.h>
#include <time.h> 
#include <signal.h>
#include <sys/wait.h>

#define max_cli 8
#define my_port 5000

struct client_table
{
    unsigned char ip[16];
    unsigned short port;
    unsigned short des_port;
    unsigned long start_ms;
    unsigned char stream_mode[2];
    unsigned char active;
}cli[max_cli];

int main(unsigned int argc, unsigned short *argv[])
{
	int i,j;
	unsigned char client_ip[16];
	unsigned short	client_cmd_port;
	unsigned char cient_cmd_buff[64];


// ===== socket =====
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
// _____ socket _____ 

	printf("size: %d\n", sizeof(cli));
    bzero(cli, sizeof(cli));

// ===== data =====

	strcpy(cli[0].ip,"192.168.1.1");
	strcpy(cli[1].ip,"192.168.1.2");
	strcpy(cli[2].ip,"192.168.1.3");
	strcpy(cli[3].ip,"192.168.1.4");
	strcpy(cli[4].ip,"192.168.1.5");

	cli[0].port = 10000;	
	cli[1].port = 10001;
	cli[2].port = 10002;
	cli[3].port = 10003;
	cli[4].port = 10004;

	cli[0].active = 1;	
	cli[1].active = 1;
	cli[2].active = 1;
	cli[3].active = 1;
	cli[4].active = 1;
// _____ data _____

	unsigned char newFlag=0;
	for(;;)
    {
    	// check database 
    	printf("check \n");
    	newFlag = 0;
    	bzero(cient_cmd_buff,128);
        int recv_len = recvfrom(sockfd,cient_cmd_buff,64,0,(struct sockaddr *)&foreign_addr, &foreign_addr_len);
        inet_ntop(AF_INET, &(foreign_addr.sin_addr.s_addr), client_ip, INET_ADDRSTRLEN);
        client_cmd_port = ntohs(foreign_addr.sin_port);
        printf("msg received from %s:%d\n",client_ip, client_cmd_port);
	    // scanf("%s %hd",client_ip, &client_cmd_port);
	    for(i=0;i<max_cli;i++)
	    {
	    	// printf("comparing cli[%d]\t%s:%d\n",i , cli[i].ip, cli[i].port);
		    // if(!strcmp(cli[i].ip,client_ip) && (cli[i].port == client_cmd_port))
		    if(cli[i].active == 0) 
	    	{
				newFlag=1;
				printf("FOUND MATCH, cli[%d]\t%s:%d == %s:%d\n",i,cli[i].ip,cli[i].port, client_ip,client_cmd_port);
				break;
			}
			else
			{
				newFlag=0;
				if(strlen(cli[i].ip) == 0) break;
	    		// printf("don't match, keep checking\n");
	    		continue;
			}
		}
		if(newFlag == 0)
		{ 
			printf("NEW ENTRY, cli[%d]\t%s:%d\n",i,client_ip,client_cmd_port);
			strcpy(cli[i].ip,client_ip);
			cli[i].port = client_cmd_port;

		}
		int send_len = sendto(sockfd,"hello", strlen("hello"),0,(struct sockaddr *)&foreign_addr, sizeof(foreign_addr));
	}


	// for(i=0;i<max_cli;i++)
 //    {
	//     printf("cli[%d]:\n%s\n",i,cli[i].ip);
	// }

	close(sockfd); 
    return 0;
}