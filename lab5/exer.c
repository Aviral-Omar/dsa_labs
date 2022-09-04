#include "measureTimeAndSpace.h"

void clearData(struct records r)
{
	for (int i = 0; i < r.n; i++) {
		free(r.arr[i]);
	}
	free(r.arr);
}

int main()
{
	int size = 1;
	FILE* fp = fopen("complexity.csv", "w");
	for (int i = 1; i <= 5; i++) {
		size *= 10;
		fprintf(fp, "%d", size);
		struct records r = readingTimeTest(size, fp);
		insertionTest(r, fp);
		clearData(r);
	}
	fclose(fp);
}
