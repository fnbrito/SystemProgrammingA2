//
// Created by filipe on 2/18/21.
//
#include "../inc/encodeInput.h"

void encode(const char* filename)
{
	unsigned char* byteBlock = NULL;

	if (flagFromPipe)
	{
		//reads pipe to get the binary data
	}
	else
	{
		//reads from filename
	}

	if (flagSRecord)
	{
		//convert byte block to S-Record
	}
	else
	{
		//convert byte block to hexadecimal characters (.asm)
	}

	if (flagToPipe)
	{
		//writes to pipe
	}
	else
	{
		//writes to filename
	}
}

