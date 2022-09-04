#include "insertionSort.h"

int* topOfStack;

void insertInOrder(CreditCard* arr, int n, CreditCard c)
{
	CreditCard temp;
	int i = n - 1;
	while (i >= 0 && arr[i]->cardNumber > c->cardNumber) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = c;
}

void insertionSort(CreditCard* arr, int n)
{
	if (n == 0) {
		topOfStack = &n;
		return;
	}
	insertionSort(arr, n - 1);
	insertInOrder(arr, n - 1, arr[n - 1]);
}
