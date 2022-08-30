#include "algorithm.h"
#include "heap.h"
#include "linkedlist.h"

int	dfs_recursive_edge(int fromVertexID, int toVertexID, LinkedGraph *pGraph, int start_ID)
{
	ListNode*	temp;

	if (toVertexID == start_ID)
		return (FAIL);
	getLLElement(pGraph->ppAdjEdge[fromVertexID], \
				findGraphNodePosition(pGraph->ppAdjEdge[fromVertexID], toVertexID))->visit = 1;
	getLLElement(pGraph->ppAdjEdge[toVertexID], \
				findGraphNodePosition(pGraph->ppAdjEdge[toVertexID], fromVertexID))->visit = 1;
	temp = pGraph->ppAdjEdge[toVertexID]->headerNode.pLink;
	while (temp)
	{
		if (!temp->visit)
		{
			if (dfs_recursive_edge(toVertexID, temp->vertexID, pGraph, start_ID) == FAIL)
				return (FAIL);
		}
		temp = temp->pLink;
	}
	return (SUCCESS);
}

void	node_visit_clear(LinkedGraph *pGraph)
{
	int	i = 0;
	ListNode*	temp;

	while (i < pGraph->maxVertexCount)
	{
		temp = pGraph->ppAdjEdge[i]->headerNode.pLink;
		while (temp)
		{
			temp->visit = 0;
			temp = temp->pLink;
		}
		i++;
	}
}

int	cycle_check(LinkedGraph *kruskal)
{
	int	i = 0;
	int	result = SUCCESS;
	ListNode	*to_node;

	if (isEmptyLG(kruskal))
		return (FAIL);
	while (i < kruskal->maxVertexCount)
	{
		to_node = kruskal->ppAdjEdge[i]->headerNode.pLink;
		if (to_node)
		{	
			result = dfs_recursive_edge(i, to_node->vertexID, kruskal, i);
			node_visit_clear(kruskal);
		}
		if (result == FAIL)
			return (FAIL);
		i++;
	}
	return(SUCCESS);
}

LinkedGraph	*init_origin_graph(void)
{
	LinkedGraph	*temp;
	int	i = 0;

//	temp = createLinkedGraph(MAX_COUNT);
	temp = createLinkedDirectedGraph(MAX_COUNT);
	while (i < MAX_COUNT)
		addVertexLG(temp, i++);
	addEdgewithWeightLG(temp, 0, 1, 4);
	addEdgewithWeightLG(temp, 0, 2, 3);
	addEdgewithWeightLG(temp, 1, 2, 2);
	addEdgewithWeightLG(temp, 2, 3, 1);
	addEdgewithWeightLG(temp, 3, 4, 1);
	addEdgewithWeightLG(temp, 3, 5, 5);
	addEdgewithWeightLG(temp, 5, 4, 6);
	return (temp);
}