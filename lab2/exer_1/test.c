/* File: test.c */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	for (int i = 2; argv[0][i] != '\0'; i++) {
		printf("%c", argv[0][i]);
	}
	for (int i = 1; i < argc; i++) {
		int v = atoi(argv[i]);
		v ? printf(" %d", v) : printf(" %s", argv[i]);
	}
}
