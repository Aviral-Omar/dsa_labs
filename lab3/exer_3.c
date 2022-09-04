#include "cycle.h"
#define N 1000000

int main()
{
	LinkedList* Ls = createList(N);
	Ls = createCycle(Ls, N);
	printf("%s\n", testCyclic(Ls) ? "Linear" : "Cyclic");
	Node it = Ls->first, *temp;
	while (it != NULL) {
		temp = it;
		it = it->next;
		myfree((void*)temp, sizeof(struct node));
	}
	myfree((void*)Ls, sizeof(LinkedList));


	return 0;
}
