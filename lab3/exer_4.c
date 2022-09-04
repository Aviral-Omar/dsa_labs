#define N 10000000
#include <sys/time.h>
#include <time.h>
#include "cycle.h"

int main()
{
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL);

	srand(time(0));
	LinkedList* Ls = createList(N);
	Ls = createCycle(Ls, N);
	int cycle = testCyclic(Ls);
	printf("%s\n", (cycle ? "Cyclic" : "Linear"));
	if (!cycle) {
		Node it = Ls->first, temp;

		while (it != NULL) {
			temp = it;
			it = it->next;
			myfree((void*)temp, sizeof(struct node));
		}
		myfree((void*)Ls, sizeof(LinkedList));
	}


	gettimeofday(&t2, NULL);

	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
	printf("Total time is %lf ms.\n", elapsedTime);


	return 0;
}
