#include <errno.h>      // Error number definitions
#include <stdint.h>     // C99 fixed data types
#include <stdio.h>      // Standard input/output definitions
#include <stdlib.h>     // C standard library
#include <string.h>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions

// Open usb-serial port for reading & writing
int open_port(void){

    int fd;    // File descriptor for the port
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    if (fd == -1){
        fprintf(stderr, "open_port: Unable to open /dev/ttyACM0 %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    return fd;
}

int main(int argc, char *argv[]){

    int              fd = 0;     // File descriptor
    struct termios   options;    // Terminal options
    int              rc;         // Return value

    fd = open_port();            // Open tty device for RD and WR

    // Get the current options for the port
    if((rc = tcgetattr(fd, &options)) < 0){
        fprintf(stderr, "failed to get attr: %d, %s\n", fd, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Set the baud rates to 230400
    cfsetispeed(&options, B4000000);

    // Set the baud rates to 230400
    cfsetospeed(&options, B4000000);

    cfmakeraw(&options);
    options.c_cflag |= (CLOCAL | CREAD);   // Enable the receiver and set local mode
    options.c_cflag &= ~CSTOPB;            // 1 stop bit
    options.c_cflag &= ~CRTSCTS;           // Disable hardware flow control
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 2;

    // Set the new attributes
    if((rc = tcsetattr(fd, TCSANOW, &options)) < 0){
        fprintf(stderr, "failed to set attr: %d, %s\n", fd, strerror(errno));
        exit(EXIT_FAILURE);
    }

    ////////////////////////////////
        // Simple Read/Write Code Here//
        
        ////////////////////////////////

    // Close file descriptor & exit
    close(fd);
    return EXIT_SUCCESS;
}