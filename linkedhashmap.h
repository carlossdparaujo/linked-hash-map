typedef struct _Element 
{
	float value;	
} Element;

typedef struct _Node 
{
	Element *bucket;	
	struct _Node* next;
} Node;

typedef struct _LinkedHashMap 
{
	Node* hash;
	int hashSize;
} LinkedHashMap;

LinkedHashMap* createLinkedHashMap(int hashSize);
void put(LinkedHashMap* linkedHashMap, float value);
Element* get(LinkedHashMap* linkedHashMap, float value);
