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



/*
{
    "signature":"MX", 
    "serial":"1234",
    "firmware":25,
    "i":"WizData Systems, MeasureX. Version 6.03. S/N: 1234",
    "data_pcb":"N=4 D=0.4 L=0.1 R=8 B=1 M=19  Z=0 OFF",
    "core_error":0,
    "usb_error":0,
    "compression_flag":1, 
    "sensor_calibration":1,
    "box_calibration":0,
    "transformation":1,
    "sensor_x":64,
    "sensor_y":32,
    "sensor_length":19,
    "sensor_width":38
}
*/

typedef struct
{
    unsigned char signature[3];
    unsigned char serial[5];
    unsigned short firmware;

}myStatus_data;

typedef struct
{
    unsigned char signature[16];
    unsigned char serial[16];
    unsigned char firmware[16];
}myStatus_name;

typedef struct
{
    myStatus_data data;
    myStatus_name name;

}my_status;

int main(int argc, char const *argv[])
{
    int i,j;
    unsigned char str_json[512] = "{\n"
    "\"signature\":\"MX\",\n" 
    "\"serial\":\"1234\",\n"
    "\"firmware\":25\n"
    "}";
    printf("%s\n", str_json);
    // for(i=0;i<strlen(str_json);i++)
    // {
    //     printf("%d, %x, %c\n",i,str_json[i],str_json[i]);
    // }

    unsigned char json_str[512];
    unsigned char tmp_str[32];

    my_status myStatus;
    // data
    strcpy(myStatus.data.signature, "MX");
    strcpy(myStatus.data.serial, "1234");
    myStatus.data.firmware=25;
    // name
    strcpy(myStatus.name.signature, "signature");
    strcpy(myStatus.name.serial, "serial");
    strcpy(myStatus.name.firmware, "firmware");

    // prepare json string 
    strcpy(json_str,"{\"");
    strcat(json_str, myStatus.name.signature);
    strcat(json_str,"\":\"");
    strcat(json_str, myStatus.data.signature);
    strcat(json_str,"\",\n");

    strcat(json_str,"\"");
    strcat(json_str, myStatus.name.serial);
    strcat(json_str,"\":\"");
    strcat(json_str, myStatus.data.serial);
    strcat(json_str,"\",\n");

    strcat(json_str,"\"");
    strcat(json_str, myStatus.name.serial);
    strcat(json_str,"\":\"");
    sprintf(tmp_str, "%d", myStatus.data.firmware);
    strcat(json_str, tmp_str);
    strcat(json_str,"\"}");

    for(i=0;i<strlen(json_str);i++) 
    {
        printf("%d, %x, %c\n",i,json_str[i],json_str[i] );
    }


    printf("%s\n", json_str);


    // printf("size: %d, %d, %d\n", 
    //     sizeof(myStatus), 
    //     sizeof(myStatus.data), 
    //     sizeof(myStatus.name));
    // unsigned char *struct_char;
    // struct_char = (unsigned char *)&myStatus;
    // for (i=0;i<sizeof(myStatus);i++)
    // {
    //     printf("%d, %x, %c\n",i,*(struct_char+i),*(struct_char+i));
    // }

    
    return 0;
}












