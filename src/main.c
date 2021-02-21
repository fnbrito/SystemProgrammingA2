/*
 * FILE				: main.c
 * PROJECT			: Assignment 02 - encodeInput
 * PROGRAMMER		: Filipe Brito (7843808) & Zandrin Joseph (8693058)
 * FIRST VERSION	: 17/FEB/2021
 * DESCRIPTION		:
 * 		This is a tool for Linux. It will take in any binary data and
 * 		format it according to the switches used. The output can either be
 * 		formatted to the S19 Record standard or a dc.b Assembly Constant Byte declaration.
 */
#include "../inc/encodeInput.h"

int main(int argc, char* argv[]) {

	bool bFailure = false;
	int opts;
	char inputPath[MAX_FILENAME] = {0};
	char outputPath[MAX_FILENAME] = {0};


	while (((opts = getopt(argc,argv,OPTSTR)) != -1) && !bFailure)
	{
		switch (opts)
		{
			case 's':

				if ((optarg) && (strcmp(optarg, "rec") == 0))
				{
					flagSRecord = true;
				}
				else
				{
					printf(COMMAND_ERROR);
					bFailure = true;
				}
				break;

			case 'h':
				if (!optarg)
				{
					usage();
				}
				else if (strcmp(optarg, "elp") == 0)
				{
					usage();
				}
				else
				{
					printf(COMMAND_ERROR);
					bFailure = true;
				}
				break;

			case 'i':
				if (optarg)
				{
					if (strlen(optarg) < MAX_FILENAME)
					{
						flagIName = true;
						strcpy(inputPath, optarg);
					}
					flagI = true;
				}
				else
				{
					flagI = true;
				}
				break;
			case 'o':

				if (optarg)
				{
					unsigned short size = 0;
					if ((size = strlen(optarg)) < MAX_FILENAME)
					{
						flagOName = true;
						strcpy(outputPath, optarg);
					}
				}
				flagO = true;
				break;

			case '?':
				printf("Unrecognized command: %c\n", optopt);
				bFailure = true;
				printf(COMMAND_ERROR);
				usage();
				break;

			default:
				bFailure = true;
				printf(COMMAND_ERROR);
				usage();
				break;
		}

	}

	if (bFailure)
		return EXIT_FAILURE;

	flagHandler(inputPath, outputPath);

	return EXIT_SUCCESS;
}