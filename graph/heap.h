#ifndef _HEAP_
#define _HEAP_

typedef struct HeapNodeType {
	int	data;
	int	fromVertexID;
	int toVertexID;
	int	visit;
} HeapNode;

typedef struct HeapType {
  HeapNode** HeapNodeArray;
  int maxElementCount;
  int currElementCount;
} Heap;

Heap* makeHeap(int maxElementCount);
HeapNode* makeHeapNode(HeapNode element);

int isHeapEmpty(Heap* pHeap);

HeapNode* getHeapRootNode(Heap* pHeap);

int insertMaxHeap(Heap* pHeap, HeapNode element);
int insertMinHeap(Heap* pHeap, HeapNode element);

HeapNode* deleteMaxHeap(Heap* pHeap);
HeapNode* deleteMinHeap(Heap* pHeap);

void printHeap(Heap* pHeap);

void clearHeap(Heap **pHeap);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE 1
#define FALSE 0

#endif
