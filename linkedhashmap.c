#include <stdio.h>
#include <stdlib.h>
#include "linkedhashmap.h"

LinkedHashMap* createLinkedHashMap(int capacity, float loadFactor) 
{
	LinkedHashMap* linkedHashMap = (LinkedHashMap*) malloc(sizeof(LinkedHashMap));
	linkedHashMap->hashSize = capacity/loadFactor;
	linkedHashMap->capacity = capacity;
	linkedHashMap->loadFactor = loadFactor;
	linkedHashMap->linkedList = (LinkedList*) malloc(sizeof(LinkedList)*linkedHashMap->hashSize);
	linkedHashMap->oldest = NULL;
	linkedHashMap->newest = NULL;
	linkedHashMap->currentCapacity = 0;

	int i;
	for (i = 0; i < linkedHashMap->hashSize; ++i) 
	{
		linkedHashMap->linkedList[i].head = NULL;
		linkedHashMap->linkedList[i].tail = NULL;
	}

	return linkedHashMap;
}

int hash(int key, int hashSize) 
{
	int hashedValue = key*(key + 2);
	return (hashedValue) % hashSize;
}

Node* findNode(LinkedList* bucket, int key)
{
	if (bucket->head == NULL) 
	{
		return NULL;
	}

	Node* currentNode = bucket->head;
	while (currentNode->element->key != key)
	{
		currentNode = currentNode->nextOnBucket;

		if (currentNode == NULL) 
		{
			return NULL;
		}
	}

	return currentNode;
}

void removeNodeFromBucket(LinkedList* bucket, Node* currentNode)
{
	if (currentNode == bucket->tail && currentNode == bucket->head) 
	{
		bucket->head = NULL;
		bucket->tail = NULL;
	}
	else if (currentNode == bucket->tail) 
	{
		bucket->tail = currentNode->previousOnBucket;
		bucket->tail->nextOnBucket = NULL;
	}
	else if (currentNode == bucket->head)
	{
		bucket->head = currentNode->nextOnBucket;
		bucket->head->previousOnBucket = NULL;
	} 
	else 
	{
		currentNode->previousOnBucket->nextOnBucket = currentNode->nextOnBucket;
		currentNode->nextOnBucket->previousOnBucket = currentNode->previousOnBucket;
	}
}

void removeNodeFromHashCache(LinkedHashMap* linkedHashMap, Node* currentNode)
{
	if (currentNode == linkedHashMap->oldest && currentNode == linkedHashMap->newest) 
	{
		linkedHashMap->oldest = NULL;
		linkedHashMap->newest = NULL;
	} 
	else if (currentNode == linkedHashMap->oldest) 
	{
		linkedHashMap->oldest = linkedHashMap->oldest->next;
		linkedHashMap->oldest->previous = NULL;
	} 
	else if (currentNode == linkedHashMap->newest)
	{
		linkedHashMap->newest = linkedHashMap->newest->previous;
		linkedHashMap->newest->next = NULL;
	} 
	else 
	{
		currentNode->previous->next = currentNode->next;
		currentNode->next->previous = currentNode->previous;
	}
}

void delete(LinkedHashMap* linkedHashMap, int key) 
{
	int index = hash(key, linkedHashMap->hashSize);
	LinkedList* bucket = &linkedHashMap->linkedList[index];

	Node* currentNode = findNode(bucket, key);

	if (currentNode == NULL)
	{
		return;
	}

	removeNodeFromBucket(bucket, currentNode);
	removeNodeFromHashCache(linkedHashMap, currentNode);

	free(currentNode);
	currentNode = NULL;
}

Node* createNode(int key, float value)
{
	Node* node = (Node*) malloc(sizeof(Node));
	node->previous = NULL;
	node->next = NULL;
	node->nextOnBucket = NULL;
	node->previousOnBucket = NULL;

	node->element = (Element*) malloc(sizeof(Element));
	node->element->key = key;
	node->element->value = value;

	return node;
}

void updateNodePositionOnBucket(LinkedHashMap* linkedHashMap, LinkedList* bucket, Node* currentNode) 
{
	if (bucket->head == NULL) 
	{
		bucket->head = currentNode;
		bucket->tail = currentNode;

		linkedHashMap->currentCapacity++;
	}
	else 
	{
		currentNode->previousOnBucket = bucket->tail;
		bucket->tail->nextOnBucket = currentNode;
		bucket->tail = currentNode;
	}
}

void updateOldestAndNewestNodePointer(LinkedHashMap* linkedHashMap, Node* currentNode) 
{
	if (linkedHashMap->oldest == NULL) 
	{
		linkedHashMap->oldest = currentNode;
		linkedHashMap->newest = currentNode;
	} 
	else 
	{
		Node* oldNewest = linkedHashMap->newest;
		oldNewest->next = currentNode;
		currentNode->previous = oldNewest;
		linkedHashMap->newest = currentNode;
	}
}

void put(LinkedHashMap* linkedHashMap, int key, float value) 
{	
	int index = hash(key, linkedHashMap->hashSize);
	LinkedList* bucket = &linkedHashMap->linkedList[index];

	Node* currentNode = createNode(key, value);

	updateNodePositionOnBucket(linkedHashMap, bucket, currentNode);
	updateOldestAndNewestNodePointer(linkedHashMap, currentNode);

	if (linkedHashMap->currentCapacity > linkedHashMap->capacity) 
	{
		delete(linkedHashMap, linkedHashMap->oldest->element->key);
	}
}

Element* get(LinkedHashMap* linkedHashMap, int key) 
{	
	int index = hash(key, linkedHashMap->hashSize);
	LinkedList* bucket = &linkedHashMap->linkedList[index];

	Node* currentNode = findNode(bucket, key);

	if (currentNode == NULL)
	{
		return NULL;
	}

	return currentNode->element;
}
