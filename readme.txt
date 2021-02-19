#################################################
# Rough sketch of what to do:		        	#
#################################################

main.c
	commandline arguments
		bitfield byte to store options?
		sets options
	input (filenames only)
	calls middleman


middleman.c
	chooses where and how the code will be returned
		• writes to file
		• sends to stdout
	gets input (code) and sends it to be converted
	handles input of code
	calls functions to convert the code


converter.c
	convert hexadecimal characters to hexadecimal number array
		sends to encoder
	convert number array to hexadecimal characters
		receives from encoder 
	

encoder.c
	creates the S type records or assembly lines of code
	returns to converter



#################################################
# NOTES                     					#
#################################################
Line formation
	TT CC AAAA DD..DD MM

TT - Type of the S-Record
	S1 always adds 16 bytes to the address unless it's the last one
	S5 always follows the last S1
		The AAAA represents the number of S1 records preceeding it
	S9 is the trailer record
		The AAA represents the address in memory where the program starts
		
CC - Count of characters from AAAA to MM

DD..DD - 32chars max (16 hexadecimal values) as input data


COUNT (CC) não tem o TT incluido

Checksum function
	receives line -> returns true or false
		sum = COUNT + ADDRESS + DATA
		!sum (1's complement)
		gets the LSByte of the sum
		
		
Assembly file (define constant byte [dc.b])

Input:	ABCDEFGHIJKLMNOPQRST
OUTPUT:	dc.b $41, $42, $43, $44, $45, $46, $47, $48, $49, $4A, $4B, $4C, $4D, $4E, $4F, $50
		dc.b $51, $52, $53, $54



The task:
	C program called encodeInput with 4 switches
		-iINPUTFILENAME
			if INPUTFILENAME is not supplied it will get from stdin
			if INPUTFILENAME doesn't exist, an error will be presented
		-oOUTPUTFILENAME
			if this file is not specified
				without -srec: FILEINPUT.asm (appended)
				with -srec: FILEINPUT.srec (appended)
			else if can't write to file
				show error
			else
				no input nor output, output is sent to stdout
			
		-srec
			output in the S-Record formation, otherwise Assembly File
		-h
			output help information and exit
			name of the program + allowable runtime switches
		// check if -s contains rec in opt optarg
		// check if an invalid switch is being used
			// if yes, call usage();
		
Some more info:
	#include <unistd> Supplies EXIT_FAILURE, EXIT_SUCCESS
	#include errno ?
	
	#define OPTSTR "shio" - will define the getopt()'s behaviour

	#define USAGE_FMT  "how to use the program" - define a string in the usage() function
	
