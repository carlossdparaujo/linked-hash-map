#include <stdio.h>
#include <stdlib.h>
#include "linkedhashmap.h"

// fator de carga
// tamanho inicial

LinkedHashMap* createLinkedHashMap(int hashSize) 
{
	LinkedHashMap* linkedHashMap = (LinkedHashMap*) malloc(sizeof(LinkedHashMap));
	linkedHashMap->hashSize = hashSize;
	linkedHashMap->hash = (Node*) malloc(sizeof(Node)*linkedHashMap->hashSize);

	int i;
	for (i = 0; i < linkedHashMap->hashSize; ++i) 
	{
		linkedHashMap->hash[i].next = &(linkedHashMap->hash[i+1]);
	}

	return linkedHashMap;
}

int hash(float value, int hashSize) 
{
	int hashedValue = (int) value*(value + 3);
	return (hashedValue) % hashSize;
}

void put(LinkedHashMap* linkedHashMap, float value) 
{	
	int index = hash(value, linkedHashMap->hashSize);
	Node* linkedList = &linkedHashMap->hash[index];

	if (linkedList->bucket == NULL) {
		linkedList->bucket = (Element*) malloc(sizeof(Element));
	}

	linkedList->bucket[0].value = value;
}

Element* get(LinkedHashMap* linkedHashMap, float value) 
{	
	int index = hash(value, linkedHashMap->hashSize);
	Element* bucket = linkedHashMap->hash[index].bucket;

	if (bucket == NULL) {
		return NULL;
	}

	return &(bucket[0]);
}
