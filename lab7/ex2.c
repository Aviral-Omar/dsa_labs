#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "sort.h"

void testRun(Employee Ls[], int n, double results[])
{
	struct timeval t1, t2;
	double timeTaken;

	Employee newLs[n];
	for (int i = 0; i < n; i++)
		newLs[i] = Ls[i];

	gettimeofday(&t1, NULL);

	qs(Ls, n, 0);

	gettimeofday(&t2, NULL);

	timeTaken = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timeTaken += (t2.tv_usec - t1.tv_usec) / 1000.0;

	results[0] = timeTaken;

	gettimeofday(&t1, NULL);

	insertionSort(newLs, n);

	gettimeofday(&t2, NULL);

	timeTaken = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timeTaken += (t2.tv_usec - t1.tv_usec) / 1000.0;

	results[1] = timeTaken;
}

int estimateCutoff(Employee Ls[], int n)
{
	double results[2];

	Employee newLs[n];

	int min = 0;
	int max = n;

	int mid = (min + max) / 2;
	int prevmid = -1;

	double resultLeft, resultCenter, resultRight;

	while (mid != prevmid) {
		prevmid = mid;
		fflush(stdout);
		for (int i = 0; i < (min + mid) / 2; i++) {
			newLs[i] = Ls[i];
		}

		testRun(newLs, (min + mid) / 2, results);
		resultLeft = fabs(results[0] - results[1]);

		for (int i = 0; i < mid; i++) {
			newLs[i] = Ls[i];
		}
		testRun(newLs, mid, results);
		resultCenter = fabs(results[0] - results[1]);

		for (int i = 0; i < (mid + max) / 2; i++) {
			newLs[i] = Ls[i];
		}
		testRun(newLs, (mid + max) / 2, results);
		resultRight = fabs(results[0] - results[1]);

		printf("mid is %d, %lf,%lf,%lf\n", mid, resultLeft, resultCenter, resultRight);

		if (resultCenter <= resultLeft && resultCenter <= resultRight) {
			// We've found our minimum
			return mid;
		} else {
			if (resultLeft <= resultCenter) {
				max = mid;	// go left
			} else {
				min = mid;
			}
		}
		mid = (min + max) / 2;
	}
	return mid;	 // mid is equal to prevmid, so return mid
}

int main(int argc, char* argv[])
{
	FILE* inpFp = fopen(argv[1], "r");

	int n = 10;
	Employee* arr = malloc(sizeof(Employee) * n);

	int j = 0;
	while (!feof(inpFp)) {
		fscanf(inpFp, "%[^ ] %d\n", arr[j].name, &arr[j].empID);
		j++;
		if (j == 150000) break;
		if (j == n - 1) {
			n *= 10;
			arr = realloc(arr, sizeof(Employee) * n);
		}
	}


	int cutoff = estimateCutoff(arr, j);
	printf("The cutoff is %d\n", cutoff);

	fclose(inpFp);

	FILE* outFp = fopen(argv[2], "w");

	struct timeval t1, t2;
	double timeTaken;

	gettimeofday(&t1, NULL);

	sort(arr, j, cutoff);

	gettimeofday(&t2, NULL);

	timeTaken = (t2.tv_sec - t1.tv_sec) * 1000.0;
	timeTaken += (t2.tv_usec - t1.tv_usec) / 1000.0;

	fprintf(outFp, "Time Taken to sort %d elements with insertion sort cutoff %d: %lf ms.\n", j, cutoff, timeTaken);
	printf("Time Taken to sort %d elements with insertion sort cutoff %d: %lf ms.\n", j, cutoff, timeTaken);

	for (int i = 0; i < j; i++) {
		fprintf(outFp, "%s %d\n", arr[i].name, arr[i].empID);
	}
}
