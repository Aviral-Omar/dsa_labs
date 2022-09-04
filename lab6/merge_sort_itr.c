#include "merge_sort.h"

int min(int a, int b)
{
	return (a < b) ? a : b;
}

void mergeSort(Record *arr, int l, int r)
{
	int size = r - l + 1;
	int currSize;
	int left;

	for (currSize = 1; currSize < size; currSize *= 2) {
		for (left = 0; left < size; left += 2 * currSize) {
			int mid = min(left + currSize - 1, size - 1);
			int right = min(left + 2 * currSize - 1, size - 1);

			int sz = mid - left + 1 + right - mid;

			Record ls[sz];

			merge(arr + left, mid - left + 1, arr + mid + 1, right - mid, ls);

			int j = 0;
			for (int i = left; i <= right; i++) {
				arr[i] = ls[j++];
			}
		}
	}
}
