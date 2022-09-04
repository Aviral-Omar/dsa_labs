#include "def.h"

int main()
{
	int r = (rand() % 15001) + 10000;
	int* a = (int*)myalloc(sizeof(int) * r);
	while (a != NULL) {
		printf("%u %u ", a, a + r - 1);
		myfree((void*)a, sizeof(int) * r);
		r = (rand() % 15001) + 10000;
		a = (int*)myalloc(sizeof(int) * r);
	}
	return 0;
}
