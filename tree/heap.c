#include "arraylist.h"
#include "heap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void	recreate(ArrayList **pList)
{
	ArrayList	*temp;

	temp = createArrayList((*pList)->maxElementCount * 2);
	temp->currentElementCount = (*pList)->currentElementCount;
	memcpy(temp->pElement, (*pList)->pElement, \
	sizeof(ArrayListNode) * (*pList)->maxElementCount);
	free((*pList)->pElement);
	free(*pList);
	*pList = temp;
}

int	insertMaxHeap(ArrayList **pList, ArrayListNode element)
{
	ArrayList	*list;
	int	i;

	if (isArrayListFull(*pList))
		recreate(pList);
	list = *pList;
	i = list->currentElementCount + 1;
	list->pElement[i] = element;
	while (i != 1 && element.data > list->pElement[i/2].data)
	{
		list->pElement[i] = list->pElement[i / 2];
		i = i / 2;
	}
	list->pElement[i] = element;
	list->currentElementCount++;
	return (TRUE);
}

int	deleteMaxHeap(ArrayList *pList)
{
	int	parent;
	int	child;

	if (!pList || pList->currentElementCount == 0)
		return (FALSE);
	pList->pElement[0] = pList->pElement[pList->currentElementCount];
	pList->currentElementCount--;
	parent = 1;
	child = 2;
	while (child <= pList->currentElementCount)
	{
		if (child < pList->currentElementCount && \
		pList->pElement[child].data < pList->pElement[child + 1].data)
			child++;
		if (pList->pElement[0].data >= pList->pElement[child].data)
			break ;
		pList->pElement[parent] = pList->pElement[child];
		parent = child;
		child = child * 2;
	}
	pList->pElement[parent] = pList->pElement[0];
	return (TRUE);
}

int	main(void)
{
	ArrayList	*heap;
	ArrayListNode	temp[10];
	int	i;

	i = 0;
	while (i < 10)
	{
		temp[i].data = i;
		i++;
	}
	i = 0;
	heap = createArrayList(128);
	while (i < 10)
		insertMaxHeap(&heap, temp[i++]);
	i = 0;
	while (i < 10)
		printf("%d\n", heap->pElement[i++].data);
	while (deleteMaxHeap(heap));
}