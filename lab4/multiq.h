#include "que.h"

typedef struct multiq {
	Queue* head;
	int size;
} * MultiQ;

typedef int Priority;

typedef struct {
	int tid;
	Priority p;
} Task;


MultiQ createMQ(int num);

MultiQ addMQ(MultiQ mq, Task t);

Task nextMQ(MultiQ mq);

MultiQ delNextMQ(MultiQ mq);

Boolean isEmptyMQ(MultiQ mq);

int sizeMQ(MultiQ mq);

int sizeMQbyPriority(MultiQ mq, Priority p);

Queue getQueueFromMQ(MultiQ mq, Priority p);
