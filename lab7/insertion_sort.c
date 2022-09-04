#include "insertion_sort.h"

void insertInOrder(Employee* arr, int n, Employee c)
{
	int i = n - 1;
	while (i >= 0 && arr[i].empID > c.empID) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = c;
}

void insertionSort(Employee* arr, int n)
{
	for (int j = 1; j < n; j++)
		insertInOrder(arr, j, arr[j]);
}
