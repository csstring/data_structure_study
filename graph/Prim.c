#include "linkedgraph.h"
#include <stdio.h>
#include "algorithm.h"

void	minweightelement(LinkedList	*node, LinkedGraph	*prim, int fromID)
{
	ListNode	*min;
	ListNode	*temp;

	temp = node->headerNode.pLink;
	min = temp;
	while (temp)
	{
		if (min->weight >= temp->weight)
		{
			removeEdgeLG(prim, fromID, temp->vertexID);
			addVertexLG(prim, fromID);
			addVertexLG(prim, temp->vertexID);
			addEdgewithWeightLG(prim, fromID, temp->vertexID, temp->weight);
			if (!cycle_check(prim))
				removeEdgeLG(prim, fromID, temp->vertexID);
			else
				min = temp;
		}
		temp = temp->pLink;
	}
}
void	do_prim(LinkedGraph *origin, LinkedGraph *prim)
{
	int	i = 0;

	while (i < origin->maxVertexCount)
	{
		minweightelement(origin->ppAdjEdge[i], prim, i);
		i++;
	}
}

int	main(void)
{
	LinkedGraph	*origin;
	LinkedGraph *prim;

	prim = createLinkedGraph(MAX_COUNT);
	origin = init_origin_graph(UNDIRECTED);
	displayLinkedGraph(origin);
	do_prim(origin, prim);
	displayLinkedGraph(prim);
	return (0);
}