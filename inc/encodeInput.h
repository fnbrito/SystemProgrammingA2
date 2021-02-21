/*
 * FILE				: middleman.c
 * PROJECT			: Assignment 02 - encodeInput
 * PROGRAMMER		: Filipe Brito (7843808) & Zandrin Joseph (8693058)
 * FIRST VERSION	: 17/FEB/2021
 * DESCRIPTION		:
 * 		Header file of the project.
 */

#ifndef ENCODEINPUT_ENCODEINPUT_H
#define ENCODEINPUT_ENCODEINPUT_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>


#define SREC_S0LINE "S01410005A414E4452494E2D46494C4950450D"
#define OPTSTR "s::h::i::o::"
#define USAGE_FMT "Usage: [-iINPUTFILENAME] [-oOUTPUTFILENAME] [-srec] [-h]\n"
#define COMMAND_ERROR "ERROR: Unrecognized command.\n"
#define IO_ERROR "ERROR: Could not read or write to file.\n"
#define MEMORY_ERROR "ERROR: Could not allocate memory.\n"
#define STARTING_ADDRESS 0000
#define BLOCK_SIZE 256
#define SREC_LINE_SIZE 43
#define ASM_LINE_SIZE 89
#define BUFFER_SIZE 16
#define MAX_FILENAME 255

bool flagI;
bool flagIName;
bool flagO;
bool flagOName;
bool flagSRecord;
bool flagFromPipe;
bool flagToPipe;


void usage();
void flagHandler(const char* inputName, const char* outputName);
unsigned long encode(const char* inputName, const char* outputName);


#endif //ENCODEINPUT_ENCODEINPUT_H

