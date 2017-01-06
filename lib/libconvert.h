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
#define SMALLNUM 0.0000000000

/* För tester i tests.h - annan namngivning av funktioner */
#define convert_to_binary(n) convertIntDecToBase(n, 2)
#define convert_to_base(n,b) convertIntDecToBase(n, b)
#define convert_to_base_frac(n,m,b) convertFracDecToBase(n, m, b)

void reverseString(char *str);
void stripZeroes(char *str);

char *convertIntDecToBase(int decimal, int base);
char *convertFracDecToBase(double decimal, int maxDigits, int base);
char *convertDecToBase(double decimal, int maxDigits, int base);

double convertBaseToDec(char *number, int base);
int convertIntBaseToDec(char *number, int base);
double convertFracBaseToDec(char *number, int base);

char *convertBaseToBase(char *number, int maxDigits, int baseIn, int baseOut);

char numToChar(int num);
int charToNum(char num);
double powerOf(int base, int i);