# -*- coding: latin-1 -*-

def convert_to_base(num, base): #definition of functions in python
	convertedString = []
	alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	while num:
		rest = num % base;
		digit = alpha[rest]
		convertedString.append(digit)
		num //= base; # // is integer division
		#reversedString = convertedString[::-1] #reverses
	convertedString.reverse()
	return convertedString

num = int(input("Input number: "))
base = int(input("Input base: "))
converted = convert_to_base(num, base)
print("Konverterat: ",converted)