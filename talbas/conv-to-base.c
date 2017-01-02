#include <stdio.h>
#include <string.h>

void reverse(char *str) {
   int lix, uix = strlen(str)-1;
   for(lix = 0; lix < uix; lix++, uix--) {
      char temp;
      temp = str[uix];
      str[uix] = str[lix];
      str[lix] = temp;
   }
}

//Global strings, accessible by all functions
char omvand[256]; //for holding integer conversions
char omvand_frac[256]; //for holding >1 conversions
char rak[256]; //Dont know.

//Original dec (base10) to binary conversion function
char *convert_to_binary(int decimal) {
   int oix, t;
   oix = 0;
    if(decimal == 0){
		return "0";
	}
   for(t = decimal; t != 0 && t != '.'; t = t / 2) {
      if(t%2 == 1) {
         omvand[oix]='1';
      }
      else {
         omvand[oix]='0';
      }
      oix++;
   }
   omvand[oix]='\0';
   reverse(omvand);
   return omvand;
}

/* Converts integer to char, for number bases > 10. 
	eg. Hexadecimal A=10, B=11 etc */
char get_digit(int digit) {
   if(0 <= digit && digit <= 9) return '0'+digit;
   if(10 <= digit && digit <= 36) return 'A'+digit-10;
   else return '*';
}

/*
	Algorithm for converting decimal integer to any base
		decimal = decimal number to convert.
		base = the base to convert to (eg 16 for hexadecimal or 2 for binary)
		
		1: Divide decimal by base
		2: The rest (modulus) of decimal is the first digit 
			in the converted base number (right to left!)
		3: Keep the integer part as the new decimal number
		3: Repeat until decimal is zero
		
		Example:
		
		Decimal 77, to Hexadecimal (base 16):
			
			77 / 16 = 4,8125
			
			rest is 0,8125 * 16 = 13
			(this can be done with 77 % 16 in code)
			(77 % 16 = 13)
			
			13 is the rightmost digit
			13 in hexadecimal is 'D'
			
			Decimal is now 4
			
			4 / 16 = 0,25
			rest is 0,25 * 16 = 4
			
			4 is the next digit 
			4 in hexadecimal is 4
			
			Decimal is now 0 and conversion is complete
			Result is: 4D
*/

//Modified 'convert_to_binary', to handle any base
char *convert_to_base(int decimal, int base) {
   int oix, rest; //oix = index for global char array 'omvand'
   oix = 0;
   /*	If input decimal to convert is zero, immediatly return char string "0", 
		this skips the conversion */
   if(decimal == 0){
		return "0"; // string "0"!, not 0.
	}
	/* Conversion alhorithm:
	
	The loop runs while decimal is not zero.
	For each loop decimal is set to decimal divided by base:
		decimal /= base (same as decimal = decimal / base)
	*/
   for(decimal; decimal != 0; decimal /= base){
		/* rest is set to modulus division by base, 
			this is the digit in the converted number. */
		rest = decimal % base;
		/* 'omvand' is the global char array used to store
			converted numbers. Here we set the number in rest
			to the index-place in the string that is oix.
			
			The function get_digit (in this file) converts the
			passed integer to a char. So if the passed integer
			is 7, the function returns the char '7'.
			'A' if 10, 'B' if 11, etc.
		*/
		omvand[oix] = get_digit(rest);
		oix++; //increase index for char-array omvand for each loop.
	}
	//When the algorithm (for-loop) is done, set NULL character in string.
   omvand[oix]='\0';
   /* This function reverses the string, as the for-loop sets chars from left to right. 
		According to the algorithm the chars has to be placed from right to left.
   */
   reverse(omvand);
   return omvand; //Done!
}

/*
	Algorithm for converting decimal float < 1 to any base
		decimal_frac = decimal number to convert.
		base = the base to convert to (eg 16 for hexadecimal or 2 for binary)
		
		1: Multiply decimal_frac by base
		2: The integer part of tha value is the first digit in the converted number
		3: Remove the integer part from decimal_frac
		3: Repeat until decimal_frac is zero, or until max digits has been reached
		
		Example:
		
		decimal_frac 0,6875, to Octal (base 8):
			
			0,6875 * 8 = 5,5
			
			First digit is 5
			
			0,5 * 8 = 4,0
			
			Second digit is 4
			
			decimal_frac is now 0 and conversion is complete
			Result is: 0,54
*/


/*
Converts decimal numbers smaller than 1 to any base */
char *convert_to_base_frac(float dec_frac, int max_digits, int base) {
	int heltal, oix = 1;
	/* Set first index in string to '.', so output will be in format ".12345", 
		hence index oix starts at 1 */
	omvand_frac[0] = '.';
   /*	If input to convert is zero, set char  '0' to string and skip conversion, 
		this skips the conversion */
	if(dec_frac == 0){
		omvand_frac[oix] = '0';
		oix++; //Need to increase to set Null character
	}
	else{
		/* Conversion alhorithm:
		The loop runs while decimal_frac is not zero and max_digits is not zero
		
		For each loop decimal_frac is set to decimal_frac multiplied by base
		dec_frac *= base (same as dec_frac = dec_frac * base)
		
		Note that the loop starts as dec_frac *= base
	*/
		for(dec_frac *= base; dec_frac != 0.0 && max_digits; dec_frac *= base){
			/*	Heltal gets only the integer part of dec_frac	*/
			heltal = dec_frac;
			/*	Remove the integer part from dec_frac, dec_frac is now again < 1	*/
			dec_frac -= heltal;
			/* 'omvand_frac' is the global char array used to store
			converted numbers. Here we set the number in heltal
			to the index-place in the string that is oix.
			
			The function get_digit (in this file) converts the
			passed integer to a char. So if the passed integer
			is 7, the function returns the char '7'.
			'A' if 10, 'B' if 11, etc.
		*/
			omvand_frac[oix] = get_digit(heltal);
			max_digits--; //Decrease by one, for loop will end if this reaches zero
			oix++; //increase index for char-array omvand for each loop.
		}
	}
	omvand_frac[oix] = '\0';
	return omvand_frac;  //Done! - Note that we do not reverse the string in this function
}

/* Uses functions convert_to_base_frac and convert_to_base to convert any decimal number */
char *convert_to_base_both(double dec_frac, int max_digits, int base){
	//Separate int part from float
	int heltal = dec_frac;
	double frac = dec_frac - heltal; //frac is < 1
	//As char arrays are global in this file, i dont use the return value from functions
	convert_to_base(heltal, base);
	convert_to_base_frac(frac, max_digits, base);
	//Return omvand_frac added to end of string omvand.
	return strcat(omvand, omvand_frac);
}

#include "tests.h" //Tests written by teacher TomKi

int main(void) {
   int decimal = 826;
   char *binstr;
   binary_tests();
   octal_tests();
   hexadecimal_tests();
   binary_fraction_tests();
   hexadecimal_fraction_tests();
   char *str1 = strdup(convert_to_base(3, 2));
   char *str2 = strdup(convert_to_base_frac(.141592654, 20, 2));
   printf("PI = %s%s(2)\n", str1, str2);
   char *str3 = strdup(convert_to_base(3, 16));
   char *str4 = strdup(convert_to_base_frac(.141592654, 20, 16));
   printf("PI = %s%s(16)\n", str3, str4);
   //Own test to check "convert_to_base_both"
   char *returnString;
   returnString = convert_to_base_both(3.141592654, 20, 16);
   printf("convert_to_base_both:\nPI = %s(16)\n", returnString);
}