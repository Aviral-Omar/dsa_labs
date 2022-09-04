#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

void mergeFiles(char* file1, char* file2, char* outfile)
{
	FILE* inFp1 = fopen(file1, "r");
	FILE* inFp2 = fopen(file2, "r");
	FILE* outFp = fopen(outfile, "w");

	Record a;
	Record b;

	fscanf(inFp1, "%[^,],%f", a.name, &a.cgpa);
	fscanf(inFp2, "%[^,],%f", b.name, &b.cgpa);

	while (!feof(inFp1) && !feof(inFp2)) {
		if (a.cgpa < b.cgpa) {
			fprintf(outFp, "%s,%f\n", a.name, a.cgpa);
			fscanf(inFp1, " %[^,],%f", a.name, &a.cgpa);
		} else {
			fprintf(outFp, "%s,%f\n", b.name, b.cgpa);
			fscanf(inFp2, " %[^,],%f", b.name, &b.cgpa);
		}
	}

	while (!feof(inFp1)) {
		fprintf(outFp, "%s,%f\n", a.name, a.cgpa);
		fscanf(inFp1, " %[^,],%f", a.name, &a.cgpa);
	}
	while (!feof(inFp2)) {
		fprintf(outFp, "%s,%f\n", b.name, b.cgpa);
		fscanf(inFp2, " %[^,],%f", b.name, &b.cgpa);
	}


	fclose(inFp1);
	fclose(inFp2);
	fclose(outFp);
}

int main()
{
	printf("Enter file 1 name: ");
	char fname1[20];
	scanf("%s", fname1);
	printf("Enter file 2 name: ");
	char fname2[20];
	scanf("%s", fname2);
	printf("Enter output file name: ");
	char outName[20];
	scanf("%s", outName);
	mergeFiles(fname1, fname2, outName);
}
