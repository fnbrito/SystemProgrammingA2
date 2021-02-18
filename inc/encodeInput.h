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

#include "../src/middleman.c"

#define OPTSTR "s::h::i::o::"
#define USAGE_FMT "Usage: [-iINPUTFILENAME] [-oOUTPUTFILENAME] [-srec] [-h]\n"
#define COMMAND_ERROR "ERROR: Unrecognized command.\n"
#define MAX_FILENAME 255

bool flagI;
bool flagIName;
bool flagO;
bool flagOName;
bool flagSrecord;
bool flagFailure;

inline void usage();
void flagHandler();

#endif //ENCODEINPUT_ENCODEINPUT_H
