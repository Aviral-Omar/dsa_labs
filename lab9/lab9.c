#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// QuickSort Code

typedef struct pair {
	int l;
	int r;
	struct pair *next;
} Pair;


typedef struct {
	Pair *top;
	int size;
} PairStack;

PairStack *newStack()
{
	PairStack *stack = (PairStack *)malloc(sizeof(PairStack));
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

int isEmpty(PairStack *stack)
{
	return !stack->size;
}

void push(PairStack *stack, int a, int b)
{
	Pair *node = (Pair *)malloc(sizeof(Pair));
	node->l = a;
	node->r = b;

	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

void pop(PairStack *stack)
{
	if (isEmpty(stack)) {
		return;
	}

	stack->top = (stack->top)->next;
	(stack->size)--;
}

Pair top(PairStack *stack)
{
	Pair node;
	if (stack->size == 0) {
		node.l = -1;
		node.r = -1;
		node.next = NULL;
		return node;
	}

	node = *(stack->top);
	return node;
}

void swap(int arr[], int f, int s)
{
	int t = arr[f];
	arr[f] = arr[s];
	arr[s] = t;
}

int part(int arr[], int lo, int hi, int pInd)
{
	swap(arr, pInd, lo);
	int lt = lo + 1, rt = hi;
	int pv = arr[lo];

	while (lt < rt) {
		for (; lt <= hi && arr[lt] <= pv; lt++)
			;
		for (; arr[rt] > pv; rt--)
			;
		if (lt < rt)
			swap(arr, lt, rt);
	}
	int pPos;
	if (arr[lt] < pv)
		pPos = lt;
	else
		pPos = lt - 1;
	swap(arr, lo, pPos);
	return pPos;
}

void quickSort(int arr[], int n)
{
	PairStack *st = newStack();
	push(st, 0, n - 1);

	while (!isEmpty(st)) {
		Pair p = top(st);
		int lo = p.l;
		int hi = p.r;
		pop(st);
		while (lo < hi) {
			int pInd = lo;
			pInd = part(arr, lo, hi, pInd);
			push(st, lo, pInd - 1);
			lo = pInd + 1;
		}
	}
}

// Merge Sort Code

void merge(int arr1[], int sz1, int arr2[], int sz2, int arr[])
{
	int i = 0, j = 0, k = 0;
	while (i < sz1 && j < sz2) {
		if (arr1[i] < arr2[j]) {
			arr[k++] = arr1[i++];
		} else {
			arr[k++] = arr2[j++];
		}
	}
	while (i < sz1) {
		arr[k++] = arr1[i++];
	}
	while (j < sz2) {
		arr[k++] = arr2[j++];
	}
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

void mergeSort(int arr[], int n)
{
	int currSize;
	int left;

	for (currSize = 1; currSize < n; currSize *= 2) {
		for (left = 0; left < n; left += 2 * currSize) {
			int mid = min(left + currSize - 1, n - 1);
			int right = min(left + 2 * currSize - 1, n - 1);

			int sz = mid - left + 1 + right - mid;

			int ls[sz];

			merge(arr + left, mid - left + 1, arr + mid + 1, right - mid, ls);

			int j = 0;
			for (int i = left; i <= right; i++) {
				arr[i] = ls[j++];
			}
		}
	}
}

// Insertion Sort Code

void insertInOrder(int arr[], int n, int c)
{
	int temp;
	int i = n - 1;
	while (i >= 0 && arr[i] > c) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = c;
}

void insertionSort(int arr[], int n)
{
	for (int i = 1; i < n; i++) {
		insertInOrder(arr, i, arr[i]);
	}
}

// Heap Sort Code

int left(int i)
{
	return (i + 1) * 2 - 1;
}

int right(int i)
{
	return (i + 1) * 2;
}

void heapify(int arr[], int n, int i)
{
	int l = left(i);
	int r = right(i);
	int largest = i;
	if (l < n && arr[l] > arr[i]) {
		largest = l;
	}
	if (r < n && arr[r] > arr[largest]) {
		largest = r;
	}
	if (largest != i) {
		swap(arr, largest, i);
		heapify(arr, n, largest);
	}
}

void build_heap(int arr[], int n)
{
	for (int i = n / 2; i >= 0; i--) {
		heapify(arr, n, i);
	}
}

void heap_sort(int arr[], int n)
{
	build_heap(arr, n);
	for (int i = n - 1; i >= 1; i--) {
		swap(arr, i, 0);
		heapify(arr, i - 1, 0);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1], "r");
	int size = 10;
	int *arr = (int *)malloc(sizeof(int) * size);
	int n = 0;
	fscanf(fp, " %*s");	 // String assignment is skipped
	while (!feof(fp)) {
		if (n == size) {
			size *= 2;
			arr = (int *)realloc(arr, sizeof(int) * size);
		}
		fscanf(fp, " %d", arr + n);
		n++;
		fscanf(fp, " %*s");
	}
	fclose(fp);

	int *arr1 = (int *)malloc(sizeof(int) * n);
	int *arr2 = (int *)malloc(sizeof(int) * n);
	int *arr3 = (int *)malloc(sizeof(int) * n);
	int *arr4 = (int *)malloc(sizeof(int) * n);
	memcpy(arr1, arr, n * sizeof(int));
	memcpy(arr2, arr, n * sizeof(int));
	memcpy(arr3, arr, n * sizeof(int));
	memcpy(arr4, arr, n * sizeof(int));

	struct timeval t1, t2, t3, t4, t5;
	double tt1, tt2, tt3, tt4;

	gettimeofday(&t1, NULL);

	quickSort(arr1, n);

	gettimeofday(&t2, NULL);

	tt1 = (t2.tv_sec - t1.tv_sec) * 1000.0;
	tt1 += (t2.tv_usec - t1.tv_usec) / 1000.0;
	printf("Total time taken for quick sort is %lf ms.\n", tt1);

	mergeSort(arr2, n);

	gettimeofday(&t3, NULL);

	tt2 = (t3.tv_sec - t2.tv_sec) * 1000.0;
	tt2 += (t3.tv_usec - t2.tv_usec) / 1000.0;
	printf("Total time taken for merge sort is %lf ms.\n", tt2);

	heap_sort(arr3, n);

	gettimeofday(&t4, NULL);

	tt3 = (t4.tv_sec - t3.tv_sec) * 1000.0;
	tt3 += (t4.tv_usec - t3.tv_usec) / 1000.0;
	printf("Total time taken for heap sort is %lf ms.\n", tt3);

	insertionSort(arr4, n);

	gettimeofday(&t5, NULL);

	tt4 = (t5.tv_sec - t4.tv_sec) * 1000.0;
	tt4 += (t5.tv_usec - t4.tv_usec) / 1000.0;
	printf("Total time taken for insertions sort is %lf ms.\n", tt4);

	FILE *outfp = fopen("data_sorted.txt", "w");
	for (int i = 0; i < n; i++) {
		fprintf(outfp, "%d\n", arr3[i]);
	}
	fclose(outfp);

	free(arr);
	free(arr1);
	free(arr2);
	free(arr3);
	free(arr4);

	return 0;
}

/*
Time Taken for data10000:
Total time taken for quick sort is 7.230000 ms.
Total time taken for merge sort is 7.916000 ms.
Total time taken for insertion sort is 189.281000 ms.
Total time taken for heap sort is 4.744000 ms.
*/

/*
Time Taken for data100000:
Total time taken for quick sort is 41.824000 ms.
Total time taken for merge sort is 38.810000 ms.
Total time taken for insertion sort is 9980.314000 ms.
Total time taken for heap sort is 58.207000 ms.
*/

/*
Time Taken for data1000000:
Total time taken for quick sort is 405.576000 ms.
Total time taken for merge sort is 397.739000 ms.
Total time taken for heap sort is 765.606000 ms.
*/

/*
Time Taken for data10000000:
Total time taken for quick sort is 4032.833000 ms.
Total time taken for heap sort is 10269.775000 ms.
*/
