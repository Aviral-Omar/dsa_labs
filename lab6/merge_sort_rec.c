#include "merge_sort.h"

// void mergeSort(Record arr[], int sz, Record ls[])
// {
// 	if (!sz) return;
// 	int mid = floor(sz / 2);
// 	mergeSort(arr, mid, ls);
// 	mergeSort(arr + mid + 1, sz - mid, ls + mid + 1);
// 	merge(arr, mid, arr + mid + 1, sz - mid, ls);
// 	for (int i = 0; i < sz; i++) {
// 		arr[i] = ls[i];
// 	}
// }


void mergeSort(Record arr[], int left, int right)
{
	// printf("%f first\n", arr[0].cgpa);
	if (left == right) {
		return;
	}

	int mid = (left + right) / 2;

	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	int size = right - left + 1;
	Record mergedArr[size];

	int leftArrSize = mid - left + 1;
	int rightArrSize = right - mid;

	merge(arr + left, leftArrSize, arr + mid + 1, rightArrSize, mergedArr);

	int j = 0;
	for (int i = left; i <= right; i++) {
		// printf("%f\n", mergedArr[j].cgpa);
		arr[i] = mergedArr[j++];
	}
}
