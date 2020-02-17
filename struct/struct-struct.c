#include <stdio.h>
#include <string.h>

typedef struct
{
    unsigned char serial[8];
    unsigned char n[4];
    unsigned char delay[8];
    unsigned char l[4];
    unsigned char gain[8];
    unsigned char b[4];
    unsigned char m[4];
    unsigned char z[4];
    unsigned char core_timeout[32];
    unsigned char transformation[32];
    unsigned char sensor_calibration[32];
    unsigned char box_calibration[32];
    unsigned char compression_type[32]; 
    unsigned char device_phy_height[32];
    unsigned char device_phy_width[32];
    unsigned char frameLocation_x[32];
    unsigned char frameLocation_y[32];
    unsigned char frame_height[32];
    unsigned char frame_width[32];
    unsigned char max_pseudo_psi[32];
    unsigned char max_psi[32];
    unsigned char empty_packet_hz[32];
    unsigned char check_frame_delay[32];
    unsigned char send_packet_delay[32];
    unsigned char read_data_timeout[32];
    unsigned char packet_max_size[32];
}ConfigFileName;

typedef struct
{
    unsigned char serial[8];
    unsigned char n[4];
    unsigned char delay[8];
    unsigned char l[4];
    unsigned char gain[8];
    unsigned char b[4];
    unsigned char m[4];
    unsigned char z[4];
    unsigned char core_timeout[4];
    unsigned char transformation[4];
    unsigned char sensor_calibration[4];
    unsigned char box_calibration[4];
    unsigned char compression_type[4]; 
    unsigned char device_phy_height[4];
    unsigned char device_phy_width[4];
    unsigned char frameLocation_x[4];
    unsigned char frameLocation_y[4];
    unsigned char frame_height[4];
    unsigned char frame_width[4];
    unsigned char max_pseudo_psi[4];
    unsigned char max_psi[4];
    unsigned char empty_packet_hz[4];
    unsigned char check_frame_delay[4];
    unsigned char send_packet_delay[4];
    unsigned char read_data_timeout[4];
    unsigned char packet_max_size[4];
}ConfigFileValue;

typedef struct 
{
    ConfigFileName Name;
    ConfigFileValue Value; 
}ConfigFile;

void ConfigFileInit(ConfigFile *myConfieFile)
{
    strcpy((*myConfieFile).Name.serial,"serial");
    strcpy((*myConfieFile).Name.n,"N");
    strcpy((*myConfieFile).Name.delay,"delay");
    strcpy((*myConfieFile).Name.l,"L");
    strcpy((*myConfieFile).Name.gain,"gain");
    strcpy((*myConfieFile).Name.b,"B");
    strcpy((*myConfieFile).Name.m,"M");
    strcpy((*myConfieFile).Name.z,"Z");
    strcpy((*myConfieFile).Name.transformation,"transformation");
    strcpy((*myConfieFile).Name.sensor_calibration,"sensor_calibration");
    strcpy((*myConfieFile).Name.box_calibration,"box_calibration");
    strcpy((*myConfieFile).Name.compression_type,"compression_type");
    strcpy((*myConfieFile).Name.device_phy_height,"device_phy_height");
    strcpy((*myConfieFile).Name.device_phy_width,"device_phy_width");
    strcpy((*myConfieFile).Name.frameLocation_x,"frameLocation_x");
    strcpy((*myConfieFile).Name.frameLocation_y,"frameLocation_y");
    strcpy((*myConfieFile).Name.frame_height,"frame_height");
    strcpy((*myConfieFile).Name.frame_width,"frame_width");
    strcpy((*myConfieFile).Name.max_pseudo_psi,"max_pseudo_psi");
    strcpy((*myConfieFile).Name.max_psi,"max_psi");
    strcpy((*myConfieFile).Name.empty_packet_hz,"empty_packet_hz");
    strcpy((*myConfieFile).Name.check_frame_delay,"check_frame_delay");
    strcpy((*myConfieFile).Name.send_packet_delay,"send_packet_delay");
    strcpy((*myConfieFile).Name.read_data_timeout,"read_data_timeout");
    strcpy((*myConfieFile).Name.packet_max_size,"packet_max_size");
}

int cmd_string_parse(unsigned char *par_name, unsigned char *par_value, unsigned char *cmd)
{
    unsigned char *par_value_start;
    unsigned char *par_value_end;

    par_value_start = strstr(cmd, par_name);
    if(par_value_start == NULL) return 1;
    par_value_end = strstr(par_value_start, "&");

    if(par_value_end == NULL) {
        par_value_start = strstr(par_value_start, "=") + 1; 
        strcpy(par_value,par_value_start);
    }
    else 
    {
        par_value_start = strstr(par_value_start, "=") + 1; 
        int len = par_value_end - par_value_start;
        memcpy(par_value,par_value_start,len);
        memcpy(par_value+len,"\0",1);
    }
    return 0;
}

int main(int argc, char *argv[]) {

    unsigned char cmd[]="gain=r032&x=1";

    ConfigFile myConfieFile;
    ConfigFileInit(&myConfieFile);

    // cmd_iteration(cmd);
    if(!cmd_string_parse(myConfieFile.Name.gain, myConfieFile.Value.gain,cmd))
        printf("myConfieFile: %s\n",myConfieFile.Value.gain);

    if(!cmd_string_parse(myConfieFile.Name.delay, myConfieFile.Value.delay,cmd))
        printf("myConfieFile: %s\n",myConfieFile.Value.delay);


    printf("cmd: %s\n",cmd);
    // printf("myConfieFile: %s\n",myConfieFile.Name.serial);
    // printf("myConfieFile: %s\n",myConfieFile.Name.delay);
    // printf("myConfieFile: %s\n",myConfieFile.Name.l);
    return 0;
}









