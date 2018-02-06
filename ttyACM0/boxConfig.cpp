#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>    // POSIX terminal control definitions


using namespace std;

int main(int argc, char* argv[]){
	struct termios options;
	int rc;

	int fd;
	int ln=0;
	int a,b,c;
	char buff[200];
	int length = 200;

 	for (a=0; a<200; a++){
			buff[a] = 0;
	}

	//===================W/R to the ttyACM========================
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK); 
	// O_RDWR: Open for reading/writing. 
	if(fd>0) {
		// Set the baud rates to 4 000 000
	    cfsetispeed(&options, B4000000);
	    // Set the baud rates to 4 000 000
	    cfsetospeed(&options, B4000000);
	    options.c_cflag &= ~CSTOPB;
	     

		if(argc > 1){
			for(a=1; a<argc; a++){	
				write(fd,argv[a],strlen(argv[a]));// write command 1 to ttyACM0
				usleep(1000);
				ln = read(fd,buff,length);
				if(ln>0){
					buff[ln] = 0;
					cout << buff << endl
						 << "cmd: " << argv[a] << endl
						 << "ln: " << ln << endl;
				}
				else{
					cout << "bad communication" << endl;
				}
			}	  
		}
		else{
			cout << "No command" << endl;	
		}
	}
	close(fd);
	return 0;

}
