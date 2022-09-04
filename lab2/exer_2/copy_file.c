#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE* reader = fopen(argv[1], "r");
	FILE* writer = fopen(argv[2], "w");

	if (reader == NULL || writer == NULL) {
		printf("File does not exist or unable to access file.");
		exit(1);
	}
	char c = fgetc(reader);
	while (c != EOF) {
		fprintf(writer, "%c", c);
		c = fgetc(reader);
	}
	return 0;
}
