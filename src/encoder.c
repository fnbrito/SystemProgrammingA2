//
// Created by filipe on 2/18/21.
//
#include "../inc/encodeInput.h"

unsigned long encode(const char* filename, char* outByteBlock)
{
	FILE* fp;
	unsigned long blockSize = 0;						// Size of the accumulated data block
	unsigned long size = 0;								// Number of bytes read from in / size of read
	unsigned char receivedBytes[BLOCK_SIZE] = {0};		// Array to store data from in
	unsigned char* data = NULL;							// Data block to store accumulated data (blockSize is the size)
	unsigned char* result = NULL;


	if (flagFromPipe)
	{
	//gets binary data from STDIN (pipe) -> stores in data
		if ((fp = popen("","r")) == NULL)
		{
			printf(IO_ERROR);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
	//gets binary data from FILE -> stores in data
		if ((fp = fopen(filename, "r")) == NULL)
		{
			printf(IO_ERROR);
			exit(EXIT_FAILURE);
		}
	}



	while ((size = fread(receivedBytes, 1, BLOCK_SIZE, fp)) > 0)
	{
		blockSize += size;
		if ((data = (unsigned char*)realloc(data, blockSize)) == NULL)
		{
			if (data)
				free(data);
			printf(IO_ERROR);
			exit(EXIT_FAILURE);
		}

		memcpy(data, receivedBytes, size);
	}


	if (flagSRecord)
	{
	//converts data to S-Record format and stores it in result
	}
	else
	{
	//converts data to ASM format and stores it in result
	}

	if (flagToPipe)
	{
	//writes result to STDOUT (pipe)
	}
	else
	{
	//writes result to FILE (filename)
	}

	return blockSize;
}

