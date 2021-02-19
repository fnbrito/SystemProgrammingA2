//
// Created by filipe on 2/17/21.
//

#ifndef ENCODEINPUT_ENCODEINPUT_H
#define ENCODEINPUT_ENCODEINPUT_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define OPTSTR "s::h::i::o::"
#define USAGE_FMT "Usage: [-iINPUTFILENAME] [-oOUTPUTFILENAME] [-srec] [-h]\n"
#define COMMAND_ERROR "ERROR: Unrecognized command.\n"
#define IO_ERROR "ERROR: Could not read or write to file.\n"
#define MEMORY_ERROR "ERROR: Could not allocate memory.\n"
#define MAX_FILENAME 255
#define BLOCK_SIZE 256

bool flagI;
bool flagIName;
bool flagO;
bool flagOName;
bool flagSRecord;
bool flagFailure;
bool flagFromPipe;
bool flagToPipe;

void usage();
void flagHandler(const char* inputName, const char* outputName);
char* getBasename(const char* path);
bool ableToRead(const char* filePath);
bool ableToWrite(const char* filePath);
unsigned long encode(const char* filename, char* outByteBlock);

#endif //ENCODEINPUT_ENCODEINPUT_H