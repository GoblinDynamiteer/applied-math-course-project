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

/* Plockar bort nollor högerifrån i en sträng.
	Används för att t.ex. konvertera 0.23100 -> 0.231 */
void stripZeroes(char *str){
	int i = strlen(str) - 1;
	if(str[i] == '0'){
		while(str[i-1] == '0'){
			i--;
		}
		str[i] = '\0';
	}
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

/* Konverterar decimaltal < 1 'decimal' till tal med talbas 'base' */
char *convertFracDecToBase(double decimal, int maxDigits, int base){
	char *converted = malloc(sizeof(char) * N);
	int i = 1, num; // i: index för char-array 'converted'
	/* Funktionens returvärde ska vara i form: '.XXXX'
		Därför sätts strängens början till '.' och index börjar på 1	*/
	converted[0] = '.';
	/* Om 'decimal' är 0, sätts textsträngen 'converted' till tecknet '0' och
		loop för omvandling till annan talbas hoppas över. */
	if(!decimal){
		converted[i] = '0';
		i++; //För att sätta nolltecken
	}
	/* Algoritm för konvertering av decimala tal < 0 till talbas 'base':
			-	Multiplicera det decimala talet med 'base'
			-	Heltalsvärdet innan kommatecken är den första 
				siffran i det konverterade värdet
			-	Subtrahera heltalsvärdet från det multiplicerade värdet
			-	Börja om med steg 1, tills det multiplicerade värdet är 0 */
	else{
		for(decimal *= base; decimal != SMALLNUM && maxDigits; decimal *= base){
			/*	'num' är av typen int och kan enbart hålla heltalsdelen av 'decimal' */
			num = decimal;
			decimal = decimal - num;
			converted[i] = numToChar(num);
			i++;
			/*	'maxDigits' anger hur många siffror det konverterade värdet ska ha,
				i fall det inte går jämnt ut eller är stort */
			maxDigits--;
		}
	}
	converted[i] = '\0';
	return converted;
}

/* Konverterar decimaltal 'decimal' till tal med talbas 'base' */
char *convertDecToBase(double decimal, int maxDigits, int base){
	char *baseInt = malloc(sizeof(char) * N);
	char *baseFrac = malloc(sizeof(char) * N);
	/* "Plockar ut" heltalet från decimal till num */
	int num = (int)decimal;
	decimal = decimal - num;
	/* Om flyttal, anropas konverteringsfunktion, 
	annars sätts sträng till nolltecken */
	if(decimal > SMALLNUM){
		baseFrac = convertFracDecToBase(decimal, maxDigits, base);
		stripZeroes(baseFrac);
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

/* Konverterar tal 'number' med talbas 'baseIn' till tal med talbas 'baseOut' */
char *convertBaseToBase(char *number, int maxDigits, int baseIn, int baseOut){
	double convertedDecimal = convertBaseToDec(number, baseIn);
	char *converted = malloc(sizeof(char) * N);
	converted = convertDecToBase(convertedDecimal, maxDigits, baseOut);
	return converted;
}

/* Konverterar tal 'number' med talbas 'base' till decimalt tal */
double convertBaseToDec(char *number, int base){
	char *baseInt = malloc(sizeof(char) * N);
	char *baseFrac = malloc(sizeof(char) * N);
	int stringLength = strlen(number);
	/* Delar upp 'number' till 'baseInt' & 'baseFrac'
		vardera sida om eventuella kommatecken */
	int i = 0;
	for(; i < stringLength && number[i] != '.'; i++){
		/* Tecken i 'number' sätts till 'baseInt', tills alla tecken
			är skrivna, eller tills kommatecken ( . )  hittas. */
		baseInt[i] = number[i];
	}
	baseInt[i+1] == '\0'; //Nolltecken skrivs
	/* Heltalet 'baseInt' konverteras till decimalt tal,
		som sätts till 'convertedInt'	*/
	int convertedInt = convertIntBaseToDec(baseInt, base);
	/* 'convertedFrac' används för värdet efter decimaltecken i 'number',
		om finns.	*/
	double convertedFrac = 0.0;
	/* Om kommatecken ( . ) finns i 'number' efter kopiering till 'baseInt',
		kopieras resten av tecknen till 'baseFrac' */
	if(number[i++] == '.'){
		int j = 0;
		while(number[i] != '\0'){
			baseFrac[j] = number[i];
			i++; j++;
		}
		/* Värdet 'baseFrac' konverteras till decimalt tal,
			som sätts till 'convertedFrac' */
		convertedFrac = convertFracBaseToDec(baseFrac, base);
	}
	else{	// Eventuellt onödigt
		baseFrac[0] = '\0'; 
	}
	return convertedInt + convertedFrac;
}

//*****BUG: NÅGOT TOKIGT I LOOPEN! FIXA 2*10^2 sätts till 199..
//Ev. FIXAT - KONTROLLERA!

/*	Konverterar heltal 'number' med talbas 'base' till decimalt heltal */
int convertIntBaseToDec(char *number, int base){
	int i = strlen(number) - 1, powerOf = 0;
	int converted = 0;
	for(i; i >= 0; i--){
		/* funktionen pow() från math.h strulade med avrdundning när jag 
			adderade till 'converted' i varje varv. Är eventuellt fixat med typecasting
			till (int) samt addering av 0.5 
			Finns det risk att den blir för stor? Jag hade problemet att den blev 1 för liten.
			Bygg egen funktion?
			*/
		//gammal: converted += charToNum(number[i]) * pow(base, powerOf);
		converted += charToNum(number[i]) * (int)(pow(base, powerOf) + 0.5);
		powerOf++;
	}
	return converted;
}

/*	Konverterar tal < 1 'number' med talbas 'base' till decimalt tal */
double convertFracBaseToDec(char *number, int base){
	int stringLength = strlen(number), powerOf = -1;
	double converted = 0.0;
	for(int i = 0; i < stringLength; i++){
		converted += charToNum(number[i]) * pow(base, powerOf);
		powerOf--;
	}
	return converted;
}
