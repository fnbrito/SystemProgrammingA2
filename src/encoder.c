/*
 * FILE				: middleman.c
 * PROJECT			: Assignment 02 - encodeInput
 * PROGRAMMER		: Filipe Brito (7843808) & Zandrin Joseph (8693058)
 * FIRST VERSION	: 18/FEB/2021
 * DESCRIPTION		:
 * 		Here lies all the functions related to converting data to the specified formats.
 */
#include "../inc/encodeInput.h"


int dcbBlockBuilder(unsigned char *block, int blockSize, unsigned char *outResult);
int dcbLineBuilder(int size, unsigned char *data, unsigned char *outLine);
int s19BlockBuilder (unsigned char* block, int blockSize, unsigned char* outResult);
int s19LineBuilder(unsigned short address, unsigned char dataSize, unsigned char* data, char *line);
unsigned char checksumCalculator(unsigned char count, unsigned short address, unsigned char dataSize, const unsigned char* data);


//
// FUNCTION 	:	encode
// DESCRIPTION	:	This function decides how the data will be handled depending on
// 					the flags previously set.
// PARAMETERS	:	char* inputName - path or name of the input file (optional if flagI is NOT set).
//             		char* outputName - path or name for the output file (optional if flagO is NOT set).
// RETURNS		:	void
//
unsigned long encode(const char* inputName, const char* outputName)
{
	FILE* fp = NULL;
	int blockSize = 0;								// Size of the accumulated dataBlock block
	int resultSize = 0;
	int previousBlockSize = 0;
	int bytesRead = 0;								// Number of bytes read from in / size of read
	unsigned char receivedBytes[BLOCK_SIZE] = {0};		// Array to store dataBlock from in
	unsigned char* dataBlock = NULL;					// Data block to store accumulated data (blockSize is the size)
	unsigned char* result = NULL;
	char outName[MAX_FILENAME] = {0};
	//char inName[MAX_FILENAME] = {0};



	if (flagIName && !flagO)
	{
		strcpy(outName, inputName);
		if(flagSRecord)
		{
			strcat(outName, ".srec");
		}
		else
			strcat(outName, ".asm");
	}
	else if (flagO)
	{
		strcpy(outName, outputName);
		flagSRecord ? strcat(outName, ".srec") : strcat(outName, ".asm");
	}
	else if (flagIName)
	{
		//
	}


	if (flagFromPipe)
	{
		while ((bytesRead = (int)fread(receivedBytes, 1, BLOCK_SIZE, stdin)) > 0)
		{
			previousBlockSize = blockSize;
			blockSize += bytesRead;
			if ((dataBlock = (unsigned char*)realloc(dataBlock, blockSize)) == NULL)
			{
				if (dataBlock) {
					free(dataBlock);
				}
				printf(MEMORY_ERROR);
				exit(EXIT_FAILURE);
			}

			memcpy(dataBlock + previousBlockSize, receivedBytes, bytesRead);
		}
		if (blockSize == 0)
		{
			printf("Error: no data could be read from pipe.");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
	//gets binary dataBlock from FILE -> stores in dataBlock
		if ((fp = fopen(inputName, "rb")) == NULL)
		{
			printf(IO_ERROR);
			exit(EXIT_FAILURE);
		}

		while ((bytesRead = fread(receivedBytes, 1, BLOCK_SIZE, fp)) > 0)
		{
			previousBlockSize = blockSize;
			blockSize += bytesRead;
			if ((dataBlock = (unsigned char*)realloc(dataBlock, blockSize)) == NULL)
			{
				if (dataBlock)
					free(dataBlock);
				printf(MEMORY_ERROR);
				exit(EXIT_FAILURE);
			}

			memcpy(dataBlock + previousBlockSize, receivedBytes, bytesRead);
		}
		fclose(fp);
	}


	if (flagSRecord)
	{ //2 * ((blockSize / 16) * 40)
	//converts dataBlock to S-Record format and stores it in result
		if ((result = (unsigned char*)malloc((((blockSize + 15) / 16) * 43) + 65)) == NULL)// (blockSize + 15) / 16 = max no of lines
		{																						// max no of lines * 43(max number of characters in S1 line)
			printf(MEMORY_ERROR);																//  + 65 (sum overhead of S0 S5 and S9 lines)
			exit(EXIT_FAILURE);
		}
		resultSize = s19BlockBuilder(dataBlock, blockSize, result);
	}
	else
	{
	//converts dataBlock to ASM format and stores it in result
		if ((result = (unsigned char*)malloc(((blockSize + 15) / 16) * 83)) == NULL)	// (blockSize + 15) / 16 = max no of lines
		{																					// max no of lines * 83(max number of characters in line)
			printf(MEMORY_ERROR);
			exit(EXIT_FAILURE);
		}
		resultSize = dcbBlockBuilder(dataBlock, blockSize, result);
	}

	if (flagToPipe)
	{
	//writes result to STDOUT (pipe)
		int fd[2];
		pipe(fd);
		write(fd[1], result, resultSize);
	}
	else
	{
	//writes result to FILE (inputName)
		if ((fp = fopen(outName, "wb")) == NULL)
		{
			printf(IO_ERROR);
			exit(EXIT_FAILURE);
		}

		//bytesRead = (int)
		fwrite(result, 1, resultSize - 1, fp);

		fclose(fp);
	}

	if (result)
		free(result);

	return EXIT_SUCCESS;
}


//
// FUNCTION 	:	dcbBlockBuilder
// DESCRIPTION	:	This function will generate an S19 Record of the block (data) give.
// 					The result is stored in outResult.
// PARAMETERS	:	unsigned char* block - Pointer to where the data is stored
//					int blockSize - size of the data block
// RETURNS		:	void
//
int dcbBlockBuilder(unsigned char *block, int blockSize, unsigned char *outResult) {
	int bytesReceived = 0;
	int bytesProcessed = 0;
	int getBytes = 0;
	int resultSize = 0;
	unsigned char* ptrResult = outResult;
	unsigned char dataBuffer[BUFFER_SIZE] = {0};
	unsigned char line[ASM_LINE_SIZE] = {0};

	for (int i = 0; (blockSize - bytesProcessed - 1) > 0; i++)
	{

		if (blockSize - bytesProcessed >= 16){
			getBytes = BUFFER_SIZE;
		}
		else{
			getBytes = blockSize - bytesProcessed - 1;
		}

		memcpy(dataBuffer, block + bytesProcessed, getBytes);
		bytesProcessed += getBytes;
		bytesReceived = dcbLineBuilder(getBytes, dataBuffer, line);

		memcpy(ptrResult, line, bytesReceived);
		ptrResult += bytesReceived;
		*ptrResult++ = 10;
		resultSize += bytesReceived + 1;

		memset(line, 0, 100);
	}

	return resultSize;
}


//
// FUNCTION 	:	dcbLineBuilder
// DESCRIPTION	:	This function will convert a line in hexadecimal form.
// PARAMETERS	:	int size - size of data.
// 					unsigned char* data - Pointer to where the data is stored
// 					unsigned char* outLine - The result is stored in outResult.
// RETURNS		:	int - how many characters were stored in outLine
//
int dcbLineBuilder(int size, unsigned char *data, unsigned char *outLine) {
	const char format[] = "$%02X, ";
	unsigned char* ptrData = data;
	unsigned char* ptrOut = outLine;


	sprintf((char*)outLine, "dc.b\t");

	for (int i = 0; i < size; i++)
	{
		ptrOut += 5;
		sprintf((char*)ptrOut,format,*ptrData++);
	}

	ptrOut += 3;
	*ptrOut = 0;


	return (int)strlen((char*)outLine);
}


//
// FUNCTION 	:	s19BlockBuilder
// DESCRIPTION	:	This function will get input and convert it to SRecord standard.
// PARAMETERS	:	unsigned char* block - data to be converted.
// 					int blockSize - size of data
// 					unsigned char* outResult - The result is stored in outResult.
// RETURNS		:	int - how many characters were stored in outResult
//
int s19BlockBuilder (unsigned char* block, int blockSize, unsigned char* outResult)
{
	unsigned char dataSize = 0;
	unsigned short address = STARTING_ADDRESS;
	unsigned char dataBuffer[BUFFER_SIZE] = {0};
	char line[SREC_LINE_SIZE] = SREC_S0LINE;
	unsigned char* ptrResult = outResult;
	char* ptrLine = NULL;
	int resultSize = 0;
	int bytesProcessed = 0;
	int numberOfLines = 0;


	// S0
	memcpy(ptrResult, line, strlen(line));
	ptrResult += strlen(line);
	*ptrResult++ = 10;
	resultSize += (int)strlen(line) + 1;
	ptrLine = line;
	memset(ptrLine, 0, SREC_LINE_SIZE);


	// S1 Loops
	blockSize--;
	for (numberOfLines = 0; (blockSize - bytesProcessed) > 0; numberOfLines++)
	{
		int numOfChars = 0;

		*ptrLine++ = 'S';
		*ptrLine++ = '1';

		if (blockSize - bytesProcessed >= 16){
			dataSize = BUFFER_SIZE;
		}
		else{
			dataSize = blockSize - bytesProcessed;
		}

		memcpy(dataBuffer, block + bytesProcessed, dataSize);
		bytesProcessed += dataSize;
		numOfChars = s19LineBuilder(address, dataSize, dataBuffer, ptrLine);
		numOfChars += 2; // account for S1

		memcpy(ptrResult, line, numOfChars);
		ptrResult += numOfChars;
		*ptrResult++ = 10;
		resultSize += numOfChars + 1;

		address += dataSize;
		ptrLine = line;
		memset(ptrLine, 0, SREC_LINE_SIZE);
	}
	// S5
	dataSize = 0;
	address = numberOfLines;
	*ptrLine++ = 'S';
	*ptrLine++ = '5';
	s19LineBuilder(address, dataSize, NULL, ptrLine);

	memcpy(ptrResult, line, strlen(line));
	ptrResult += strlen(line);
	*ptrResult++ = 10;
	resultSize += (int)strlen(line) + 1;
	ptrLine = line;

	// S9
	address = STARTING_ADDRESS;
	*ptrLine++ = 'S';
	*ptrLine++ = '9';
	s19LineBuilder(address, dataSize, NULL, ptrLine);

	memcpy(ptrResult, line, strlen(line));
	ptrResult += strlen(line);
	*ptrResult++ = 10;
	resultSize += (int)strlen(line) + 1;

	return resultSize;
}


//
// FUNCTION 	:	s19LineBuilder
// DESCRIPTION	:	This function will get a data line and convert it to SRecord standard.
//					This function will not add the S# head of the line, that should be added
//					by other logic.
// PARAMETERS	:	unsigned short address - value of address.
// 					unsigned char dataSize - size of data block
// 					unsigned char* data - data block
//					char* line - result will be stored in line
// RETURNS		:	int - how many characters were stored in line
//
int s19LineBuilder(unsigned short address, unsigned char dataSize, unsigned char* data, char* line)
{
	int i = 0;
	int charCount = 0;
	unsigned char checksum = 0;
	unsigned char count = dataSize + (char)sizeof(address) + (char)sizeof(checksum);
	checksum = checksumCalculator(count, address, dataSize, data);

	sprintf(line, "%02X%04X", count, address);
	line += 6;
	charCount += 6;

	while (i < dataSize && data != NULL)
	{
		sprintf(line, "%02X\n", data[i++]);
		line += 2;
		charCount += 2;
	}
	sprintf(line, "%02X", checksum);
	charCount += 2;

	return charCount;
}


//
// FUNCTION 	:	checksumCalculator
// DESCRIPTION	:	This function will calculate the checksum for the SRecord line's values sent.
//					The checksum is the sum of the values of count, address and each byte of data, NOTted and only the last byte remained.
// PARAMETERS	:	unsigned char count - value of CC(count)
// 					unsigned short address - value of AAAA(address)
// 					unsigned char dataSize - size of what's in data
//					const unsigned char* data - the data to be summed
// RETURNS		:	unsigned char - the resulting checksum value (1byte)
//
unsigned char checksumCalculator(unsigned char count, unsigned short address, unsigned char dataSize, const unsigned char* data)
{
	unsigned char checksum = 0;
	int temp = 0;

	for (int i = 0; i < dataSize && data != NULL; i++)
	{
		temp += (char)data[i];
	}

	temp += count + address;
	checksum = temp << 0;
	checksum = ~checksum;

	return checksum;
}