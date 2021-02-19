#include "../inc/encodeInput.h"

int main(int argc, char* argv[]) {

	int opts;
//	char inputPath[MAX_FILENAME] = {0};
//	char outputPath[MAX_FILENAME] = {0};
	char* inputPath = NULL;
	char* outputPath = NULL;

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
					printf("DEBUG: flagSRecord = true\n");
					flagSRecord = true;
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
						//strncpy(inputPath, optarg, size);
						inputPath = strdup(optarg);
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
//						if((outputPath = (char*)malloc(size)) == NULL)
//						{
//							printf(MEMORY_ERROR);
//							return EXIT_FAILURE;
//						}
//						strncpy(outputPath, optarg, size);
						outputPath = strdup(optarg);
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

	flagHandler(inputPath, outputPath);

	if (inputPath)
		free(inputPath);
	if (outputPath)
		free(outputPath);

	return EXIT_SUCCESS;
}