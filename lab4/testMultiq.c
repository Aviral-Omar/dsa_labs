#include <sys/time.h>
#include "multiq.h"

MultiQ loadData(FILE* f)
{
	MultiQ mq = createMQ(10);

	while (!feof(f)) {
		Task t;
		fscanf(f, "%d", &t.tid);
		fgetc(f);
		fscanf(f, "%d", &t.p);
		fgetc(f);
		addMQ(mq, t);
	}
	fclose(f);
	return mq;
}

MultiQ testDel(MultiQ mq, int num)
{
	while (num--) {
		delNextMQ(mq);
	}
}

int main()
{
	struct timeval t1, t2, t3;
	double tt1, tt2;
	gettimeofday(&t1, NULL);

	MultiQ mq = loadData(fopen("input10000.txt", "r"));
	gettimeofday(&t2, NULL);

	int num = 5000;
	testDel(mq, num);

	gettimeofday(&t3, NULL);

	// compute and print the elapsed time in millisec
	tt1 = (t2.tv_sec - t1.tv_sec) * 1000.0;
	tt1 += (t2.tv_usec - t1.tv_usec) / 1000.0;
	tt2 = (t3.tv_sec - t2.tv_sec) * 1000.0;
	tt2 += (t3.tv_usec - t2.tv_usec) / 1000.0;
	printf("Total time taken for adding elements is %lf ms.\n", tt1);
	printf("Total time taken for deleting elements is %lf ms.\n", tt2);
	printf("Average time taken for deleting an element is %lf ms.\n", tt2 / num);

	for (int i = 0; i < 10; i++) {
		while (!isEmptyQ(mq->head[i])) {
			delQ(mq->head[i]);
		}
		free(mq->head[i]);
	}
	free(mq->head);
	free(mq);

	return 0;
}
