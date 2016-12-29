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
	
	//Manual tests
	char *converted_number;
	double  converted_number2;
	puts("MANUAL CONVERSION BASE -> BASE");

	//HEX 3A = OCT 72
	while(1){
		int base = 2, base2 = 3;
		char num[N];
		printf("Enter number | base-in | base-out: ");
		scanf("%s %d %d", &num, &base, &base2);
		converted_number = convertBaseToBase(num, 10, base, base2);
		printf("%s(%d) = %s(%d)\n", num, base, converted_number, base2);
	}
	return 0;
}