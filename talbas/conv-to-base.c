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

char omvand[256];
char omvand_frac[256];
char rak[256];

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

char get_digit(int digit) {
   if(0 <= digit && digit <= 9) return '0'+digit;
   if(10 <= digit && digit <= 36) return 'A'+digit-10;
   else return '*';
}

//Ombyggd *convert_to_binary
char *convert_to_base(int decimal, int base) {
   int oix, rest;
   oix = 0;
   if(decimal == 0){
		return "0";
	}
   for(decimal; decimal != 0; decimal /= base){
		rest = decimal % base;
		omvand[oix]=get_digit(rest);
		oix++;
	}
   omvand[oix]='\0';
   reverse(omvand);
   return omvand;
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