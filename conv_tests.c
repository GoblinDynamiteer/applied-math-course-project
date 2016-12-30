/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016/2017

Johan Kämpe 


Code used to test functions in libconvert library
*/

#include <stdio.h>
#include "lib/libconvert.h"
#include "test/tests.h"

int main(){
	puts("\noctal_tests:");
	octal_tests();//-- OK
	puts("\nhexadecimal_tests:");
	hexadecimal_tests();//-- OK
	puts("\nhexadecimal_fraction_tests:");
	hexadecimal_fraction_tests();//-- OK
	puts("\nbinary_fraction_tests:");
	binary_fraction_tests();//-- OK 
	puts("\nhexadecimal_full_tests:");
	hexadecimal_full_tests();
	puts("\ndec_to_dec_tests:");
	dec_to_dec_tests();
	
/* 	puts("powerOf func tests");
	while(1){
		int b, i;
		printf("Enter number, power of: ");
		scanf("%d %d", &b, &i);
		printf("Result: %g\n", powerOf(b,i));
		printf("Result pow(): %g\n", pow(b,i));
	} */
	
	//Manual tests
	char *converted;

	puts("MANUAL CONVERSION BASE -> BASE");
	//http://www.cleavebooks.co.uk/scol/calnumba.htm
	while(1){
		int base = 2;
		char num[N];
		printf("Enter number & base: ");
		scanf("%s %d", &num, &base);
		printf("\nInput: %s (%d)", num, base);
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
		printf("*****************************\n");
		for(int baseOut = 2; baseOut <= 36; baseOut++){
			converted = convertBaseToBase(num, 10, base, baseOut);
			printf("Base %2d:  %s\n", baseOut, converted);
		}
		printf("*****************************\n");
	}
	return 0;
}