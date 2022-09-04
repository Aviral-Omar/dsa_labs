#include "cycle.h"

int testCyclic(LinkedList* Ls)
{
	Node hare = Ls->first, tort = Ls->first;
	while (hare && hare->next) {
		tort = tort->next;
		hare = hare->next->next;
		if (hare == tort) {
			return TRUE;
		}
	}
	return FALSE;
}
