#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

//#define path "files/raw.csv"
//#define path "files/test.csv"
#define path "files/rawTest.csv"

FILE *calibration;
int main(int argc, char *argv[]){
	char text[16384];
	char *tmp_tok;
	int row,column;
	int i,j,a,b,c,x,y,z;
	

	row=9;
	column=2048;
	unsigned int psi[]={0,2,4,6,8,10,15,20,30};
	unsigned int rawValues[row][column];
	unsigned int slope[row-1][column];

	// open file and load to buffer
	calibration = fopen(path,"r");
	if(calibration <= 0){
		perror("cannot open file");
		return 0;
	}
	printf("csv file Opened\n");
	// get header
	if(fgets(text,8192,calibration)){
		//printf("header: %s\n",text);

	}
	// get calibration data
	y=0;
	while(fgets(text,10240,calibration)){
		//printf("%s\n",text);
		// parse csv group them to array
		//printf("row: %d\n",y);
		tmp_tok = strtok (text,",");
		x=0;
		while(tmp_tok){
			//printf("\tcolumn:%d,%s\n",column,tmp_tok);
			rawValues[y][x++] = atoi(tmp_tok);
			tmp_tok = strtok(NULL, ",");
		} // tmp_tok
		y++;	
	} // fgets
	// calculate the slope of each rawValues[][]
	printf("%s\n", "slope");
	for(y=0; y<row-1; y++){
		for(x=0; x<column; x++){
			slope[y][x] = (int)(((double)(psi[y+1] - psi[y]))/(rawValues[y+1][x]-rawValues[y][x]) * 4096);
			//printf("%f",psi[y][x]);		
		}
		printf("%d\t\n",psi[y]);
	}
	printf("\n\n%d,%d\t,%d\n",rawValues[0][0],rawValues[1][0],slope[0][0]);
	printf("%f\n",((double)(psi[1]-psi[0]))/(rawValues[1][0]-rawValues[0][0])*4096);
	
	printf("done\n");

	close(calibration);
}