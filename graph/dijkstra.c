#include "linkedgraph.h"
#include <stdio.h>
#include "algorithm.h"

int	get_targetnode_weight(int toVertexID, LinkedList* node)
{
	ListNode	*temp;

	temp = getLLElement(node, findGraphNodePosition(node, toVertexID));
	if (!temp)
		return (FAIL);
	return (temp->weight);
}

int	clear_bridge(ListNode *end_node ,ListNode *waypoint_node, LinkedGraph *pGraph, int start_point)
{
	int		wayToend_weight;

	wayToend_weight = get_targetnode_weight(end_node->vertexID, \
								pGraph->ppAdjEdge[waypoint_node->vertexID]);
	if (wayToend_weight != FAIL)
	{
		printf("start_point : %d waypoint : %d waytoend : %d startto_end : %d\n",start_point, waypoint_node->weight, wayToend_weight, end_node->weight);
		if (waypoint_node->weight + wayToend_weight < end_node->weight)
		{
			removeEdgeLG(pGraph, start_point, end_node->vertexID);
			return (SUCCESS);
		}
	}
	return (FAIL);
}
int near_node_weight_check(LinkedGraph *pGraph, int check_point)
{
	ListNode	*end_node;
	ListNode	*waypoint_node;

	end_node = pGraph->ppAdjEdge[check_point]->headerNode.pLink;
	while (end_node)
	{
		waypoint_node = pGraph->ppAdjEdge[check_point]->headerNode.pLink;
		while (waypoint_node)
		{
			if (end_node->vertexID == waypoint_node->vertexID)
			{
				waypoint_node = waypoint_node->pLink;
				continue;
			}
			if (clear_bridge(end_node ,waypoint_node, pGraph, check_point) == SUCCESS)
			{
				displayLinkedGraph(pGraph);
				return (SUCCESS);
			}
			waypoint_node = waypoint_node->pLink;
		}
		end_node = end_node->pLink;
	}
	return (FAIL);
}

int	getTotalWeight(LinkedGraph *pGraph)
{
	int	i = 0;
	int	totalweight = 0;
	ListNode	*temp;

	while (i < pGraph->maxVertexCount)
	{
		temp = pGraph->ppAdjEdge[i]->headerNode.pLink;
		while (temp)
		{
			totalweight += temp->weight;
			temp = temp->pLink;
		}
		i++;
	}
	if (pGraph->graphType == UNDIRECTED)
		totalweight = totalweight / 2;
	return (totalweight);
}

void	do_dijkstra(LinkedGraph *pGraph, int start_point)
{
	int	i = 0;

	while (i < pGraph->maxVertexCount)
	{
		while (near_node_weight_check(pGraph, i));
		i++;
	}
	node_visit_clear(pGraph);
}

LinkedGraph	*init_dijkstra_graph(enum e_arraygraph_type	type)
{
	LinkedGraph	*temp;
	int	i = 0;

	if (type == UNDIRECTED)
		temp = createLinkedGraph(MAX_COUNT);
	else
		temp = createLinkedDirectedGraph(MAX_COUNT);
	while (i < MAX_COUNT)
		addVertexLG(temp, i++);
	addEdgewithWeightLG(temp, 0, 1, 1);
	addEdgewithWeightLG(temp, 0, 2, 4);
	addEdgewithWeightLG(temp, 1, 2, 2);
	addEdgewithWeightLG(temp, 2, 3, 1);
	addEdgewithWeightLG(temp, 3, 4, 8);
	addEdgewithWeightLG(temp, 3, 5, 3);
	addEdgewithWeightLG(temp, 5, 4, 4);
	return (temp);
}

int	main(void)
{
	LinkedGraph	*pGraph;
	int	start_point = 0;

	pGraph = init_dijkstra_graph(UNDIRECTED);
	displayLinkedGraph(pGraph);
	do_dijkstra(pGraph, start_point);
	printf("after dijkstra\n");
	displayLinkedGraph(pGraph);
	printf("total cost : %d\n", getTotalWeight(pGraph));
}