/* linkedlist.c */
#include "linkedlist.h"

void insertFirst(struct linkedList *head, int ele)
{
	//create a node
	struct node *link = (struct node *)malloc(sizeof(struct node)); /* by this you are creating a node whose address is being stored in the link pointer. */
	link->element = ele;
	//point it to old first node
	link->next = head->first;
	//point first to new first node
	head->first = link;
	head->count++;
}

//delete first item
struct node *deleteFirst(struct linkedList *head)
{
	// exercise to implement this operation.
	struct node *temp = head->first;
	head->first = temp->next;
	head->count--;
	return temp;
}

//display the list
void printList(struct linkedList *head)
{
	struct node *ptr = head->first;
	printf("\n[ ");
	//start from the beginning
	while (ptr != NULL) {
		printf("%d, ", ptr->element);
		ptr = ptr->next;
	}
	printf(" ]");
}

int search(struct linkedList *head, int ele)
{
	struct node *ptr = head->first;
	while (ptr != NULL) {
		if (ptr->element == ele) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

struct node *deleteNode(struct linkedList *head, int ele)
{
	struct node *ptr = head->first;
	if (ptr->element == ele) {
		head->first = ptr->next;
		return ptr;
	}
	struct node *prev = ptr;
	ptr = ptr->next;
	do {
		if (ptr->element == ele) {
			prev->next = ptr->next;
			return ptr;
		}
		prev = ptr;
		ptr = ptr->next;
	} while (ptr != NULL);
	printf("Element not found");
	return ptr;
}
