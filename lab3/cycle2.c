#include "cycle.h"

int testCyclic(LinkedList* Ls)
{
	Node prev = NULL, it = NULL, next = Ls->first;

	while (next != NULL) {
		prev = it;
		it = next;
		next = next->next;
		it->next = prev;
		if (next == Ls->first) {
			return TRUE;
		}
	}
	return FALSE;
}
