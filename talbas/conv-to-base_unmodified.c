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
char rak[256];

char *convert_to_binary(int decimal) {
   int oix, t;
   oix = 0;
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

char *convert_to_base(int decimal, int base) {
   return "(stump)";
}

char *convert_to_base_frac(float dec_frac, int max_digits, int base) {
   return "(stump)";
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
}