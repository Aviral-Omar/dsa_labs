/* linkedlist.h */
#include <stdio.h>
#include <stdlib.h>

#include "def.h"

// structure definitions
// structure of a linked list node. It contains an element
typedef struct node* Node;
struct node {
	int element;
	Node next;
};
/* structure of a linked list / head. It stores the count of number of elements
in the list and also a pointer link to the first node of the list. */
typedef struct linkedList {
	int count;
	Node first;
} LinkedList;
// function declarations
void insertFirst(LinkedList* head, int ele);
/* inserts a given element at the beginning of the list */
Node deleteFirst(LinkedList* head);
/* deletes the first element of the list and returns pointer to the deleted
node. */
void printList(LinkedList* head, int size);
/* prints all the elements in the list */
int search(LinkedList* head, int ele);
/* searches for a given element in the linked list. Returns 1 if found, 0
otherwise. */
void deleteNode(LinkedList* head, int ele);
/* deletes the first node in the list that contains the element = ele and
retuns it. If the element is not found it returns an error message saying
element not found. */
/* End of linkedlist.h */
LinkedList* createList(int size);

LinkedList* createCycle(LinkedList* Ls, int size);
