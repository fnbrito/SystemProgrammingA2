#include "../inc/encodeInput.h"

void usage();

int main(int argc, char* argv[]) {

	int opts;
	char inputFileName[MAX_FILENAME] = {0};
	char outputFileName[MAX_FILENAME] = {0};

	printf("encodeInput started!\n");

	while (((opts = getopt(argc,argv,OPTSTR)) != -1) && !flagFailure)
	{
		switch (opts)
		{
			case 's':
				printf("DEBUG: -s was found\n");
				printf("DEBUG: Added: %s\n", optarg);

				if ((optarg) && (strcmp(optarg, "rec") == 0))
				{
					printf("DEBUG: flagSrecord = true\n");
					flagSrecord = true;
				}
				else
				{
					printf(COMMAND_ERROR);
					flagFailure = true;
				}
				break;

			case 'h':
				printf("DEBUG: -h was found\n");
				if (!optarg)
				{
					printf("DEBUG: usage() called\n");
					usage();
				}
				else if (strcmp(optarg, "elp") == 0)
				{
					printf("DEBUG: usage() called\n");
					usage();
				}
				else
				{
					printf(COMMAND_ERROR);
					flagFailure = true;
				}
				break;

			case 'i':
				printf("DEBUG: -i was found\n");
				if (optarg)
				{
					printf("DEBUG: inputfilename declared as %s\n", optarg);
					unsigned short size = 0;
					if ((size = strlen(optarg)) < MAX_FILENAME)
					{
						flagIName = true;
						strncpy(inputFileName, optarg, size);
					}
					flagI = true;
				}
				else
				{
					printf("DEBUG: empty\n");
					flagI = true;
				}
				break;
			case 'o':
				printf("DEBUG: -o was found\n");

				if (optarg)
				{
					printf("DEBUG: outputfilename declared as %s\n", optarg);
					unsigned short size = 0;
					if ((size = strlen(optarg)) < MAX_FILENAME)
					{
						flagOName = true;
						strncpy(outputFileName, optarg, size);
					}
				}
				flagO = true;
				break;

			case '?':
				printf("Unrecognized command: %c\n", optopt);
				flagFailure = true;
				printf(COMMAND_ERROR);
				usage();
				break;

			default:
				flagFailure = true;
				printf(COMMAND_ERROR);
				usage();
				break;
		}

	}

	if (flagFailure)
		return EXIT_FAILURE;
	else
		//continue program / call function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return EXIT_SUCCESS;
}

void inline usage() {
	printf(USAGE_FMT);
}
