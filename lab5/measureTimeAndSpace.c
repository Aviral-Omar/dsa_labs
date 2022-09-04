#include "measureTimeAndSpace.h"

struct records readingTimeTest(int size, FILE* fp)
{
	struct timeval t1, t2;
	double tt1;
	gettimeofday(&t1, NULL);

	char str[8];
	sprintf(str, "%d", size);

	struct records r = readData(fopen(size < 100000 ? str : "100000", "r"), size);

	gettimeofday(&t2, NULL);
	tt1 = (t2.tv_sec - t1.tv_sec) * 1000.0;
	tt1 += (t2.tv_usec - t1.tv_usec) / 1000.0;

	fprintf(fp, ",%lf", tt1);

	return r;
}

void insertionTest(struct records r, FILE* fp)
{
	int bottomOfStack;
	struct timeval t1, t2;
	double tt1;
	gettimeofday(&t1, NULL);

	insertionSort(r.arr, r.n);

	gettimeofday(&t2, NULL);
	tt1 = (t2.tv_sec - t1.tv_sec) * 1000.0;
	tt1 += (t2.tv_usec - t1.tv_usec) / 1000.0;
	fprintf(fp, ",%lf,%llu\n", tt1, (unsigned long long)&bottomOfStack - (unsigned long long)topOfStack);
}
