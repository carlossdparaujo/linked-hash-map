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

void removeOldestNode(LinkedHashMap* linkedHashMap) 
{
	Node* oldest = linkedHashMap->oldest;
	linkedHashMap->oldest = oldest->next;
	linkedHashMap->oldest->previous = NULL;

	oldest = NULL;
}

void removeNewestNode(LinkedHashMap* linkedHashMap) 
{
	Node* newest = linkedHashMap->newest;
	linkedHashMap->newest = newest->previous;
	linkedHashMap->newest->next = NULL;

	newest = NULL;
}

void delete(LinkedHashMap* linkedHashMap, int key) 
{
	int index = hash(key, linkedHashMap->hashSize);
	LinkedList* bucket = &linkedHashMap->linkedList[index];

	if (bucket->head == NULL) 
	{
		return;
	}

	Node* currentNode = bucket->head;
	while (currentNode->element->key != key)
	{
		currentNode = currentNode->nextOnBucket;

		if (currentNode == NULL) 
		{
			return;
		}
	}

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

	if (currentNode == linkedHashMap->oldest && currentNode == linkedHashMap->newest) 
	{
		linkedHashMap->oldest = NULL;
		linkedHashMap->newest = NULL;
	} 
	else if (currentNode == linkedHashMap->oldest) 
	{
		removeOldestNode(linkedHashMap);
	} 
	else if (currentNode == linkedHashMap->newest)
	{
		removeNewestNode(linkedHashMap);
	} 
	else 
	{
		currentNode->previous->next = currentNode->next;
		currentNode->next->previous = currentNode->previous;
	}

	free(currentNode);
	currentNode = NULL;
}

void updateOldestAndNewestNodePointer(LinkedHashMap* linkedHashMap, Node* currentNode) 
{
	if (linkedHashMap->oldest == NULL && linkedHashMap->newest == NULL) 
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

	Node* currentNode = (Node*) malloc(sizeof(Node));
	currentNode->previous = NULL;
	currentNode->next = NULL;
	currentNode->nextOnBucket = NULL;
	currentNode->previousOnBucket = NULL;

	currentNode->element = (Element*) malloc(sizeof(Element));
	currentNode->element->key = key;
	currentNode->element->value = value;

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

	if (bucket->head == NULL) {
		return NULL;
	}

	Node* node = bucket->head;
	while (node->element->key != key)
	{
		node = node->nextOnBucket;

		if (node == NULL) 
		{
			return NULL;
		}
	}

	return node->element;
}
