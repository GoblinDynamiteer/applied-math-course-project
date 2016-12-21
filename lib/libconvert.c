/* 
Mjukvaruutvecklare Inbyggda System
Applicerad Yrkesmatematik
Julprojekt 2016

Johan Kämpe 
*/




#include "libconvert.h"

/* Vänder på en char-array. Används för konvertering
från hela decimaltal till binära tal. */
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

//Konverterar dec (int) till binär (char array)
char *convert_i_to_binary(int decimal){
	char *omvand = malloc(sizeof(char) * N);
	//oix: omvandling index:
	int t, oix;
	oix = 0;
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
	omvand[oix] = '\0';
	//Vänder på tecknen i char-arrayen
	vand(omvand);
	return omvand;
}

//Konverterar float (double) till binär (char array)
char *convert_f_to_binary(double decfloat){
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

/* Använder funktionerna convert_f_to_binary & convert_i_to_binary
för att konvertera ett flyttal i decimalform till ett binärt flyttal */
char *convert_to_binary(double decimal){
	char *binarD = malloc(sizeof(char) * N);
	char *binarF = malloc(sizeof(char) * N);
	int heltal = decimal;
	decimal = decimal - heltal;
	/* Om flyttal, anropas konverteringsfunktion, 
	annars sätts sträng till nolltecken */
	if(decimal > 0.00000000){
		binarF = convert_f_to_binary(decimal);
	}
	else{
		binarF[0] ='\0';
	}
	/* Om inmatat heltal är större än 1, 
	annars sätts sträng till tecken 0 */
	if(heltal > 0){
		binarD = convert_i_to_binary(heltal);
	}
	else{
		binarD[0] ='0';
		binarD[1] ='\0';
	}
	/* Returnerar sammansatta char-arrayer, 
	+1 för att få bort den initiala nollan i strängen binarF */
	return strcat(binarD, binarF+1);
}