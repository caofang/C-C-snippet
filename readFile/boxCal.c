#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define boxCal_path "files/boxCal.csv"


FILE *boxCal;
int main(int argc, char *argv[]){


	int i,j,a,b,c,x,y,z;
	
	// Open files

	boxCal = fopen(boxCal_path,"r");
	if(boxCal <= 0){
		perror("cannot open file");
		return 0;
	}
	printf("csv file Opened\n");
	
	unsigned char *buff=malloc(16);
	// fgets(buff,16,stdin);

	// get header
	unsigned char *header=malloc(512);
	if(fgets(header,512,boxCal)){
		printf("header: \n%s",header);
	}
	// fgets(buff,16,stdin);

	// get boxCal data
	y=0;
	unsigned char *file_body=malloc(16384);

	while(fgets(file_body,512,boxCal))
	{
		// printf("%d\t%s",y++, file_body);
		printf("line: %d\t%s",y, file_body);

		unsigned char *tmp_tok = strtok (file_body, ",");
		printf("gain:\t%s\n",tmp_tok);
		
		tmp_tok = strtok(NULL, ",");
		printf("delay:\t%s\n",tmp_tok);

		tmp_tok = strtok(NULL, ",");
		printf("SenCell:\t%s\n",tmp_tok);

		tmp_tok = strtok(NULL, ",");
		printf("ohmData:\t%s\n",tmp_tok);

		tmp_tok = strtok(NULL, ",");
		printf("TimeStamp:\t%s\n",tmp_tok);

		tmp_tok = strtok(NULL, ",");
		printf("RawData:\t%s\n",tmp_tok);

		y++;	
	} // fgets

	close(boxCal);
}
















