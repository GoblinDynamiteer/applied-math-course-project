/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016/2017

Johan Kämpe 
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Antal tecken för i binära textsträngar
#define N 256

//Antal siffror efter kommatecken, för binära flyttal
#define DECIMALTECKEN 10

void vand(char *str);
char *convert_to_binary(int decimal);
char *convert_to_binary_frac(double decimal);
char *convert_decimal_to_binary(double decimal);
char *convert_to_base(int decimal, int base);
char numToChar(int num);
char *convert_to_base_frac(double dec_frac, int max_digits, int base);
char *convert_dec_to_base(double dec_frac, int max_digits, int base);