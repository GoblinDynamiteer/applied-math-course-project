/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016/2017
https://github.com/GoblinDynamiteer/XmasProject2016

Johan Kämpe 


Code used to test functions in libconvert library
*/

#include <stdio.h>
#include "lib/libconvert.h"
//#include "test/tests.h" /*Modified file*/
#include "test/tests_original.h" /*Original tests from teacher*/

int main(){
	//Tests written by Tomas "Tomki" Kindahl
	puts("TESTS:");
	puts("binary_tests:");
	binary_tests();
	puts("\noctal_tests:");
	octal_tests();//-- OK
	puts("\nhexadecimal_tests:");
	hexadecimal_tests();//-- OK
	puts("\nhexadecimal_fraction_tests:");
	hexadecimal_fraction_tests();//-- Rounding errors?
	puts("\nbinary_fraction_tests:");
	binary_fraction_tests();//-- OK 
	
	//Manual input of number and base, displays a list of conversions from base 2 to 36
	puts("\nMANUAL CONVERSION BASE -> BASE");
	char *converted;
	while(1){
		int base = 2;
		char num[N];
		printf("Enter number & base: ");
		scanf("%s %d", &num, &base);
		printf("\nInput: %s (%d)", num, base);
		//Fancy stuff:
		switch(base){
			case 2:
				printf(" [ binary ] \n");
				break;
			case 8:
				printf(" [ octal ] \n");
				break;
			case 10:
				printf(" [ decimal ] \n");
				break;
			case 16:
				printf(" [ hexadecimal ] \n");
				break;
			default:
				printf("\n");
				break;
		}
		//Output-list of converted  values
		printf("*****************************\n");
		for(int baseOut = 2; baseOut <= 36; baseOut++){
			char *converted;
			converted = convertBaseToBase(num, 10, base, baseOut);
			printf("Base %2d:  %s\n", baseOut, converted);
			//free(converted);
		}
		printf("*****************************\n");
	}
	return 0;
}