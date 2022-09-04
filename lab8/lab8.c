#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(unsigned char* str, int baseNumber, int tableSize)
{
	int hash = 0;
	for (int i = 0; i < strlen(str); i++) {
		hash += str[i];
		hash %= baseNumber;
	}
	hash = hash % tableSize;
	return hash;
}

int collisionCount(unsigned char* arr[], int len, int baseNumber, int tableSize)
{
	int seenHashes[tableSize];

	int collisions = 0;
	int hashValue;
	for (int i = 0; i < len; i++) {
		hashValue = hash(arr[i], baseNumber, tableSize);

		if (seenHashes[hashValue]) {
			collisions++;
		} else {
			seenHashes[hashValue] = 1;
		}
	}

	return collisions;
}

unsigned char** validStrings(unsigned char* filename, int* len)
{
	int currSize = 10;
	unsigned char** arr = (unsigned char**)malloc(sizeof(unsigned char*) * currSize);

	FILE* fp = fopen(filename, "r");

	unsigned char currString[10000] = {};

	int validCount = 0;

	int asd = 0;


	while (fscanf(fp, "%s ", currString) != EOF) {
		arr[validCount] = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(currString) + 1));
		strcpy(arr[validCount], currString);
		validCount++;

		if (validCount >= currSize) {
			currSize *= 2;
			arr = (unsigned char**)realloc(arr, sizeof(unsigned char*) * currSize);
		}
	}

	*len = validCount;
	fclose(fp);

	printf("Number of valid strings: %d\n", validCount);
	return arr;
}

int profiler(unsigned char** strArr, int len, int tableSizes[3], int baseNumbers[3][6])
{
	int collisions[18];
	int coll;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			coll = collisionCount(strArr, len, baseNumbers[i][j], tableSizes[i]);
			printf("Table Size:%d Base Number:%d Collision Count:%d\n", tableSizes[i], baseNumbers[i][j], coll);
			collisions[6 * i + j] = coll;
		}
	}

	int minIndex = 0;
	int min = collisions[0];
	for (int i = 0; i < 18; i++) {
		if (collisions[i] < min) {
			min = collisions[i];
			minIndex = i;
		}
	}
	printf("Best Parameters - Table Size: %d Base Number: %d Collisions: %d\n", tableSizes[minIndex / 6], baseNumbers[minIndex / 6][minIndex % 6], min);
	return minIndex;
}

typedef struct node Node;
struct node {
	int firstIndex;
	int count;
	Node* next;
};

typedef struct hashtable HashTable;
struct hashtable {
	int tableSize;
	int baseNumber;
	Node** table;
	int elementCount;
	int insertionCost;
	int queryingCost;
};

Node* newNode()
{
	Node* node = malloc(sizeof(Node));
	node->firstIndex = 0;
	node->count = 0;
	node->next = NULL;
	return node;
}

HashTable* newHashTable(int tableSize, int baseNumber)
{
	HashTable* ht = malloc(sizeof(HashTable));
	ht->tableSize = tableSize;
	ht->baseNumber = baseNumber;
	ht->table = malloc(sizeof(Node*) * tableSize);
	for (int i = 0; i < tableSize; i++) {
		ht->table[i] = NULL;
	}
	ht->elementCount = 0;
	ht->insertionCost = 0;
	ht->queryingCost = 0;
	return ht;
}

void insert(unsigned char** arr, int index, HashTable* ht)
{
	int hashValue = hash(arr[index], ht->baseNumber, ht->tableSize);

	if (ht->table[hashValue] == NULL) {
		Node* node = newNode();
		node->count = 1;
		node->firstIndex = index;
		ht->tableSize++;
		ht->table[hashValue] = node;
	} else {
		int asd = 0;
		Node* current = ht->table[hashValue];
		while (current->next != NULL && strcmp(arr[index], arr[current->firstIndex])) {
			ht->insertionCost++;
			current = current->next;
		}
		if (!strcmp(arr[index], arr[current->firstIndex])) {
			current->count++;
		} else {
			Node* node = newNode();
			node->count = 1;
			node->firstIndex = index;
			ht->tableSize++;
			current->next = node;
		}
	}
}

int insertAll(unsigned char** arr, int size, HashTable* ht)
{
	for (int i = 0; i < size; i++) {
		insert(arr, i, ht);
	}
	return ht->insertionCost;
}

Node* lookup(unsigned char** arr, int index, HashTable* ht)
{
	int hashValue = hash(arr[index], ht->baseNumber, ht->tableSize);

	Node* curr = ht->table[hashValue];
	while (curr && strcmp(arr[index], arr[curr->firstIndex])) {
		ht->queryingCost++;
		curr = curr->next;
	}

	return curr;
}

int lookupAll(unsigned char** arr, int size, HashTable* ht, double m)
{
	ht->queryingCost = 0;

	for (int i = 0; i < (int)(m * size); i++) {
		lookup(arr, i, ht);
	}
	return ht->queryingCost;
}

void freeHashTable(HashTable* ht, int tableSize)
{
	Node *curr, *prev;
	for (int i = 0; i < tableSize; i++) {
		curr = ht->table[i];
		while (curr) {
			prev = curr;
			curr = curr->next;
			free(prev);
		}
	}
	free(ht->table);
	free(ht);
}


int main(int argc, unsigned char* argv[])
{
	int tableSizes[] = {5000, 50000, 500000};
	int baseNumbers[3][6] = {{5209, 6277, 6997, 6010523, 6013627, 6018659}, {50021, 50023, 50033, 50000017, 50000021, 50000047}, {500009, 500029, 500041, 500000003, 500000009, 500000041}};

	int len;
	unsigned char* filename = argv[1];
	unsigned char** strArr = validStrings(filename, &len);

	int bestIndex = profiler(strArr, len, tableSizes, baseNumbers);
	int tableSize = tableSizes[bestIndex / 6];
	int baseNumber = baseNumbers[bestIndex / 6][bestIndex % 6];

	HashTable* hashTable = newHashTable(tableSize, baseNumber);

	printf("Insertion Cost: %d\n", insertAll(strArr, len, hashTable));
	printf("Count of element 5: %d\n", lookup(strArr, 4, hashTable)->count);
	printf("Querying Cost of 80%% strings: %d\n", lookupAll(strArr, len, hashTable, 0.8));

	free(strArr);
	freeHashTable(hashTable, tableSize);
	return 0;
}
