//
// Created by filipe on 2/18/21.
//
#include "../inc/encodeInput.h"

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
	char* input = NULL;
	bool canRead = false;
	bool canWrite = false;

	inFilename = getBasename(inputName);	//!!!!!!!!!!!!!!!!!! remember to free!
	outFilename = getBasename(outputName);	//!!!!!!!!!!!!!!!!!! remember to free!
	if (realloc(outFilename, strlen(outFilename) + 6) != NULL) // realloc to allow for extension appending
	{
		if (flagSRecord)
			strcat(outFilename, ".srec");
		else
			strcat(outFilename, ".asm");
	}
	else
	{
		printf(MEMORY_ERROR);
		if (inFilename)
			free(inFilename);
		if (outFilename)
			free(outFilename);
		exit(EXIT_FAILURE);
	}

	canRead = ableToRead(inputName);
	canWrite = ableToWrite(outFilename);


	if (flagI)
	{
		if (flagO)
		{
		// 11 - inputfile -> outputfile + extensions
			if (canRead && canWrite)
			{
				flagFromPipe = true;
				// call converter and pass filenames
			}
			else
			{
				printf(IO_ERROR);
				exit(EXIT_FAILURE);
			}

			printf("DEBUG: flagI, flagO");
		}
		else // flagO = false
		{
		// 10 - inputfile - inputfile + extension

			if (realloc(inFilename, strlen(inFilename) + 6) != NULL)
			{
				if (flagSRecord) {
					strcat(outFilename, ".srec");
				}
				else {
					strcat(outFilename, ".asm");
				}
			}
			else
			{
				printf(MEMORY_ERROR);
				exit(EXIT_FAILURE);
			}
			canWrite = ableToRead(inFilename);
			if (canRead && canWrite)
			{
				//call converter and pass !!!INPUTFILENAME!!!
			}
			else
			{
				printf(IO_ERROR);
				exit(EXIT_FAILURE);
			}

			printf("DEBUG: flagI");
		}
	}
	else // flagI = false
	{
		if (flagO)
		{
			// 01 - stdin - outputfile

			if (canWrite)
			{
				flagToPipe = true;
				// call converter
			}

			printf("DEBUG: flagO");
		}
		else // flagO = false
		{
			// 00 - stdin - stdout
			flagFromPipe = true;
			flagToPipe = true;
			// call converter
			printf("DEBUG: noflags");
		}
	}
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
	char* slash = strrchr(path, '/');

	// if a slash was found, return basename else return copy of path
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
		return true;
	}
	else
	{
		return false;
	}
}


void usage() {
	printf(USAGE_FMT);
}