//
// Created by filipe on 2/18/21.
//
#include "../inc/encodeInput.h"

extern bool flagI;
extern bool flagIName;
extern bool flagO;
extern bool flagOName;

// sorting the flags
void flagHandler(const char* inputName, const char* outputName)
{
	if (flagI)
	{

		if (flagO)
		{
			// 11 - inputfile - outputfile + extension
			printf("flagI, flagO");
		}
		else // flagO = false
		{
			// 10 - inputfile - inputfile + extension
			// input file name
			printf("flagI");
		}


	}
	else // flagI = false
	{
		if (flagO)
		{
			// 01 - stdin - outputfile
			printf("flagO");
		}
		else // flagO = false
		{
			// 00 - stdin - stdout
			printf("noflags");
		}
	}
}

// chooses where and how the code will be returned

	//• writes to file

	//• sends to stdout

	//	gets input (code) and sends it to be converted

//handles input of code

//calls functions to convert the code
