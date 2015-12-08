typedef struct _Element 
{
	long hash;
	int value;
} Element; 

typedef struct _Node 
{
	Element *bucket;	
	struct _Node* next;
} Node;

typedef struct _LinkedHashMap 
{
	Node* hash;
} LinkedHashMap;

LinkedHashMap createLinkedHashMap(void);
