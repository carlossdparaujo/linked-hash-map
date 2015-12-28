#include <stdio.h>
#include "linkedhashmap.h"
#include "CUnitForAndo/include/testRunner.h"

unsigned int testPutNewItemOnEmptyMap(void) 
{
	float valueToPut = 5;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20);

	put(linkedHashMap, valueToPut);

	Element* element = get(linkedHashMap, valueToPut);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->value, valueToPut);

	return 0;
}

unsigned int testPutTwoItensOnMap(void) 
{
	float firstValueToPut = 5;
	float secondValueToPut = 8;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20);

	put(linkedHashMap, firstValueToPut);
	put(linkedHashMap, secondValueToPut);

	Element* element = get(linkedHashMap, firstValueToPut);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->value, firstValueToPut);
	element = get(linkedHashMap, secondValueToPut);
	TEST_ASSERT(NULL != element);
	TEST_ASSERT_EQUALS(element->value, secondValueToPut);

	return 0;
}

unsigned int testGetItemThatDoesNotExist(void) 
{
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20);

	Element* element = get(linkedHashMap, 5);
	TEST_ASSERT(NULL == element);

	return 0;
}

unsigned int testRemoveItem(void) 
{
	float valueToPut = 5;
	LinkedHashMap* linkedHashMap = createLinkedHashMap(20);

	put(linkedHashMap, valueToPut);

	//float value = get(linkedHashMap, valueToPut)->value;
	//TEST_ASSERT_EQUALS(value, valueToPut);

	return 0;
}

unsigned int testManyFunction(void) {

    TEST_ASSERT(! testPutNewItemOnEmptyMap()); 
    TEST_ASSERT(! testPutTwoItensOnMap());
    TEST_ASSERT(! testGetItemThatDoesNotExist());
 
    return 0;
}

int main(void) 
{
	return (int) testRunner(testManyFunction);
}