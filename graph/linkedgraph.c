#include "linkedgraph.h"
#include <stdio.h>
#include <stdlib.h>

LinkedGraph* createLinkedGraph(int maxVertexCount)
{
	LinkedGraph	*temp;
	int	i = 0;

	if (maxVertexCount < 1)
		return (NULL);
	temp = malloc(sizeof(LinkedGraph));
	temp->pVertex = malloc(sizeof(int) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = createLinkedList();
	temp->graphType = UNDIRECTED;
	temp->currentEdgeCount = 0;
	temp->currentVertexCount = 0;
	return (temp);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
	LinkedGraph	*temp;
	int	i = 0;

	if (maxVertexCount < 1)
		return (NULL);
	temp = malloc(sizeof(LinkedGraph));
	temp->pVertex = malloc(sizeof(int) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = createLinkedList();
	temp->graphType = DIRECTED;
	temp->currentEdgeCount = 0;
	temp->currentVertexCount = 0;
	return (temp);
}

void deleteLinkedGraph(LinkedGraph* pGraph)
{
	int	i = 0;

	if (!pGraph)
		return ;
	free(pGraph->pVertex);
	while (i < pGraph->maxVertexCount)
		deleteLinkedList(pGraph->ppAdjEdge[i++]);
	free(pGraph->ppAdjEdge);
	free(pGraph);
}

int isEmptyLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	if (pGraph->currentEdgeCount == 0)
		return (TRUE);
	return (FALSE);
}

int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID) || pGraph->pVertex[vertexID])
		return (FALSE);
	pGraph->pVertex[vertexID] = 1;
	pGraph->currentVertexCount++;
	return (TRUE);
}

int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	ListNode	add;

	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[fromVertexID] || \
		!pGraph->pVertex[toVertexID])
		return (FALSE);
	add.vertexID = toVertexID;
	add.weight = 1;
	add.pLink = NULL;
	if (pGraph->graphType == UNDIRECTED)
	{
		addLLElement(pGraph->ppAdjEdge[fromVertexID], 0, add);
		add.vertexID = fromVertexID;
		addLLElement(pGraph->ppAdjEdge[toVertexID], 0, add);
	}
	else
		addLLElement(pGraph->ppAdjEdge[fromVertexID], 0, add);
	return (TRUE);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	ListNode	add;

	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[fromVertexID] || \
		!pGraph->pVertex[toVertexID] || weight < 1)
		return (FALSE);
	add.vertexID = toVertexID;
	add.weight = weight;
	add.pLink = NULL;
	if (pGraph->graphType == UNDIRECTED)
	{
		addLLElement(pGraph->ppAdjEdge[fromVertexID], 0, add);
		add.vertexID = fromVertexID;
		addLLElement(pGraph->ppAdjEdge[toVertexID], 0, add);
	}
	else
		addLLElement(pGraph->ppAdjEdge[fromVertexID], 0, add);
	return (TRUE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph || vertexID >= pGraph->maxVertexCount || vertexID < 0)
		return (FALSE);
	return (TRUE);
}

int	get_position(LinkedList* pList, int vertexID)
{
	int	i = 0;
	ListNode	*temp;

	temp = pList->headerNode;
	while (temp && temp->vertexID != vertexID)
	{
		temp = temp->pLink;
		i++;	
	}
	if (temp == NULL)
		return (-1);
	return (i);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int	i = 0;

	if (!checkVertexValid(pGraph, vertexID) || !pGraph->pVertex[vertexID])
		return (FALSE);
	while (i < pGraph->maxVertexCount)
	{
		removeLLElement(pGraph->ppAdjEdge[i], findGraphNodePosition(pGraph->ppAdjEdge[i], vertexID));
		i++;
	}
	clearLinkedList(pGraph->ppAdjEdge[vertexID]);
	pGraph->pVertex[vertexID] = 0;
	pGraph->currentVertexCount--;
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID);
void deleteGraphNode(LinkedList* pList, int delVertexID);
int findGraphNodePosition(LinkedList* pList, int vertexID)
{
	int	i = 0;
	ListNode	*temp;

	temp = pList->headerNode;
	while (temp && temp->vertexID != vertexID)
	{
		temp = temp->pLink;
		i++;	
	}
	if (temp == NULL)
		return (-1);
	return (i);
}

int getEdgeCountLG(LinkedGraph* pGraph);
int getVertexCountLG(LinkedGraph* pGraph);
int getMaxVertexCountLG(LinkedGraph* pGraph);
int getGraphTypeLG(LinkedGraph* pGraph);
void displayLinkedGraph(LinkedGraph* pGraph);