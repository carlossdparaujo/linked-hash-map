#include <stdio.h>
#include "linkedhashmap.h"
#include "CUnitForAndo/include/testRunner.h"

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testPutNewItemOnEmptyMap_ShouldBecomeHeadAndTailAndOldestAndNewest(void) 
{
	int key = 0;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, key, 5.0);

	Element* element = get(linkedHashMap, key);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, key);
	TEST_ASSERT(linkedHashMap->oldest->element == element);
	TEST_ASSERT(linkedHashMap->newest->element == element);
	// Index calculated using a h(x, m) = x*(x + 2) % m hash function
	TEST_ASSERT(linkedHashMap->linkedList[0].head->element == element);
	TEST_ASSERT(linkedHashMap->linkedList[0].tail->element == element);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testPutTwoItensOnMap_SecondItemShouldBecomeTailAndNewestAndFirstShouldBecomeHeadAndOldest(void) 
{
	int firstKey = 0;
	int secondKey = 40;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, firstKey, 8.0);
	put(linkedHashMap, secondKey, 9.0);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, firstKey);
	TEST_ASSERT(linkedHashMap->oldest->element == element);
	TEST_ASSERT(linkedHashMap->newest->element != element);
	// Index calculated using a h(x, m) = x*(x + 2) % m hash function
	TEST_ASSERT(linkedHashMap->linkedList[0].head->element == element);
	TEST_ASSERT(linkedHashMap->linkedList[0].tail->element != element);

	element = get(linkedHashMap, secondKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);
	TEST_ASSERT(linkedHashMap->newest->element == element);
	TEST_ASSERT(linkedHashMap->oldest->element != element);
	// Index calculated using a h(x, m) = x*(x + 2) % m hash function
	TEST_ASSERT(linkedHashMap->linkedList[0].tail->element == element);
	TEST_ASSERT(linkedHashMap->linkedList[0].head->element != element);

	return 0;
}

unsigned int testGetItemThatDoesNotExist_ShouldReturnNull(void) 
{
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	Element* element = get(linkedHashMap, 5);
	TEST_ASSERT(NULL == element);

	return 0;
}

unsigned int testDeleteItem_ShouldReturnNull(void) 
{
	int keyToRemove = 5;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, keyToRemove, 9.0);
	delete(linkedHashMap, keyToRemove);

	Element* element = get(linkedHashMap, keyToRemove);
	TEST_ASSERT(NULL == element);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testOverflowHashCapacity_ShouldRemoveOldestItem(void) 
{
	int firstKey = 0; // Hash: 0
	int secondKey = 1; // Hash: 1
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 10.0);
	put(linkedHashMap, secondKey, 50.0);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL == element);

	return 0;
}

unsigned int testDeleteOldestItem_ShouldChangeOldestItem(void) 
{
	int firstKey = 0; 
	int secondKey = 1;
	int thirdKey = 2;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, firstKey, 9.0);
	put(linkedHashMap, secondKey, 9.0);
	put(linkedHashMap, thirdKey, 9.0);

	delete(linkedHashMap, firstKey);

	Element* element = get(linkedHashMap, linkedHashMap->oldest->element->key);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);

	return 0;
}

unsigned int testDeleteNewestItem_ShouldChangeNewestItem(void) 
{
	int firstKey = 0; 
	int secondKey = 1;
	int thirdKey = 2;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, firstKey, 9.0);
	put(linkedHashMap, secondKey, 9.0);
	put(linkedHashMap, thirdKey, 9.0);

	delete(linkedHashMap, thirdKey);

	Element* element = get(linkedHashMap, linkedHashMap->newest->element->key);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);

	return 0;
}

unsigned int testDeleteInBetweenItem_ShouldMaintainOldestAndNewestAndRelinkThem(void) 
{
	int firstKey = 0; 
	int secondKey = 1;
	int thirdKey = 2;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20, 0.5);

	put(linkedHashMap, firstKey, 9.0);
	put(linkedHashMap, secondKey, 9.0);
	put(linkedHashMap, thirdKey, 9.0);

	delete(linkedHashMap, secondKey);

	Element* newest = get(linkedHashMap, linkedHashMap->newest->element->key);
	TEST_ASSERT(NULL != newest);
	TEST_ASSERT_EQUALS(newest->key, thirdKey);

	Element* oldest = get(linkedHashMap, linkedHashMap->oldest->element->key);
	TEST_ASSERT(NULL != oldest);
	TEST_ASSERT_EQUALS(oldest->key, firstKey);

	TEST_ASSERT(linkedHashMap->oldest->next == linkedHashMap->newest);
	TEST_ASSERT(linkedHashMap->newest->previous == linkedHashMap->oldest);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testPutConflictingItens_ShouldMaintainBothItens(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, firstKey);

	element = get(linkedHashMap, secondKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testPutManyConflictingItens_ShouldMaintainAllItens(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, firstKey);

	element = get(linkedHashMap, secondKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);

	element = get(linkedHashMap, thirdKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, thirdKey);

	element = get(linkedHashMap, fourthKey);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, fourthKey);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testGetNonInsertedItemOnCrowdedBucket_ShouldReturnNull(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	Element* element = get(linkedHashMap, 32);
	TEST_ASSERT(NULL == element);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testDeleteItemOnBucketWithConflits_ShouldReturnNull(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	delete(linkedHashMap, secondKey);

	Element* element = get(linkedHashMap, secondKey);
	TEST_ASSERT(NULL == element);

	element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL != element);

	element = get(linkedHashMap, thirdKey);
	TEST_ASSERT(NULL != element);

	element = get(linkedHashMap, fourthKey);
	TEST_ASSERT(NULL != element);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testDeleteTailOfBucketWithConflits_ShouldReturnNullAndTailShouldChange(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	delete(linkedHashMap, fourthKey);

	Element* element = get(linkedHashMap, fourthKey);
	TEST_ASSERT(NULL == element);

	element = get(linkedHashMap, linkedHashMap->linkedList->tail->element->key);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, thirdKey);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testDeleteHeadOfBucketWithConflits_ShouldReturnNullAndHeadShouldChange(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	delete(linkedHashMap, firstKey);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL == element);

	element = get(linkedHashMap, linkedHashMap->linkedList->head->element->key);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->key, secondKey);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testDeleteNonInsertedItemOnBucketWithConflits_ShouldDoNothing(void) 
{
	int firstKey = 2; // Hash: 0
	int secondKey = 4; // Hash: 0
	int thirdKey = 8; // Hash: 0
	int fourthKey = 16; // Hash: 0
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	put(linkedHashMap, firstKey, 5.0);
	put(linkedHashMap, secondKey, 5.0);
	put(linkedHashMap, thirdKey, 5.0);
	put(linkedHashMap, fourthKey, 5.0);

	delete(linkedHashMap, 32);

	Element* element = get(linkedHashMap, firstKey);
	TEST_ASSERT(NULL != element);

	element = get(linkedHashMap, secondKey);
	TEST_ASSERT(NULL != element);

	element = get(linkedHashMap, thirdKey);
	TEST_ASSERT(NULL != element);

	element = get(linkedHashMap, fourthKey);
	TEST_ASSERT(NULL != element);

	return 0;
}

// This method is guaranteed to work with the hash function h(x, m) = x*(x + 2) % m
unsigned int testDeleteNonInsertedItemOnHash_ShouldDoNothing(void) 
{
	LinkedHashMap* linkedHashMap = createLinkedHashMap(1, 0.5);

	delete(linkedHashMap, 1);

	TEST_ASSERT(NULL == linkedHashMap->oldest);
	TEST_ASSERT(NULL == linkedHashMap->newest);

	return 0;
}

unsigned int testManyFunction(void) {

    TEST_ASSERT(!testPutNewItemOnEmptyMap_ShouldBecomeHeadAndTailAndOldestAndNewest()); 
    TEST_ASSERT(!testPutTwoItensOnMap_SecondItemShouldBecomeTailAndNewestAndFirstShouldBecomeHeadAndOldest());
    TEST_ASSERT(!testGetItemThatDoesNotExist_ShouldReturnNull());
    TEST_ASSERT(!testDeleteItem_ShouldReturnNull());
    TEST_ASSERT(!testOverflowHashCapacity_ShouldRemoveOldestItem());
    TEST_ASSERT(!testDeleteOldestItem_ShouldChangeOldestItem());
    TEST_ASSERT(!testDeleteNewestItem_ShouldChangeNewestItem());
    TEST_ASSERT(!testDeleteInBetweenItem_ShouldMaintainOldestAndNewestAndRelinkThem());
    TEST_ASSERT(!testPutConflictingItens_ShouldMaintainBothItens());
    TEST_ASSERT(!testPutManyConflictingItens_ShouldMaintainAllItens());
    TEST_ASSERT(!testGetNonInsertedItemOnCrowdedBucket_ShouldReturnNull());
    TEST_ASSERT(!testDeleteItemOnBucketWithConflits_ShouldReturnNull());
    TEST_ASSERT(!testDeleteTailOfBucketWithConflits_ShouldReturnNullAndTailShouldChange());
    TEST_ASSERT(!testDeleteHeadOfBucketWithConflits_ShouldReturnNullAndHeadShouldChange());
    TEST_ASSERT(!testDeleteNonInsertedItemOnBucketWithConflits_ShouldDoNothing());
    TEST_ASSERT(!testDeleteNonInsertedItemOnHash_ShouldDoNothing());

    return 0;
}

int main(void) 
{
	return (int) testRunner(testManyFunction);
}