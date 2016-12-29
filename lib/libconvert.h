/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016/2017

Johan Kämpe 
*/

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Antal tecken för textsträngar
#define N 256

//Antal siffror efter kommatecken, för binära flyttal
#define DECIMALTECKEN 10

void vand(char *str);

char *convert_to_base(int decimal, int base);
char *convert_to_base_frac(double dec_frac, int max_digits, int base);
char *convert_dec_to_base(double dec_frac, int max_digits, int base);

double convert_base_to_dec(char *base_frac, int max_digits, int base);
int convert_base_int_to_dec(char *base_int, int base);
double convert_base_frac_to_dec(char *base_float, int base);

char *convert_base_to_base(char *num_input, int max_digits, int base_input, int base_output);

char numToChar(int num);
int charToNum(char num);