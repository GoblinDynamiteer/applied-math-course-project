#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //for pow (x^-1...n)

int ipow(int bas, int exponent) {
   if(exponent <= 0) return 1;
   return bas*ipow(bas, exponent-1);
}

int ipow_iter(int bas, int exponent) {
   int product = 1;
   while(exponent > 0) {
      product = product * bas;
      exponent--;
   }
   return product;
}

int conv_digit(char ch) {
   if('0'<=ch && ch <='9')
     return ch-48;
   if('A'<=ch && ch <='Z')
     return ch-55;
   if('a'<=ch && ch <='z')
     return ch-55;
   return ch;
}

double convert_to_decimal(char *siffror, int bas) {
	int ix, len = strlen(siffror)-1;
	int isum = 0;
	double fsum = 0.0, frac;
	for(ix = 0; siffror[ix] != '\0' && siffror[ix] != '.'; ix++) {
		int factor = conv_digit(siffror[ix]);
		isum = isum*bas + factor;
/* 		printf("%d: '%c' = %d (%d)\n", len-ix, siffror[ix], 
			conv_digit(siffror[ix]), factor); */
	}
	/* ta hand om ev decimaler här om siffror[ix] == '.' */
	if(siffror[ix++] == '.'){ //make sure to skip past '.', it has a value of 46!
		for(int p = -1; siffror[ix] != '\0'; ix++, p--){
			int factor = conv_digit(siffror[ix]);
			fsum += factor * pow(bas, p);
		}
	}
	return isum+fsum;
}

int main(int argc, char *argv[]) {
   int bas;
   double tal;
   bas = 2;
   tal = convert_to_decimal("11.00100100001111110110", bas);
   printf("%s (bas %d) = %g\n", "11.00100100001111110110", bas, tal);
   bas = 16;
   tal = convert_to_decimal("3.243F6A8", bas);
   printf("%s (bas %d) = %g\n", "3.243F6A8", bas, tal);
/*    tal = convert_to_decimal("1B23A43.243F6A8", bas);
   printf("%s (bas %d) = %g\n", "1B23A43.243F6A8", bas, tal); */
   return 0;
}
