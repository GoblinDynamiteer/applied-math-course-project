#include "liboutput.h"
#include "libconvert.h"

/* Outputs a binary string to 
#### #### ####.#### ### format */
void printBinaryString(char *binString){
	int stringLen = 0;
	for(int i = 0; binString[i] != '.' && binString[i] != '\0'; i++){
		stringLen++;
	}
	int addZeroes = 4 - stringLen % 4;
	int counter = addZeroes;
	while(addZeroes && addZeroes != 4){
		printf("0");
		addZeroes--;
	}
	int i = 0, halt = 0;
	while(binString[i] != '\0'){
		printf("%c", binString[i]);
		if(binString[i+1] == '.'){
			halt = 4;
			counter--;
		}
		i++;
		if(!halt){
			counter++;
			if(counter % 4 == 0){
				printf(" ");
			}
		}
		else{
			halt--;
		}
	}
}