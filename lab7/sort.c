#include "sort.h"


void sort(Employee Ls[], int n, int s)
{
	qs(Ls, n, s);
	insertionSort(Ls, n);
}
