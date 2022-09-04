#include "multiq.h"

MultiQ createMQ(int num)
{
	MultiQ mq = (MultiQ)malloc(sizeof(struct multiq));
	mq->head = (Queue*)malloc(num * sizeof(Queue));
	mq->size = num;
	for (int i = 0; i < num; i++) {
		mq->head[i] = newQ();
	}
	return mq;
}

MultiQ addMQ(MultiQ mq, Task t)
{
	*(mq->head + t.p - 1) = addQ(*(mq->head + t.p - 1), t.tid);
	return mq;
}

Task nextMQ(MultiQ mq)
{
	int i = mq->size - 1;
	Task t;
	while (i >= 0) {
		if (!isEmptyQ(mq->head[i])) {
			t.p = i + 1;
			t.tid = front(mq->head[i]);
			return t;
		}
		i--;
	}
	printf("No task queued!");
	return t;
}

MultiQ delNextMQ(MultiQ mq)
{
	int i = mq->size - 1;
	while (i >= 0) {
		if (!isEmptyQ(mq->head[i])) {
			delQ(mq->head[i]);
			break;
		}
		i--;
	}
	return mq;
}

Boolean isEmptyMQ(MultiQ mq)
{
	int i = mq->size - 1;
	while (i >= 0) {
		if (!isEmptyQ(mq->head[i])) {
			return FALSE;
		}
		i--;
	}
	return TRUE;
}

int sizeMQ(MultiQ mq)
{
	int i = mq->size - 1;
	int size = 0;
	while (i >= 0) {
		size += lengthQ(mq->head[i]);
		i--;
	}
	return size;
}

int sizeMQbyPriority(MultiQ mq, Priority p)
{
	return lengthQ(mq->head[p - 1]);
}

Queue getQueueFromMQ(MultiQ mq, Priority p)
{
	return mq->head[p - 1];
}
