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
	Algorithm for converting decimal to any base
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

char *convert_to_base_frac(float dec_frac, int max_digits, int base) {
	int heltal, oix = 1;
	omvand_frac[0] = '.';
	if(dec_frac == 0){
		omvand_frac[oix] = '0';
		oix++;
	}
	else{
		for(dec_frac *= base; dec_frac != 0.0 && max_digits; dec_frac *= base){
			heltal = dec_frac;
			dec_frac -= heltal;
			omvand_frac[oix] = get_digit(heltal);
			max_digits--;
			oix++;
		}
	}
	omvand_frac[oix] = '\0';
	return omvand_frac;
}

char *convert_to_base_both(double dec_frac, int max_digits, int base){
	int heltal = dec_frac;
	double frac = dec_frac - heltal;
	//Globala char arrayer, behöver ej returvärde
	convert_to_base(heltal, base);
	convert_to_base_frac(frac, max_digits, base);
	return strcat(omvand, omvand_frac);
}


#include "tests.h"

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
   //Egen test av sammansatt funktion
   char *returnString;
   returnString = convert_to_base_both(3.141592654, 20, 16);
   printf("PI = %s(16)\n", returnString);
}