#include <stdio.h>
#include "lib/libconvert.h"

//Binary arithmetic using libconvert

int main(){
	printf("Binary arithmetic tests:\n");
	//Binary division
	int decimal1 = 20014, decimal2 = 4;
	char *string1 = convertDecToBase(decimal1, 10, 2);
	char *string2 = convertDecToBase(decimal2, 10, 2);
	printf("%s / ", string1);
	printf("%s = ", string2);
	printf("%s\n", convertDecToBase(decimal1 / decimal2, 10, 2));
	//Binary division, fraction output
	decimal1 = 10;
	decimal2 = 3;
	string1 = convertDecToBase(decimal1, 10, 2);
	string2 = convertDecToBase(decimal2, 10, 2);
	printf("%s / ", string1);
	printf("%s = ", string2);
	printf("%s\n", convertDecToBase((double)decimal1 / (double)decimal2, 10, 2));
	//Binary multiplier
	decimal1 = 127;
	decimal2 = 51;
	string1 = convertDecToBase(decimal1, 10, 2);
	string2 = convertDecToBase(decimal2, 10, 2);
	printf("%s * ", string1);
	printf("%s = ", string2);
	printf("%s\n", convertDecToBase(decimal1 * decimal2, 10, 2));
	//Hexadecimal division
	printf("Hexadecimal arithmetic tests:\n");
	decimal1 = 15236;
	decimal2 = 2749;
	string1 = convertDecToBase(decimal1, 10, 16);
	string2 = convertDecToBase(decimal2, 10, 16);
	printf("%s / ", string1);
	printf("%s = ", string2);
	printf("%s\n", convertDecToBase((double)decimal1 / (double)decimal2, 10, 16));
	printf("Hexadecimal arithmetic tests:\n");
}