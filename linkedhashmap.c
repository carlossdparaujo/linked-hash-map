#include <stdio.h>
#include <stdlib.h>
#include "linkedhashmap.h"

LinkedHashMap createLinkedHashMap(void) 
{
	LinkedHashMap linkedHashMap = (LinkedHashMap) malloc(sizeof(LinkedHashMap));
	return linkedHashMap;
}