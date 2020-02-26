// udp

// last update: see in main()
// circular buffer for shared memory applied for better sync
// support config file /etc/config/se_config_file
/*
    this code is to communicate with the mex box, and get data
    apply transformation and calibration and compression
    and then put the data onto a shared memory

    udp client 
    the server and client must under the same network to have the proper port
    program_name
    with timestamp
    instructions:
        e1: echo
            return the echo message to the sending port 
        s0: stream
            format: s0:listening_port:time_ms:timeout_sec(optional)  all in ascii
            stream processed data to listening_port,
            return s0 to sending port if succeed,
            return error to sending if failed
        s2: same as s0, (v25)
            stream raw data to listening_port

        t1: terminate single streaming
            return t1 to sending port
        t2: terminate all streaming
            return t2 to sending port
        a1: core_timeout,
            format: a1:timeout_sec(optional)
            after sending s0 with timeout, keep sending a1 to update timeout
            otherwise, it will stop streaming in timeout_sec  
*/

        // TODO : endian swap in functions

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>


typedef struct
{
    unsigned char signature[3];
    unsigned char serial[5];
    unsigned short firmware;
    unsigned char i_str[128];
    unsigned char data_pcb_str[128];
    unsigned char n[8];
    unsigned char delay[8];
    unsigned char l[8];
    unsigned char gain[8];
    unsigned char b[4];
    unsigned char m[4];
    unsigned char z[4];
    unsigned long core_time;
    unsigned char error;
    unsigned char transform_flag;
    unsigned char sensorCal_flag;
    unsigned char boxCal_flag;
    unsigned char compression_type; 
    unsigned short device_data_height;
    unsigned short device_data_width;
    int device_phy_height;
    int device_phy_width;
    unsigned short frameLocation_x;
    unsigned short frameLocation_y;
    unsigned short frame_height;
    unsigned short frame_width;
    unsigned short max_pseudo_psi;
    int max_psi;
    unsigned long core_timeout;
    uint8_t additional_error_code;
}Status;
//------------------------------------------------------------------------------

void LOG(int i)
{
    printf("%d\n", i);
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    unsigned char *myStatus_json;

    Status *status = malloc(1024);
    strcpy((*status).signature,"MX");
    strcpy((*status).serial,"000");
    status->firmware = 33;
    strcpy(status->i_str,"iiiii");
    strcpy(status->data_pcb_str,"dddd");
    strcpy(status->n,"n0004");
    strcpy(status->delay,"d004");
    strcpy(status->l,"l001");
    strcpy(status->gain,"r008");
    strcpy(status->b,"b1");
    strcpy(status->m,"m19");
    strcpy(status->z,"z1");
    status->error = 0;
    status->transform_flag = 1;
    status->sensorCal_flag = 1;
    status->boxCal_flag = 0;
    status->compression_type = 1;
    status->device_data_height = 32;
    status->device_data_width = 64;
    status->device_phy_height = 32;
    status->device_phy_width = 64;
    status->frameLocation_x = 0;
    status->frameLocation_y = 0;
    status->frame_height = 32;
    status->frame_width = 64;
    status->max_pseudo_psi = 255;
    status->max_psi = 30;

// =============== json, status =============== 
    // Creating a json object

    json_object * core_status_json = json_object_new_object();
    json_object * data_pcb_obj = json_object_new_object();
    json_object * core_obj = json_object_new_object();
    json_object * device_obj = json_object_new_object();
    json_object * frame_obj = json_object_new_object();

    json_object_object_add(core_status_json,"signature", json_object_new_string((*status).signature));
    json_object_object_add(core_status_json,"serial", json_object_new_string((*status).serial));
    json_object_object_add(core_status_json,"firmware", json_object_new_int((*status).firmware));
    json_object_object_add(data_pcb_obj,"i", json_object_new_string((*status).i_str));
    json_object_object_add(data_pcb_obj,"status", json_object_new_string((*status).data_pcb_str));
    json_object_object_add(data_pcb_obj,"n", json_object_new_string((*status).n));
    json_object_object_add(data_pcb_obj,"delay", json_object_new_string((*status).delay));
    json_object_object_add(data_pcb_obj,"l", json_object_new_string((*status).l));
    json_object_object_add(data_pcb_obj,"gain", json_object_new_string((*status).gain));
    json_object_object_add(data_pcb_obj,"b", json_object_new_string((*status).b));
    json_object_object_add(data_pcb_obj,"m", json_object_new_string((*status).m));
    json_object_object_add(data_pcb_obj,"z", json_object_new_string((*status).z));
    json_object_object_add(core_status_json,"data_pcb", data_pcb_obj);
    json_object_object_add(core_obj,"running", json_object_new_int(0)); // default core is not running, will update later
    json_object_object_add(core_obj,"error", json_object_new_int((*status).error));
    json_object_object_add(core_status_json,"core", core_obj);
    json_object_object_add(core_status_json,"transform_flag", json_object_new_int((*status).transform_flag));
    json_object_object_add(core_status_json,"sensorCal_flag", json_object_new_int((*status).sensorCal_flag));
    json_object_object_add(core_status_json,"boxCal_flag", json_object_new_int((*status).boxCal_flag));
    json_object_object_add(core_status_json,"compression_type", json_object_new_int((*status).compression_type));
    json_object_object_add(device_obj,"data_height", json_object_new_int((*status).device_data_height));
    json_object_object_add(device_obj,"data_width", json_object_new_int((*status).device_data_width));
    json_object_object_add(device_obj,"phy_height", json_object_new_double((*status).device_phy_height));
    json_object_object_add(device_obj,"phy_width", json_object_new_double((*status).device_phy_width));
    json_object_object_add(core_status_json,"device",device_obj);
    json_object_object_add(frame_obj,"location_x", json_object_new_int((*status).frameLocation_x));
    json_object_object_add(frame_obj,"location_y", json_object_new_int((*status).frameLocation_y));
    json_object_object_add(frame_obj,"height", json_object_new_int((*status).frame_height));
    json_object_object_add(frame_obj,"width", json_object_new_int((*status).frame_width));
    json_object_object_add(core_status_json,"frame",frame_obj);
    json_object_object_add(core_status_json,"max_pseudo_psi", json_object_new_int((*status).max_pseudo_psi));
    json_object_object_add(core_status_json,"max_psi", json_object_new_int((*status).max_psi));
    

    printf ("%s\n", json_object_to_json_string(core_status_json));
// _______________ json, status _______________

}