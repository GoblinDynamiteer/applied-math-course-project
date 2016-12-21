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
	puts("binary_tests:");
	binary_tests();//-- OK
	puts("\noctal_tests:");
	octal_tests();//-- OK
	puts("\nhexadecimal_tests:");
	hexadecimal_tests();//-- OK
	puts("\nhexadecimal_fraction_tests:");
	hexadecimal_fraction_tests();//-- OK
	puts("\nbinary_fraction_tests:");
	binary_fraction_tests();//-- OK
	
	//Manual tests
	char *converted_number;
	puts("MANUAL CONVERSION");
	while(1){
		int base = 2;
		double dec;
		printf("Enter decimal number and base: ");
		scanf("%lf %d", &dec, &base);
		converted_number = convert_dec_to_base(dec, 10, base);
		printf("%.10f(10) = %s(%d)\n", dec, converted_number, base);
	}
	return 0;
}