#include <stdio.h>
#include <stdlib.h>

typedef struct node *Node;

struct node {
	int value;
	Node leftNode;
	Node rightNode;
	int heightBalance;
};

int max(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}

int findHeight(Node z)
{
	if (z == NULL) {
		return -1;
	} else {
		return 1 + max(findHeight(z->leftNode), findHeight(z->rightNode));
	}
}

void printInOrder(Node root)
{
	if (root == NULL)
		return;

	printInOrder(root->leftNode);
	printf("%d\n", root->value);
	printInOrder(root->rightNode);
}

Node rotate(Node root, Node x, Node y, Node z, Node parent)
{
	Node t0, t1, t2, t3, a, b, c;

	if (!((z->leftNode == y) || (z->rightNode == y)) || !((y->leftNode == x) || (y->rightNode == x)))
		return root;

	if (z->leftNode == y) {
		c = z;
		t3 = z->rightNode;
		if (y->leftNode == x) {
			t0 = x->leftNode;
			t1 = x->rightNode;
			t2 = y->rightNode;
			b = y;
			a = x;
		} else if (y->rightNode == x) {
			t0 = y->leftNode;
			t1 = x->leftNode;
			t2 = x->rightNode;
			a = y;
			b = x;
		}
	} else if (z->rightNode == y) {
		a = z;
		t0 = z->leftNode;
		if (y->rightNode == x) {
			t1 = y->leftNode;
			t2 = x->leftNode;
			t3 = x->rightNode;
			b = y;
			c = x;
		} else if (y->leftNode == x) {
			t1 = x->leftNode;
			t2 = x->rightNode;
			t3 = y->rightNode;
			b = x;
			c = y;
		}
	}

	if (root == z || parent == NULL) {
		root = b;
	} else {
		if (parent->leftNode == z)
			parent->leftNode = b;
		else
			parent->rightNode = b;
	}

	a->leftNode = t0;
	a->rightNode = t1;
	c->leftNode = t2;
	c->rightNode = t3;
	b->leftNode = a;
	b->rightNode = c;

	int h0 = findHeight(t0);
	int h1 = findHeight(t1);
	int h2 = findHeight(t2);
	int h3 = findHeight(t3);

	a->heightBalance = h0 - h1;
	c->heightBalance = h2 - h3;
	b->heightBalance = max(h0, h1) - max(h2, h3);

	return root;
}

Node newNode(int value)
{
	Node newN = (Node)malloc(sizeof(struct node));
	newN->leftNode = NULL;
	newN->rightNode = NULL;
	newN->value = value;
	newN->heightBalance = 0;
	return newN;
}

Node add(Node root, int value, Node p)
{
	if (root == NULL) {
		return newNode(value);
	}

	Node parent = p;

	if (value < root->value) {
		root->leftNode = add(root->leftNode, value, root);
	} else if (value > root->value) {
		root->rightNode = add(root->rightNode, value, root);
	}

	root->heightBalance = findHeight(root->leftNode) - findHeight(root->rightNode);
	if (root->heightBalance > 1 && value < root->leftNode->value) {
		root = rotate(root, root->leftNode->leftNode, root->leftNode, root, parent);
	} else if (root->heightBalance > 1 && value > root->leftNode->value) {
		root = rotate(root, root->leftNode->rightNode, root->leftNode, root, parent);
	} else if (root->heightBalance < -1 && value < root->rightNode->value) {
		root = rotate(root, root->rightNode->leftNode, root->rightNode, root, parent);
	} else if (root->heightBalance < -1 && value > root->rightNode->value) {
		root = rotate(root, root->rightNode->rightNode, root->rightNode, root, parent);
	}

	return root;
}

Node find(Node root, int value)
{
	if (root == NULL) {
		printf("Node with %d value not present\n", value);
		return NULL;
	}

	if (root->value == value) {
		printf("Node with value %d is present\n", value);
		return root;
	}

	if (value < root->value)
		return find(root->leftNode, value);

	return find(root->rightNode, value);
}

Node deleteNode(Node root, int value, Node p)
{
	if (root == NULL) {
		return NULL;
	}

	Node parent = p;

	if (value < root->value) {
		root->leftNode = deleteNode(root->leftNode, value, root);
	} else if (value > root->value) {
		root->rightNode = deleteNode(root->rightNode, value, root);
	} else {
		if (root->leftNode == NULL) {
			Node temp = root->rightNode;
			free(root);
			return temp;
		} else if (root->rightNode == NULL) {
			Node temp = root->leftNode;
			free(root);
			return temp;
		} else {
			Node temp = root->rightNode;
			while (temp->leftNode != NULL) {
				temp = temp->leftNode;
			}
			root->value = temp->value;
			root->rightNode = deleteNode(root->rightNode, temp->value, root);
		}
	}

	root->heightBalance = findHeight(root->leftNode) - findHeight(root->rightNode);
	if (root->heightBalance > 1 && value < root->leftNode->value) {
		root = rotate(root, root->leftNode->leftNode, root->leftNode, root, parent);
	} else if (root->heightBalance > 1 && value > root->leftNode->value) {
		root = rotate(root, root->leftNode->rightNode, root->leftNode, root, parent);
	} else if (root->heightBalance < -1 && value < root->rightNode->value) {
		root = rotate(root, root->rightNode->leftNode, root->rightNode, root, parent);
	} else if (root->heightBalance < -1 && value > root->rightNode->value) {
		root = rotate(root, root->rightNode->rightNode, root->rightNode, root, parent);
	}

	return root;
}

int main()
{
	Node tree;

	tree = newNode(6);
	tree = add(tree, 4, NULL);
	tree = add(tree, 2, NULL);
	tree = add(tree, 5, NULL);

	printf("Root: %d, Root->leftNode: %d, Root->rightNode: %d\n", tree->value, tree->leftNode->value, tree->rightNode->value);
	printInOrder(tree);
	tree = deleteNode(tree, 4, NULL);
	printf("Root: %d, Root->leftNode: %d, Root->rightNode: %d\n", tree->value, tree->leftNode->value, tree->rightNode->value);
	printInOrder(tree);

	return 0;
}
