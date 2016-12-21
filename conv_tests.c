/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016

Johan Kämpe 


Code used to test functions in libconvert library
*/

#include <stdio.h>
#include "lib/libconvert.h"
#include "test/tests.h"

int main(){
	//binary_tests(); -- OK
	char *converted_base_n;
	 
	 //Test base 16 -- Shall be 2AE05  -- OK!
	converted_base_n = convert_to_base(175621, 16);
	puts(converted_base_n);
	
	return 0;
}