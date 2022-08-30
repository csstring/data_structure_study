#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap* makeHeap(int maxElementCount) {
  Heap* newHeap;
  HeapNode** heapNodeArray;

  newHeap = malloc(sizeof(Heap));
  if (!newHeap)
    return (NULL);
  heapNodeArray = malloc(sizeof(HeapNode*) * (maxElementCount + 1));
  if (!heapNodeArray) {
    free(newHeap);
    return (NULL);
  }
  memset(heapNodeArray, 0, sizeof(HeapNode*) * (maxElementCount + 1));
  newHeap->HeapNodeArray = heapNodeArray;
  newHeap->maxElementCount = maxElementCount;
  newHeap->currElementCount = 0;
  return (newHeap);
}

HeapNode* makeHeapNode(HeapNode element) {
  HeapNode* newNode;

  newNode = malloc(sizeof(HeapNode));
  if (!newNode)
    return (NULL);
  newNode->data = element.data;
  newNode->fromVertexID = element.fromVertexID;
  newNode->toVertexID = element.toVertexID;
  newNode->visit = 0;
  return (newNode);
}

int isHeapEmpty(Heap* pHeap) {
  return (!pHeap || pHeap->currElementCount == 0);
}

HeapNode* getHeapRootNode(Heap* pHeap) {
  if (isHeapEmpty(pHeap))
    return (NULL);
  return (pHeap->HeapNodeArray[1]);
}

int insertMaxHeap(Heap* pHeap, HeapNode element) {
  if (pHeap->currElementCount == pHeap->maxElementCount) {
    pHeap->maxElementCount *= 2;
    HeapNode** tempArray =
        malloc(sizeof(HeapNode*) * (pHeap->maxElementCount + 1));
    if (!tempArray)
      return (FALSE);
    memset(tempArray, 0, sizeof(HeapNode*) * (pHeap->maxElementCount + 1));
    for (int i = 1; i <= pHeap->currElementCount; i++)
      tempArray[i] = pHeap->HeapNodeArray[i];
    free(pHeap->HeapNodeArray);
    pHeap->HeapNodeArray = tempArray;
  }

  HeapNode* newNode = makeHeapNode(element);
  if (!newNode)
    return (FALSE);

  pHeap->currElementCount++;
  int index = pHeap->currElementCount;

  while (index > 1 && element.data > pHeap->HeapNodeArray[index / 2]->data) {
    pHeap->HeapNodeArray[index] = pHeap->HeapNodeArray[index / 2];
    index /= 2;
  }

  pHeap->HeapNodeArray[index] = newNode;
  return (TRUE);
}

HeapNode* deleteMaxHeap(Heap* pHeap) {
  if (isHeapEmpty(pHeap))
    return (NULL);

  HeapNode* root = pHeap->HeapNodeArray[1];
  HeapNode* temp = pHeap->HeapNodeArray[pHeap->currElementCount];
  pHeap->HeapNodeArray[pHeap->currElementCount] = NULL;
  pHeap->currElementCount--;
  int parent = 1;
  int child = 2;

  while (child <= pHeap->currElementCount) {
    if (child < pHeap->currElementCount &&
        pHeap->HeapNodeArray[child]->data <
            pHeap->HeapNodeArray[child + 1]->data)
      child++;
    if (temp->data >= pHeap->HeapNodeArray[child]->data)
      break;
    pHeap->HeapNodeArray[parent] = pHeap->HeapNodeArray[child];
    parent = child;
    child *= 2;
  }

  pHeap->HeapNodeArray[parent] = temp;
  return (root);
}

int insertMinHeap(Heap* pHeap, HeapNode element) {
  if (pHeap->currElementCount == pHeap->maxElementCount) {
    pHeap->maxElementCount *= 2;
    HeapNode** tempArray =
        malloc(sizeof(HeapNode*) * (pHeap->maxElementCount + 1));
    if (!tempArray)
      return (FALSE);
    memset(tempArray, 0, sizeof(HeapNode*) * (pHeap->maxElementCount + 1));
    for (int i = 1; i <= pHeap->currElementCount; i++)
      tempArray[i] = pHeap->HeapNodeArray[i];
    free(pHeap->HeapNodeArray);
    pHeap->HeapNodeArray = tempArray;
  }

  HeapNode* newNode = makeHeapNode(element);
  if (!newNode)
    return (FALSE);

  pHeap->currElementCount++;
  int index = pHeap->currElementCount;

  while (index > 1 && element.data < pHeap->HeapNodeArray[index / 2]->data) {
    pHeap->HeapNodeArray[index] = pHeap->HeapNodeArray[index / 2];
    index /= 2;
  }

  pHeap->HeapNodeArray[index] = newNode;
  return (TRUE);
}

HeapNode* deleteMinHeap(Heap* pHeap) {
  if (isHeapEmpty(pHeap))
    return (NULL);

  HeapNode* root = pHeap->HeapNodeArray[1];
  HeapNode* temp = pHeap->HeapNodeArray[pHeap->currElementCount];
  pHeap->HeapNodeArray[pHeap->currElementCount] = NULL;
  pHeap->currElementCount--;
  int parent = 1;
  int child = 2;

  while (child <= pHeap->currElementCount) {
    if (child < pHeap->currElementCount &&
        pHeap->HeapNodeArray[child]->data >
            pHeap->HeapNodeArray[child + 1]->data)
      child++;
    if (temp->data <= pHeap->HeapNodeArray[child]->data)
      break;
    pHeap->HeapNodeArray[parent] = pHeap->HeapNodeArray[child];
    parent = child;
    child *= 2;
  }

  pHeap->HeapNodeArray[parent] = temp;
  return (root);
}

void printHeap(Heap* pHeap) {
  printf("============\n");
  if (!pHeap) {
    printf("Heap does not exist\n");
  } else if (isHeapEmpty(pHeap)) {
    printf("Heap is Empty\n");
  } else {
    for (int i = 0; i < pHeap->currElementCount; i++)
      printf("[%3d] % 3d\n", i + 1, pHeap->HeapNodeArray[i + 1]->data);
  }
}

void clearHeap(Heap** pHeap) {
  HeapNode* node;

  if (*pHeap == NULL)
    return;
  while (!isHeapEmpty(*pHeap)) {
    node = deleteMaxHeap(*pHeap);
    free(node);
  }
  free((*pHeap)->HeapNodeArray);
  free(*pHeap);
  *pHeap = NULL;
}
