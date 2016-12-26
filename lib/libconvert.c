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
void vand(char *str){
	//lower / upper index
	int lix, uix = strlen(str)-1;
	char temp;
	for(lix = 0; lix < uix; lix++, uix--){
		temp = str[uix];
		str[uix] = str[lix];
		str[lix] = temp;
	}
}

//Konverterar tal med bas 10 till tal med valfri bas 'base'
char *convert_to_base(int decimal, int base){
	char *omvand = malloc(sizeof(char) * N);
	//oix: omvandling index:
	int t, oix, num;
	oix = 0;
	//Om inkommande tal att omvandla är 0, returneras 0
	if(!decimal){
		omvand[oix] = '0';
		oix++;
	}
	else{
		/* Siffran är resten av delning med talbasen 'base'
		på det decimala talet. */
		for(t = decimal; t != 0; t=t/base){
			num = t % base;
			omvand[oix] = numToChar(num);
			oix++;
		}
	}
	omvand[oix] = '\0';
	//Vänder på tecknen i char-arrayen
	vand(omvand);
	return omvand;
}

//Konverterar decimalt flyttal till tal med basen 'base'
char *convert_to_base_frac(double dec_frac, int max_digits, int base){
	char *base_frac = malloc(sizeof(char) * N);
	//oix: omvandling index:
	int oix = 0, num;
	/* Parameter anses vara i form: 0.##### 
	Därför sätts strängens början till .# 	*/
	base_frac[oix] = '.';
	oix++;
	if(!dec_frac){
		base_frac[oix] = '0';
		oix++;
	}
	else{
		for(dec_frac = dec_frac*base; dec_frac != 0.0 && 
		max_digits > 0; dec_frac=dec_frac*base){
			num = dec_frac;
			dec_frac = dec_frac - num ;
			base_frac[oix] = numToChar(num);
			oix++;
			max_digits--;
		}
	}
	base_frac[oix] = '\0';
	return base_frac;
}

//Konverterar int till char 0-9: 0-9 11+: A+
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

//Konverterar char 0-9: 0-9 : A-Z : 10-36(?)
int charToNum(char num){
	//printf("char->num c: %c", num);
	int n;
	if('0' <= num && num <= '9'){
		//printf(" ( if 0<10 ) ");
		n = num - '0';
	}
	//toupper returnerar versalen av en char
	else if ('A' <= toupper(num) && toupper(num) <= 'Z'){
		//printf(" ( if ABC ) ");
		//A = 10, B = 11 osv.
		n = num - 'A' + 10;
	}
	//printf(" int: %d\n", n);
	return n;
}

/* Använder funktionerna convert_to_base och convert_to_base_frac 
för att konvertera ett flyttal till godtycklig bas 'base' */
char *convert_dec_to_base(double dec_frac, int max_digits, int base){
	char *base_int = malloc(sizeof(char) * N);
	char *base_float = malloc(sizeof(char) * N);
	/* "Plockar ut" heltalet från dec_frac till num, sedan sätts decfrac till 
	0.##### genom att subtrahera num */
	int num = dec_frac;
	printf("convert_dec_to_base: num: %d\n",num);
	dec_frac = dec_frac - num;
	printf("convert_dec_to_base: dec_frac: %lf\n",dec_frac);
	/* Om flyttal, anropas konverteringsfunktion, 
	annars sätts sträng till nolltecken */
	if(dec_frac > 0.0000000000){
		base_float = convert_to_base_frac(dec_frac, max_digits, base);
	}
	else{
		base_float[0] ='\0';
	}
	/* Om inmatat heltal är större än 0, 
	annars sätts sträng till tecken '0' */
	if(num){
		base_int = convert_to_base(num, base);
	}
	else{
		base_int[0] ='0';
		base_int[1] ='\0';
	}
	/* Returnerar sammansatta char-arrayer */
	return strcat(base_int, base_float);
}


char *convert_base_to_base(char *num_input, int max_digits, int base_input, int base_output){
	return "A";
}

//Konverterar tal med basen 'base' till decimalt flyttal
double convert_base_to_dec(char *base_frac, int max_digits, int base){
	char *base_int = malloc(sizeof(char) * N);
	char *base_float = malloc(sizeof(char) * N);
	int string_length = strlen(base_frac);
	//Delar upp strängen till base_int & base_float, vardera sida om eventuellt kommatecken
	int i = 0;
	for(; i < string_length && base_frac[i] != '.'; i++){
		base_int[i] = base_frac[i];
		printf("base[%d] = %c \n", i, base_int[i]);
	}
	base_int[i+1] == '\0';
	int num_int = convert_base_int_to_dec(base_int, base);
	double num_float = 0.0;
	if(base_frac[i++] == '.'){
		int j = 0;
		while(base_frac[i] != '\0'){
			base_float[j] = base_frac[i];
			i++; j++;
		}
		num_float = convert_base_frac_to_dec(base_float, base);
	}
	else{
		base_float[0] = '\0';
	}
	printf("STRINGS: %s   |   %s\n", base_int, base_float);
	return num_int + num_float;
}


int convert_base_int_to_dec(char *base_int, int base){
	int i = strlen(base_int) - 1, power_of = 0;
	int converted = 0;
	for(i; i >= 0; i--){
		converted += charToNum(base_int[i]) * pow(base, power_of);
		power_of++;
	}
	return converted;
}

double convert_base_frac_to_dec(char *base_float, int base){
	int string_length = strlen(base_float), power_of = -1;
	double converted = 0.0;
	for(int i = 0; i < string_length; i++){
		converted += charToNum(base_float[i]) * pow(base, power_of);
		printf("**CONVERTER POW: base: %d pow %d ", base, power_of);
		printf("**CONVERTER FRAC: NUM: %lf\n", converted);
		power_of--;
	}
	return converted;
}

//Gamla funktioner för konvertering från decimaltal till binärt:

//Konverterar dec (int) till binär (char array)
char *convert_to_binary(int decimal){
	char *omvand = malloc(sizeof(char) * N);
	//oix: omvandling index:
	int t, oix;
	oix = 0;
	//Om inkommande tal att omvandla är 0, returneras 0
	if(!decimal){
		omvand[oix] = '0';
		oix++;
	}
	else{
		/* Den binära siffran är resten av delning med 2
		på det decimala talet. */
		for(t = decimal; t != 0; t=t/2){
			if(t%2 == 1){
				omvand[oix] = '1';
			}
			else{
				omvand[oix] = '0';
			}
			oix++;
		}
	}
	omvand[oix] = '\0';
	//Vänder på tecknen i char-arrayen
	vand(omvand);
	return omvand;
}

//Konverterar float (double) till binär (char array)
char *convert_to_binary_frac(double decfloat){
	char *binarfloat = malloc(sizeof(char) * N);
	//oix: omvandling index:
	int oix, counter = 0;
	/* Parameter anses vara i form: 0.##### 
	Därför sätts binära strängens början till 0.#
	*/
	binarfloat[0] = '0';
	binarfloat[1] = '.';
	oix = 2;
	for(decfloat=decfloat*2; decfloat != 0.0 || 
		counter > DECIMALTECKEN; decfloat=decfloat*2){
		if(decfloat >= 1.0){
			decfloat = decfloat - 1.0;
			binarfloat[oix] = '1';
		}
		else{
			binarfloat[oix] = '0';
		}
		oix++;
		counter++;
		if(counter == 20){
			break;
		}
	}
	binarfloat[oix] = '\0';
	return binarfloat;
}

/* Använder funktionerna convert_to_binary_frac & convert_to_binary
för att konvertera ett flyttal i decimalform till ett binärt flyttal */
char *convert_decimal_to_binary(double decimal){
	char *binarD = malloc(sizeof(char) * N);
	char *binarF = malloc(sizeof(char) * N);
	int heltal = decimal;
	decimal = decimal - heltal;
	/* Om flyttal, anropas konverteringsfunktion, 
	annars sätts sträng till nolltecken */
	if(decimal > 0.00000000){
		binarF = convert_to_binary_frac(decimal);
	}
	else{
		binarF[0] ='\0';
	}
	/* Om inmatat heltal är större än 1, 
	annars sätts sträng till tecken 0 */
	if(heltal > 0){
		binarD = convert_to_binary(heltal);
	}
	else{
		binarD[0] ='0';
		binarD[1] ='\0';
	}
	/* Returnerar sammansatta char-arrayer, 
	+1 för att få bort den initiala nollan i strängen binarF */
	return strcat(binarD, binarF+1);
}