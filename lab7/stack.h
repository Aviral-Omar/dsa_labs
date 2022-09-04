#include "emp.h"

#ifndef STACK_H
#define STACK_H

typedef struct pair {
	int l;
	int r;
	struct pair* next;
} Pair;


typedef struct {
	Pair* top;
	int size;
} PairStack;

PairStack* newStack();
void push(PairStack* stack, int a, int b);
void pop(PairStack* stack);
Pair top(PairStack* stack);
int isEmpty(PairStack* stack);
#endif
