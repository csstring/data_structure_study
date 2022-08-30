#include "algorithm.h"
#include "heap.h"
#include "linkedlist.h"
#include <stdio.h>

Heap	*get_minheap(LinkedGraph *pGraph)
{
	Heap		*pHeap;
	HeapNode	element;
	ListNode	*to_node;
	int	i = 0;
	int	k = 0;

	pHeap = makeHeap(MAX_COUNT);
	while (i < pGraph->maxVertexCount)
	{
		to_node = pGraph->ppAdjEdge[i]->headerNode.pLink;
		while (to_node)
		{
			element.data = to_node->weight;
			element.fromVertexID = i;
			element.toVertexID = to_node->vertexID;
			element.visit = 0;
			insertMinHeap(pHeap, element);
			to_node = to_node->pLink;
		}
		i++;
	}
	return (pHeap);
}

LinkedGraph	*kruskal_do(Heap *pHeap)
{
	LinkedGraph	*kruskal;
	HeapNode	*temp;

	kruskal = createLinkedGraph(MAX_COUNT);
	while (!isHeapEmpty(pHeap))
	{
		temp = deleteMinHeap(pHeap);
		addVertexLG(kruskal, temp->fromVertexID);
		addVertexLG(kruskal, temp->toVertexID);
		addEdgewithWeightLG(kruskal, temp->fromVertexID, temp->toVertexID, temp->data);
		if (!cycle_check(kruskal))
			removeEdgeLG(kruskal, temp->fromVertexID, temp->toVertexID);
	}
	return (kruskal);
}

int	main(void)
{
	Heap	*pHeap;
	LinkedGraph	*origin;
	LinkedGraph *kruskal;

	origin = init_origin_graph();
	pHeap = get_minheap(origin);
	displayLinkedGraph(origin);
	kruskal = kruskal_do(pHeap);
	displayLinkedGraph(kruskal);
	return (0);
}