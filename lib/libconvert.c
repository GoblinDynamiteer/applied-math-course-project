/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016/2017

Johan Kämpe 
*/

#include "libconvert.h"

/* Vänder på en char-array.
Används för konvertering från hela decimala heltal till tal 
med godtycklig bas. */
void reverseString(char *str){
	//lower / upper index
	int lix, uix = strlen(str)-1;
	char temp;
	for(lix = 0; lix < uix; lix++, uix--){
		temp = str[uix];
		str[uix] = str[lix];
		str[lix] = temp;
	}
}

//Konverterar heltalsvärde till enstaka chartecken 0-9: 0-9 11+: A+
char numToChar(int num){
	char c;
	/* ASCII-tecknet '0' har värdet 48, och siffran 0 har 0. 
	För att konvertera talet 0 till tecknet '0', kan man således använda 
	0 + '0'. Osv för 1,2,3 */
	if(0 <= num && num < 10){
		c = num + '0';
	}
	/* För tal över 9 används det versala alfabetet. A-Z
	För att konvertera talet 10 till tecknet 'A', adderas värdet för 'A'
	och sedan subtraheras 10. Således blir 11 = B, 12 = C osv.
	*/
	else{
		c = num + 'A' - 10;
	}
	return c;
}

//Konverterar chartecken till heltalsvärde 0-9: 0-9 : A-Z : 10-36
int charToNum(char num){
	int n;
	if('0' <= num && num <= '9'){
		n = num - '0';
	}
	//toupper returnerar versalen av ett char-tecken.
	else if ('A' <= toupper(num) && toupper(num) <= 'Z'){
		//A = 10, B = 11 osv.
		n = num - 'A' + 10;
	}
	return n;
}

//Konverterar heltal med bas 10 till heltal med valfri talbas
char *convertIntDecToBase(int decimal, int base){
	char *converted = malloc(sizeof(char) * N);
	int i = 0, num; // i: index för char-array converted
	//Om inkommande tal att omvandla är 0, returneras texten '0'
	if(!decimal){
		converted[i] = '0';
		i++;
	}
	else{
		/* Siffran är resten av delning med talbasen 'base'
		på det decimala talet. */
		for(decimal; decimal != 0; decimal /= base){
			num = decimal % base;
			converted[i] = numToChar(num);
			i++;
		}
	}
	converted[i] = '\0';
	//Vänder på tecknen i char-arrayen
	reverseString(converted);
	return converted;
}

//Konverterar decimalt flyttal till tal med basen 'base'
char *convertFracDecToBase(double decimal, int maxDigits, int base){
	char *converted = malloc(sizeof(char) * N);
	int i = 0, num; // i: index för char-array converted
	/* Parameter anses vara i form: 0.##### 
	Därför sätts strängens början till .# 	*/
	converted[i] = '.';
	i++;
	if(!decimal){
		converted[i] = '0';
		i++;
	}
	else{
		for(decimal = decimal * base; decimal != 0.0 && 
		maxDigits; decimal=decimal * base){
			num = decimal;
			decimal = decimal - num ;
			converted[i] = numToChar(num);
			i++;
			maxDigits--;
		}
	}
	converted[i] = '\0';
	return converted;
}

char *convertDecToBase(double decimal, int maxDigits, int base){
	char *baseInt = malloc(sizeof(char) * N);
	char *baseFrac = malloc(sizeof(char) * N);
	/* "Plockar ut" heltalet från decimal till num */
	int num = decimal;
	decimal = decimal - num;
	/* Om flyttal, anropas konverteringsfunktion, 
	annars sätts sträng till nolltecken */
	if(decimal > 0.0000000000){
		baseFrac = convertFracDecToBase(decimal, maxDigits, base);
	}
	else{
		baseFrac[0] ='\0';
	}
	/* Om inmatat heltal är större än 0, 
	annars sätts sträng till tecken '0' */
	if(num){
		baseInt = convertIntDecToBase(num, base);
	}
	else{
		baseInt[0] ='0';
		baseInt[1] ='\0';
	}
	/* Returnerar sammansatta char-arrayer */
	return strcat(baseInt, baseFrac);
}


char *convertBaseToBase(char *number, int maxDigits, int baseIn, int baseOut){
	double convertedDecimal = convertBaseToDec(number, 30, baseIn);
	char *converted = malloc(sizeof(char) * N);
	converted = convertDecToBase(convertedDecimal, maxDigits, baseOut);
	return converted;
}

//Konverterar tal med basen 'base' till decimalt flyttal
double convertBaseToDec(char *number, int maxDigits, int base){
	char *baseInt = malloc(sizeof(char) * N);
	char *baseFrac = malloc(sizeof(char) * N);
	int stringLength = strlen(number);
	//Delar upp strängen till baseInt & baseFrac, vardera sida om eventuellt kommatecken
	int i = 0;
	for(; i < stringLength && number[i] != '.'; i++){
		baseInt[i] = number[i];
	}
	baseInt[i+1] == '\0';
	int convertedInt = convertIntBaseToDec(baseInt, base);
	double convertedFrac = 0.0;
	if(number[i++] == '.'){
		int j = 0;
		while(number[i] != '\0'){
			baseFrac[j] = number[i];
			i++; j++;
		}
		convertedFrac = convertFracBaseToDec(baseFrac, base);
	}
	else{
		baseFrac[0] = '\0';
	}
	return convertedInt + convertedFrac;
}


int convertIntBaseToDec(char *number, int base){
	int i = strlen(number) - 1, powerOf = 0;
	int converted = 0;
	for(i; i >= 0; i--){
		converted += charToNum(number[i]) * pow(base, powerOf);
		powerOf++;
	}
	return converted;
}

double convertFracBaseToDec(char *number, int base){
	int stringLength = strlen(number), powerOf = -1;
	double converted = 0.0;
	for(int i = 0; i < stringLength; i++){
		converted += charToNum(number[i]) * pow(base, powerOf);
		powerOf--;
	}
	return converted;
}
