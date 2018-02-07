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
    unsigned char *port, *dir,c;   
    sttyConfig(argv[1], argv[2]);
    // ./program -b 50000 -p/dev/ttyACM0
    // while ((c = getopt (argc, argv, "b:d:")) != -1)
    // {
    //     switch (c)
    //     {
    //         case 'b':
    //             strcpy(root_dir,optarg);
    //             break;
    //         case 'd':
    //             strcpy(PORT,optarg);
    //             break;
    //         case '?':
    //             help();
    //             exit(1);
    //         default:
    //             exit(1);
    //     }
    // }
}



