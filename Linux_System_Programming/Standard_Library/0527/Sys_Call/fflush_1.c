#include <stdio.h>

int
main (int argc,
      char *argv[])
{
	char *prompt = "Prompt>>";
	char command[80];

	for (;;) {
		fputs (prompt, stdout);
		if ( fgets(command, sizeof(command), stdin) == NULL ) {
			break;
		}
		system(command);
	}
	fprintf(stdout, "Good Bye...");
	fflush(stdout);
	system("clear");

	return 0;
}
