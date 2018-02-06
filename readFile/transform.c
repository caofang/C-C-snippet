#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define transformation_path "files/transformation.csv"


int main(){
	unsigned char *frame_buf_short_p;
	unsigned char x=0;
	int i,j;
	int sensor_X=64;
	int sensor_Y=32;
	//
	unsigned char dummydata[4096];
	unsigned char *dummydata_p=&dummydata[0];
	unsigned short *dummydata_short_p=(unsigned short *)&dummydata[0];
	for (i=0;i<4096;i++){
		dummydata[i]=x;
		//printf("%u\n",dummydata[i]);
		x++;
	}


	// ==================== load transformation file ================
    unsigned char *file_header;
    int row_a,column_a;
    int row_b,column_b;
    int transform_flag;
    // 1 load transformation file;
    // 2 parse data, [y][x] to [x + y*column] to pointer  
    // 3 transform
    int position_a[16384];
    int position_b[16384];
    int *position_a_p=&position_a[0];
    int *position_b_p=&position_b[0];

    int file_total_ln=0;
    FILE * transfromation_file;

    transfromation_file=fopen(transformation_path,"r");
    if(transfromation_file<0) transform_flag=0;
    else{
        printf("transfromation file opened\n");
        transform_flag = 1;
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        // header
        read = getline(&line, &len, transfromation_file); 
        printf("test\n");

        file_header = strtok(line, ",");
        column_a = atoi(file_header);
        file_header = strtok(NULL, ",");
        row_a = atoi(file_header);

        file_header = strtok(NULL, ",");
        column_b = atoi(file_header);
        file_header = strtok(NULL, ",");
        row_b = atoi(file_header);
        printf("column_a: %d, row_a: %d, column_b: %d, row_b: %d\n",column_a,row_a,column_b,row_b);
        
        position_a[row_a * column_a];
        position_b[row_b * column_b];

        // file data
        char * tmp_buff;
        for (i=0;i<(row_a * column_a);i++){
            read = getline(&line, &len, transfromation_file); 
            //printf("%s\n", line);
            
            tmp_buff=strtok(line,",");
            int x_a = atoi(tmp_buff);
            tmp_buff=strtok(NULL,",");
            int y_a = atoi(tmp_buff);
            position_a[i] = x_a + y_a * column_a;

            tmp_buff=strtok(NULL,",");
            int x_b = atoi(tmp_buff);
            tmp_buff=strtok(NULL,",");
            int y_b = atoi(tmp_buff);
            position_b[i] = x_b + y_b * column_b;
            //printf("%d,%d\n",position_a[i],position_b[i]);
            file_total_ln++;    
        } 
        printf("file length: %d\n",file_total_ln);
    } // check transform_flag
    fclose(transfromation_file);
    unsigned short transformed_frame[sensor_X * sensor_Y];
    unsigned short * transformed_frame_p=&transformed_frame[0];
//________________ load transformation file _____________________

//
}

