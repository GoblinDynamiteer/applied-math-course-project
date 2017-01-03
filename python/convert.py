# -*- coding: latin-1 -*-
import math

#Convert integers to any base (up to Z..)
def convert_to_base(num, base): #definition of functions in python
	convertedList = []
	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" #For digits 
	while num:
		rest = num % base;
		digit = alpha[rest]
		convertedList.append(digit)
		num //= base; # // is integer division
	convertedList.reverse()
	convertedString = ''.join(convertedList)
	return convertedString
	
#Convert floats <1 to any base (up to Z..)
def convert_to_base_frac(num, base, maxDigits):
	#num shall be < 0
	convertedList = ['.']
	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" #For digits 
	while num > 0 and maxDigits > 0:
		num *= base
		integer = math.trunc(num); #truncates the integer
		digit = alpha[integer]
		convertedList.append(digit)
		num -= integer;
		maxDigits -=1
	convertedString = ''.join(convertedList)
	return convertedString

#num = float(input("Input number to convert: "))
#base = int(input("Input base to convert to: "))
#maxDigits = int(input("Max digits: "))
#converted = convert_to_base(num, base)
#converted = convert_to_base_frac(num, base, maxDigits)
converted = convert_to_base_frac(0.3523256, 16, 10)
print("0.3523256 Konverterat: ",converted)
converted = convert_to_base(123456789, 16)
print("123456789 Konverterat: ",converted)