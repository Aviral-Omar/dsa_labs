#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE,
			   TRUE } Boolean;
typedef struct queuenode* QueueNode;
struct queuenode {
	int e;
	QueueNode next;
};

typedef struct queue {
	QueueNode front;
	QueueNode rear;
	int size;
} * Queue;

Queue newQ();

Boolean isEmptyQ(Queue q);

Queue delQ(Queue q);

int front(Queue q);

Queue addQ(Queue q, int e);

int lengthQ(Queue q);
