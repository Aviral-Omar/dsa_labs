/* linkedlist.c */
#include "linkedlist.h"

void insertFirst(LinkedList *head, int ele)
{
	//create a node
	Node link = (Node)malloc(sizeof(struct node)); /* by this you are creating a node whose address is being stored in the link pointer. */
	link->element = ele;
	//point it to old first node
	link->next = head->first;
	//point first to new first node
	head->first = link;
	head->count++;
}

//delete first item
Node deleteFirst(LinkedList *head)
{
	// exercise to implement this operation.
	Node temp = head->first;
	head->first = temp->next;
	head->count--;
	return temp;
}

//display the list
void printList(LinkedList *head, int size)
{
	Node ptr = head->first;
	printf("\n[ ");
	//start from the beginning
	for (int i = 0; i < size; i++) {
		printf("%d, ", ptr->element);
		ptr = ptr->next;
	}
	printf(" ]");
}

int search(LinkedList *head, int ele)
{
	Node ptr = head->first;
	while (ptr != NULL) {
		if (ptr->element == ele) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

void deleteNode(LinkedList *head, int ele)
{
	Node ptr = head->first;
	if (ptr->element == ele) {
		head->first = ptr->next;
		free(ptr);
	}
	Node prev = ptr;
	ptr = ptr->next;
	do {
		if (ptr->element == ele) {
			prev->next = ptr->next;
			free(ptr);
		}
		prev = ptr;
		ptr = ptr->next;
	} while (ptr != NULL);
	printf("Element not found");
}

LinkedList *createList(int size)
{
	int r;
	LinkedList *Ls = (LinkedList *)myalloc(sizeof(LinkedList));
	Node h = (Node)myalloc(sizeof(struct node));
	r = rand() % (50001);
	Ls->first = h;
	h->element = r;
	int i = 1;
	while (i < size) {
		h->next = (Node)myalloc(sizeof(struct node));
		h = h->next;
		r = rand() % (50001);
		h->element = r;
		i++;
	}
	h->next = NULL;
	FILE *fp = fopen("output.txt", "w");
	fprintf(fp, "%d", space);
	fclose(fp);
	return Ls;
}

LinkedList *createCycle(LinkedList *Ls, int size)
{
	int toss = rand() & 1;
	if (!toss) {
		return Ls;
	}
	int r = rand() % size;
	Node ad;
	Node it = Ls->first;
	int i = 0;
	while (it->next != NULL) {
		i++;
		if (i == r) {
			ad = it;
		}
		it = it->next;
	}
	it->next = ad;
	return Ls;
}
