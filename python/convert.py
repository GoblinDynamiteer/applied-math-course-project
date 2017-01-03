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
	#num shall be < 1
	convertedList = ['.'] #So string begins with a comma
	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" #For digits 
	while num > 0 and maxDigits > 0:
		num *= base
		integer = math.trunc(num); #truncates the integer (gets the int-part)
		digit = alpha[integer]
		convertedList.append(digit)
		num -= integer;
		maxDigits -=1
	convertedString = ''.join(convertedList)
	return convertedString
	
#Converts decimal values to base
def convert_to_decimal(num, base):
	decimalValue = 0
	powerOf = 0
	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	splitList = num.split('.') #Splits num to 2 list items, separated by the "."
	integerString = str(splitList[0]) #Sets string to integer part of list
	floatString = str(splitList[1]) #Sets string to float part of list
	for letter in integerString[::-1]: #Loop runs reversed
		value = alpha.find(letter) #Gets index / value from string alpha 5 = 5, 10 = A etc
		decimalValue += value * base**powerOf
		powerOf += 1
	powerOf = -1
	for letter in floatString:
		value = alpha.find(letter) #Gets index / value from string alpha 5 = 5, 10 = A etc
		decimalValue += value * base**powerOf
		powerOf -= 1
	return decimalValue

#Manual input
#num = float(input("Input number to convert: "))
#base = int(input("Input base to convert to: "))
#maxDigits = int(input("Max digits: "))
#converted = convert_to_base(num, base)
#converted = convert_to_base_frac(num, base, maxDigits)

#Tests:
converted = convert_to_base_frac(0.3523256, 16, 10)
print("0.3523256(10) converted: ",converted, "(16)")
converted = convert_to_base(123456789, 16)
print("123456789 (10) converted: ",converted, "(16)")
converted = convert_to_base(255, 2)
print("255 (10) converted: ",converted, "(2)")
converted = convert_to_base(128, 8)
print("128 (10) converted: ",converted, "(8)")
converted = convert_to_decimal("1ABCD13.12F3", 16)
print("1ABCD13.12F3 (16) converted: ",converted, "(10)")
converted = convert_to_decimal("11.00100100001111110110", 2)
print("11.00100100001111110110 (2) converted: ",converted, "(10)")
converted = convert_to_decimal("3.243F6A8", 16)
print("3.243F6A8 (16) converted: ",converted, "(10)")

