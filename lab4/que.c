#include "que.h"

Queue newQ()
{
	Queue q = (Queue)malloc(sizeof(struct queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
}

Boolean isEmptyQ(Queue q)
{
	return q->front == NULL;
}

Queue delQ(Queue q)
{
	QueueNode node = q->front;
	q->front = q->front->next;
	q->size--;
	free(node);
	return q;
}

int front(Queue q)
{
	return q->front->e;
}

Queue addQ(Queue q, int e)
{
	Queue q1 = (Queue)malloc(sizeof(struct queue));
	q1->rear = (QueueNode)malloc(sizeof(struct queuenode));
	q1->rear->e = e;
	q1->rear->next = NULL;
	if (!isEmptyQ(q)) {
		q->rear->next = q1->rear;
		q1->front = q->front;
	} else {
		q1->front = q1->rear;
	}
	q1->size = q->size + 1;
	free(q);
	return q1;
}

int lengthQ(Queue q)
{
	return q->size;
}
