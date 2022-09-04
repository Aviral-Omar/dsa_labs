#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct employee {
	char name[10];
	int empID;
} Employee;

typedef struct pair {
	int l;
	int r;
	struct pair* next;
} Pair;


typedef struct {
	Pair* top;
	int size;
} PairStack;

PairStack* newStack();
void push(PairStack* stack, int a, int b);
void pop(PairStack* stack);
Pair top(PairStack* stack);
int isEmpty(PairStack* stack);

PairStack* newStack()
{
	PairStack* stack = (PairStack*)malloc(sizeof(PairStack));
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void push(PairStack* stack, int a, int b)
{
	Pair* node = (Pair*)malloc(sizeof(Pair));
	node->l = a;
	node->r = b;

	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

void pop(PairStack* stack)
{
	if (isEmpty(stack)) {
		return;
	}

	stack->top = (stack->top)->next;
	(stack->size)--;
}


Pair top(PairStack* stack)
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

int isEmpty(PairStack* stack)
{
	return !stack->size;
}

void swap(Employee Ls[], int f, int s);

int part(Employee Ls[], int lo, int hi, int pInd);

void qs(Employee Ls[], int n, int s);

void swap(Employee Ls[], int f, int s)
{
	Employee t = Ls[f];
	Ls[f] = Ls[s];
	Ls[s] = t;
}

int part(Employee Ls[], int lo, int hi, int pInd)
{
	swap(Ls, pInd, lo);
	int lt = lo + 1, rt = hi;
	Employee pv = Ls[lo];

	while (lt < rt) {
		for (; lt <= hi && Ls[lt].empID <= pv.empID; lt++)
			;
		for (; Ls[rt].empID > pv.empID; rt--)
			;
		if (lt < rt)
			swap(Ls, lt, rt);
	}
	int pPos;
	if (Ls[lt].empID < pv.empID)
		pPos = lt;
	else
		pPos = lt - 1;
	swap(Ls, lo, pPos);
	return pPos;
}

void qs(Employee Ls[], int n, int s)
{
	PairStack* st = newStack();
	if (n > s)
		push(st, 0, n - 1);

	while (!isEmpty(st)) {
		Pair p = top(st);
		int lo = p.l;
		int hi = p.r;
		pop(st);
		while (lo < hi) {
			int pInd = lo;
			if (hi - lo > s)
				pInd = part(Ls, lo, hi, pInd);
			if (pInd - 1 - lo > s)
				push(st, lo, pInd - 1);
			lo = pInd + 1;
		}
	}
}

void insertInOrder(Employee* arr, int n, Employee c);
void insertionSort(Employee* arr, int n);

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

void sort(Employee Ls[], int n, int s);

void sort(Employee Ls[], int n, int s)
{
	qs(Ls, n, s);
	insertionSort(Ls, n);
}

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
