/*
 * FILE				: middleman.c
 * PROJECT			: Assignment 02 - encodeInput
 * PROGRAMMER		: Filipe Brito (7843808) & Zandrin Joseph (8693058)
 * FIRST VERSION	: 18/FEB/2021
 * DESCRIPTION		:
 * 		This part of the program will handle the different options the user will have
 * 		chosen, and act accordingly.
 */
#include "../inc/encodeInput.h"

char* getBasename(const char* path);
bool ableToRead(const char* filePath);
bool ableToWrite(const char* filePath);


//
// FUNCTION 	:	flagHandler
// DESCRIPTION	:	This function decides how the data will be handled depending on
// 					the flags previously set.
// PARAMETERS	:	char* inputName - path or name of the input file (optional if flagI is NOT set).
//             		char* outputName - path or name for the output file (optional if flagO is NOT set).
// RETURNS		:	void
//
void flagHandler(const char* inputName, const char* outputName)
{
	char* inFilename = NULL;
	char* outFilename = NULL;
	bool canRead = false;
	bool canWrite = false;

	if (strlen(inputName) > 0)
	{
		inFilename = getBasename(inputName);	//!!!!!!!!!!!!!!!!!! remember to free!
		canRead = ableToRead(inputName);
	}

	if (strlen(outputName) > 0)
	{
		outFilename = getBasename(outputName);	//!!!!!!!!!!!!!!!!!! remember to free!
		canWrite = ableToWrite(outFilename);
		flagOName = true;
	}


	if (flagI)
	{
		if (flagO)
		{
		// i+o - inputfile -> outputfile + extensions
			if (canRead && canWrite)
			{
				encode(inputName, outputName);
			}
			else
			{
				printf(IO_ERROR);
				exit(EXIT_FAILURE);
			}

		}
		else // flagO = false
		{
		// i - inputfile -> inputfile + extension
			char* temp;
			if ((temp = (char*)malloc(strlen(inFilename) + 6)) == NULL)
			{
				printf(MEMORY_ERROR);
				exit(EXIT_FAILURE);
			}
			strcpy(temp, inputName);
			flagSRecord ? strcat(temp, ".srec") : strcat(temp, ".asm");
			canWrite = ableToWrite(temp);
			if (temp)
				free(temp);

			if (canRead && canWrite)
			{
				//call encoder and pass !!!INPUTFILENAME!!!
				encode(inFilename, NULL);
			}
			else if (canWrite)
			{
				encode(inFilename, NULL);
			}
			else
			{
				printf(IO_ERROR);
				exit(EXIT_FAILURE);
			}

		}
	}
	else // flagI = false
	{
		if (flagO)
		{
			// o - stdin -> outputfile

			if (canWrite)
			{
				flagFromPipe = true;
				encode(NULL, outFilename);
			}

		}
		else // flagO = false
		{
			// noflag - stdin -> stdout
			flagFromPipe = true;
			flagToPipe = true;

			encode(NULL, NULL);

		}
	}

//	if (inFilename)
//		free(inFilename);
//	if(outFilename)
//		free(outFilename);
}





//
// FUNCTION 	:	getBasename
// DESCRIPTION	:	This function extracts a basename from a path.
// PARAMETERS	:	char* path - path or name of file.
// RETURNS		:	char* with only the basename or the original argument.
//
char* getBasename(const char* path)
{
	// searches for a slash in the name
	char* slash = NULL;
	if ((slash = strrchr(path, '/')) == NULL)
		return (char*)path;
	// if a slash was found, return basename else return copy of path
	else
		return strdup(slash ? slash + 1 : path);
}


//
// FUNCTION 	:	ableToRead
// DESCRIPTION	:	This function simply checks if the file specified in filePath is present and can be read.
// PARAMETERS	:	char* filePath - name or filePath to a file.
// RETURNS		:	false: no file found / could not open file.
//					true: file is able to be read.
//
bool ableToRead(const char* filePath)
{
	FILE * fp = NULL;
	if ((fp = fopen(filePath, "r")) != NULL)
	{
		fclose(fp);
		return true;
	}
	else
	{
		return false;
	}
}


//
// FUNCTION 	:	ableToWrite
// DESCRIPTION	:	This function simply checks if the file specified in filePath can be written to.
// PARAMETERS	:	char* filePath - name or filePath to a file.
// RETURNS		:	0: no file found / could not open file.
//					1: file found.
//
bool ableToWrite(const char* filePath)
{
	FILE * fp = NULL;
	if ((fp = fopen(filePath, "w")) != NULL)
	{
		fclose(fp);
		remove(filePath);
		return true;
	}
	else
	{
		return false;
	}
}

//
// FUNCTION 	:	usage
// DESCRIPTION	:	This function simply prints the usage instructions to the screen.
// PARAMETERS	:	void
// RETURNS		:	void
//
void usage() {
	printf(USAGE_FMT);
}