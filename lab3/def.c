#include "def.h"

int space = 0;

void* myalloc(int size)
{
	space += size;
	return malloc(size);
}

void myfree(void* p, int size)
{
	free(p);
	space -= size;
}
