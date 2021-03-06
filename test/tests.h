//Code written by Tomas "Tomki" Kindahl

#define CHECK_DEC_TO_BASE(VAR, CVAR, EXPECT, BASE) \
   if(0 == strcmp(CVAR, EXPECT)) \
      printf("SUCCESS %d(10) = " EXPECT "(" BASE ") = %s(" BASE ")\n", VAR, CVAR); \
   else \
      printf("** FAILURE %d(10) = " EXPECT "(" BASE ") =/= %s(" BASE ")\n", VAR, CVAR);

/* void binary_tests(void) {
   char *binstr;
   binstr = convert_to_binary(826);
   CHECK_DEC_TO_BASE(826, binstr, "1100111010", "2");
   binstr = convert_to_binary(128);
   CHECK_DEC_TO_BASE(128, binstr, "10000000", "2");
   binstr = convert_to_binary(255);
   CHECK_DEC_TO_BASE(255, binstr, "11111111", "2");
   binstr = convert_to_binary(0);
   CHECK_DEC_TO_BASE(0, binstr, "0", "2");
} */

void octal_tests(void) {
   char *octstr;
   octstr = convertIntDecToBase(826, 8);
   CHECK_DEC_TO_BASE(826, octstr, "1472", "8");
   octstr = convertIntDecToBase(365, 8);
   CHECK_DEC_TO_BASE(365, octstr, "555", "8");
   octstr = convertIntDecToBase(128, 8);
   CHECK_DEC_TO_BASE(128, octstr, "200", "8");
   octstr = convertIntDecToBase(0, 8);
   CHECK_DEC_TO_BASE(0, octstr, "0", "8");
}

void hexadecimal_tests(void) {
   char *hexstr;
   hexstr = convertIntDecToBase(826, 16);
   CHECK_DEC_TO_BASE(826, hexstr, "33A", "16");
   hexstr = convertIntDecToBase(365, 16);
   CHECK_DEC_TO_BASE(365, hexstr, "16D", "16");
   hexstr = convertIntDecToBase(128, 16);
   CHECK_DEC_TO_BASE(128, hexstr, "80", "16");
   hexstr = convertIntDecToBase(0, 16);
   CHECK_DEC_TO_BASE(0, hexstr, "0", "16");
}


#define CHECK_DECFRAC_TO_BASE(VAR, CVAR, EXPECT, BASE) \
   if(0 == strcmp(CVAR, EXPECT)) \
      printf("SUCCESS %g(10) = " EXPECT "(" BASE ") = %s(" BASE ")\n", VAR, CVAR); \
   else \
      printf("** FAILURE %g(10) = " EXPECT "(" BASE ") =/= %s(" BASE ")\n", VAR, CVAR);

void binary_fraction_tests(void) {
   char *binstr;
   binstr = convertFracDecToBase(.375, 10, 2);
   CHECK_DECFRAC_TO_BASE(.375, binstr, ".011", "2");
   binstr = convertFracDecToBase(.1, 10, 2);
   CHECK_DECFRAC_TO_BASE(.1, binstr, ".0001100110", "2");
   binstr = convertFracDecToBase(.1416, 15, 2);
   CHECK_DECFRAC_TO_BASE(.1416, binstr, ".001001000011111", "2");
   binstr = convertFracDecToBase(.0, 12, 2);
   CHECK_DECFRAC_TO_BASE(.0, binstr, ".0", "2");
}

void hexadecimal_fraction_tests(void) {
   char *hexstr;
   hexstr = convertFracDecToBase(.375, 10, 16);
   CHECK_DECFRAC_TO_BASE(.375, hexstr, ".6", "16");
   hexstr = convertFracDecToBase(.1, /* 10 */7, 16);
   CHECK_DECFRAC_TO_BASE(.1, hexstr, ".199999A", "16"); //Hur avrunda?
   hexstr = convertFracDecToBase(.1416, /* 10 */7, 16);
   CHECK_DECFRAC_TO_BASE(.1416, hexstr, ".243FE5C", "16");
   hexstr = convertFracDecToBase(.0, 12, 16);
   CHECK_DECFRAC_TO_BASE(.0, hexstr, ".0", "16");
}




//Johans Tester

#define CHECK_DEC_INT_FRAC_TO_BASE(VAR, CVAR, EXPECT, BASE) \
   if(0 == strcmp(CVAR, EXPECT)) \
      printf("SUCCESS %g(10) = " EXPECT "(" BASE ") = %s(" BASE ")\n", VAR, CVAR); \
   else \
      printf("** FAILURE %g(10) = " EXPECT "(" BASE ") =/= %s(" BASE ")\n", VAR, CVAR);
	  
void hexadecimal_full_tests(void) {
   char *hexstr;
   //VÄRDEN FRÅN http://www.statman.info/conversions/hexadecimal.html
   hexstr = convertDecToBase(12.5, 10, 16);
   CHECK_DECFRAC_TO_BASE(12.5, hexstr, "C.8", "16");
   hexstr = convertDecToBase(365.1264, 11, 16);
   CHECK_DECFRAC_TO_BASE(365.1264, hexstr, "16D.205BC01A36E", "16");
   hexstr = convertDecToBase(0.65, 5, 16);
   CHECK_DECFRAC_TO_BASE(0.65, hexstr, "0.A6666", "16");
   hexstr = convertDecToBase(171.0, 10, 16); //Måste slås in som med 0 efter decimal för min funktion
   CHECK_DECFRAC_TO_BASE(171.0, hexstr, "AB", "16");
}

#define CHECK_BASE_TO_BASE(VAR, CVAR, EXPECT, BASE) \
   if(0 == strcmp(CVAR, EXPECT)) \
      printf("SUCCESS %g(10) = " EXPECT "(" BASE ") = %s(" BASE ")\n", VAR, CVAR); \
   else \
      printf("** FAILURE %g(10) = " EXPECT "(" BASE ") =/= %s(" BASE ")\n", VAR, CVAR);
	  

//Konverterar från talbas 10 till talbas 10, ska bli samma!
//char *convertBaseToBase(char *number, int maxDigits, int baseIn, int baseOut);
void dec_to_dec_tests(void) {
   char *decstr;
   decstr = convertBaseToBase("12456.789", 10, 10, 10);
	CHECK_BASE_TO_BASE(12456.789, decstr, "12456.789", "10");
   decstr = convertBaseToBase("0.98092", 10, 10, 10);
   CHECK_BASE_TO_BASE(0.98092, decstr, "0.98092", "10");
   decstr = convertBaseToBase("99999.0", 10, 10, 10);
   CHECK_BASE_TO_BASE(99999.0, decstr, "99999.0", "10");
}