#include <stdio.h>
#include "lib/libconvert.h"

//Binary arithmetic using libconvert

int main(){
	//Binary division
	int decimal1 = 20014, decimal2 = 4;
	char *binString1 = convertDecToBase(decimal1, 10, 2);
	char *binString2 = convertDecToBase(decimal2, 10, 2);
	printf("%s / ", binString1);
	printf("%s = ", binString2);
	printf("%s\n", convertDecToBase(decimal1 / decimal2, 10, 2));
	//Binary multiplier
	decimal1 = 127;
	decimal2 = 51;
	binString1 = convertDecToBase(decimal1, 10, 2);
	binString2 = convertDecToBase(decimal2, 10, 2);
	printf("%s * ", binString1);
	printf("%s = ", binString2);
	printf("%s\n", convertDecToBase(decimal1 * decimal2, 10, 2));
	//Binary division, fraction output
	decimal1 = 10;
	decimal2 = 3;
	binString1 = convertDecToBase(decimal1, 10, 2);
	binString2 = convertDecToBase(decimal2, 10, 2);
	printf("%s / ", binString1);
	printf("%s = ", binString2);
	printf("%s\n", convertDecToBase((double)decimal1 / (double)decimal2, 10, 2));
}