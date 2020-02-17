#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

//=============================================================================
int main(int argc, char *argv[]){
	

	unsigned int i,a,b,c;
	char cmd[10];
	char inString[52];
	unsigned char inData[16385],outData[32769];
	int fd;
	int ln=0;
	int loops;
	int frames;
	int BytesRequired,Timeout; 

	// helloworld?cmd=i&bytes=2048&timeout=100
	
//===================================================================================================
	// argv{helloworld, frame,cmd,bytes,timeout,loops}
	frames = atoi(argv[1]);
	// number of frames
	sttyConfig();
	strcpy(cmd, argv[2]);
	BytesRequired = atoi(argv[3]);
	Timeout = atoi(argv[4]);
	loops = atoi(argv[5]);

	struct timeval start, end;
	gettimeofday(&start, NULL);
    long current_sec = start.tv_sec;
	for (c=0; c<frames; c++){
		
		fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK); 
		// O_RDWR: Open for reading/writing. 
		//printf("\n\nFrame: %d\n",c);
		if(fd>0) {
			//printf("\nFrames: %d BytesRequired: %d Timeout: %d \n",frames,BytesRequired,Timeout);			
		
			write(fd,argv[2],strlen(argv[2]));// write command to ttyACM0
//........................................................................................................
//.................Debug..................................................................................	


			ln = 0;
			a=0;
			while(ln < BytesRequired) {
				usleep(Timeout); 
				int ret = read(fd,inData+ln,1024);
				if(ret > 0) ln+=ret;
				//printf("\tln %d; ",ln);
				if(a > loops)  goto StopReading;
				a++;
			}
StopReading:
			//printf("\nloops: %d\n",a);
			close(fd);	
		}
	}
	gettimeofday(&end, NULL);
	long dur = (end.tv_sec-start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000 ;
	printf("duration : %ld\n",dur); 

	return 0;		
}

//---------------------------------------------------------------------------------------------
int sttyConfig(){
	system("stty -F /dev/ttyACM0 cs8 4000000 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");

	return 0;
}


