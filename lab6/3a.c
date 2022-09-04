#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

int main()
{
	printf("Enter file name: ");
	char fname[20];
	scanf("%s", fname);

	printf("Enter k: ");
	int k;
	scanf("%d", &k);

	FILE* inFp = fopen(fname, "r");
	FILE* outFp = fopen("3a_out.txt", "w");


	Record arr[k];
	int done = 0;

	while (1) {
		for (int i = 0; i < k; i++) {
			if (feof(inFp)) {
				done = i;
				break;
			}
			fscanf(inFp, " %[^,],%f", arr[i].name, &arr[i].cgpa);
		}

		if (done) {
			k = done;
		}

		mergeSort(arr, 0, k - 1);

		for (int i = 0; i < k; i++) {
			fprintf(outFp, "%s,%f\n", arr[i].name, arr[i].cgpa);
		}

		if (done) break;
	}

	fclose(inFp);
	fclose(outFp);
}
