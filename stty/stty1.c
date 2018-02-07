#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void help()
{
    printf("-b\tbaud\n");
    printf("-d\tdirectory\n");
}
int sttyConfig(unsigned char *port, unsigned char *baud){
    unsigned char *config_par_1;
    unsigned char *config_par_2;
    
    // port = "/dev/ttyACM0";
    config_par_1 = "stty -F ";
    config_par_2 = " cs8 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts";

    unsigned char cmd[256];
    strcpy(cmd,config_par_1);
    strcat(cmd, port); 
    strcat(cmd, " "); 
    strcat(cmd, baud); 
    // printf("%s\n",cmd);

    strcat(cmd,config_par_2);
    printf("%s\n",cmd);

    system(cmd);
    return 0;
}

int main(int argc, char *argv[])
{
    //unsigned char *port, *dir,c;

    //sttyConfig(argv[1], argv[2]);

    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK); 
    // O_RDWR: Open for reading/writing. 

    char str[] = "aw0500w0600w2129";
    char tmp[4];
    fgets(tmp,4,stdin);
    int c=10000;
    if(fd>0) {

        //write(fd,"a\r\n",strlen("d128\r\n"));
        while(c--)
        {
            write(fd,"d128\r\n",strlen("d128\r\n"));// write command to ttyACM0, 
            usleep(1000); // n us delay     
        }
        close(fd);  
    }
}



