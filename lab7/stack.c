#include "stack.h"

#include <stdlib.h>

PairStack* newStack()
{
	PairStack* stack = (PairStack*)malloc(sizeof(PairStack));
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void push(PairStack* stack, int a, int b)
{
	Pair* node = (Pair*)malloc(sizeof(Pair));
	node->l = a;
	node->r = b;

	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

void pop(PairStack* stack)
{
	if (isEmpty(stack)) {
		return;
	}

	stack->top = (stack->top)->next;
	(stack->size)--;
}


Pair top(PairStack* stack)
{
	Pair node;
	if (stack->size == 0) {
		node.l = -1;
		node.r = -1;
		node.next = NULL;
		return node;
	}

	node = *(stack->top);
	return node;
}

int isEmpty(PairStack* stack)
{
	return !stack->size;
}
