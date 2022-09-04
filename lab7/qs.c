#include "qs.h"

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
