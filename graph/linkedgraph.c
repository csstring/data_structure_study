#include "linkedgraph.h"
#include <stdio.h>
#include <stdlib.h>
#include "arrayqueue.h"

LinkedGraph* createLinkedGraph(int maxVertexCount)
{
	LinkedGraph	*temp;
	int	i = 0;

	if (maxVertexCount < 1)
		return (NULL);
	temp = malloc(sizeof(LinkedGraph));
	temp->pVertex = malloc(sizeof(int) * maxVertexCount);
	temp->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = createLinkedList();
	temp->graphType = UNDIRECTED;
	temp->maxVertexCount = maxVertexCount;
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
	temp->ppAdjEdge = malloc(sizeof(LinkedList *) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = createLinkedList();
	temp->graphType = DIRECTED;
	temp->maxVertexCount = maxVertexCount;
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
	if (pGraph->currentVertexCount == 0)
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
	pGraph->currentEdgeCount++;
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
	pGraph->currentEdgeCount++;
	return (TRUE);
}

int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	if (!pGraph || vertexID >= pGraph->maxVertexCount || vertexID < 0)
		return (FALSE);
	return (TRUE);
}

int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	int	i = 0;

	if (!checkVertexValid(pGraph, vertexID) || !pGraph->pVertex[vertexID])
		return (FALSE);
	while (i < pGraph->maxVertexCount)
	{
		if (removeLLElement(pGraph->ppAdjEdge[i], findGraphNodePosition(pGraph->ppAdjEdge[i], vertexID)) == TRUE)
			pGraph->currentEdgeCount--;
		i++;
	}
	if (pGraph->graphType == DIRECTED)
		pGraph->currentEdgeCount -= getLinkedListLength(pGraph->ppAdjEdge[vertexID]);
	clearLinkedList(pGraph->ppAdjEdge[vertexID]);
	pGraph->pVertex[vertexID] = 0;
	pGraph->currentVertexCount--;
	return (TRUE);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[toVertexID] || \
		!pGraph->pVertex[fromVertexID])
		return (FALSE);
	if (deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID) == TRUE)
	{
		pGraph->currentEdgeCount--;
		if (pGraph->graphType == UNDIRECTED)
		{
			deleteGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
		}
		return (TRUE);
	}
	return (FALSE);
}

int deleteGraphNode(LinkedList* pList, int delVertexID)
{
	int	pos = findGraphNodePosition(pList, delVertexID);

	return (removeLLElement(pList, pos));
}

int findGraphNodePosition(LinkedList* pList, int vertexID)
{
	int	i = 0;
	ListNode	*temp;

	temp = pList->headerNode.pLink;
	while (temp && temp->vertexID != vertexID)
	{
		temp = temp->pLink;
		i++;	
	}
	if (temp == NULL)
		return (-1);
	return (i);
}

int getEdgeCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (-1);
	return (pGraph->currentEdgeCount);
}

int getVertexCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (-1);
	return (pGraph->currentVertexCount);
}

int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (-1);
	return (pGraph->maxVertexCount);
}

int getGraphTypeLG(LinkedGraph* pGraph)
{
	if (!pGraph)
		return (-1);
	return (pGraph->graphType);
}

void displayLinkedGraph(LinkedGraph* pGraph)
{
	int	i = 0;
	ListNode	*temp;

	if (!pGraph)
		printf("nonexit graph\n");
	printf("max vertex count : %d\n", pGraph->maxVertexCount);
	printf("current vertex count : %d\n", pGraph->currentVertexCount);
	printf("currentEdgeCount : %d\n", pGraph->currentEdgeCount);
	if (pGraph->graphType == UNDIRECTED)
		printf("graphType : undirected\n");
	else
		printf("graphType : directed\n");
	printf("fromvertexID toVertexID\n");
	while (i < pGraph->maxVertexCount)
	{
		temp = pGraph->ppAdjEdge[i]->headerNode.pLink;
		printf("%d ",i);
		while (temp)
		{
			printf("%d ", temp->vertexID);
			temp = temp->pLink;
		}
		printf("\n");
		i++;
	}
}

void	dfs_recursive(int from, LinkedGraph *pGraph)
{
	ListNode*	temp;

	temp = pGraph->ppAdjEdge[from]->headerNode.pLink;
	pGraph->ppAdjEdge[from]->visit = 1;
	printf("%d\n", from);
	while (temp)
	{
		if (!pGraph->ppAdjEdge[temp->vertexID]->visit)
			dfs_recursive(temp->vertexID, pGraph);
		temp = temp->pLink;
	}
}

void	traver_bfs(LinkedGraph *pGraph)
{
	int	i = 0;
	ArrayQueue	*pQueue;
	ArrayQueueNode	temp;
	ListNode	*list_node;
	
	pQueue = createArrayQueue(pGraph->maxVertexCount);
	while (i < pGraph->maxVertexCount)
	{
		if (pGraph->pVertex[i])
			break;
		i++;
	}
	temp.vertexID = i;
	printf("%d\n", temp.vertexID);
	pGraph->ppAdjEdge[temp.vertexID]->visit = 1;
	enqueueAQ(pQueue, temp);
	while (!isArrayQueueEmpty(pQueue))
	{
		list_node = pGraph->ppAdjEdge[peekAQ(pQueue)->vertexID]->headerNode.pLink;
		while (list_node)
		{	
			if (!pGraph->ppAdjEdge[list_node->vertexID]->visit)
			{
				printf("%d\n", list_node->vertexID);
				pGraph->ppAdjEdge[list_node->vertexID]->visit = 1;
				temp.vertexID = list_node->vertexID;
				enqueueAQ(pQueue, temp);
			}
			list_node = list_node->pLink;
		}
		dequeueAQ(pQueue);
	}
	deleteArrayQueue(pQueue);
}

void	traver_dfs(LinkedGraph* pGraph)
{
	int	i = 0;

	if (isEmptyLG(pGraph))
		return ;
	while (i < pGraph->maxVertexCount)
	{
		if (pGraph->pVertex[i])
			break;
		i++;
	}
	dfs_recursive(i, pGraph);
}

#define MAX_COUNT 9

int	main(void)
{
	LinkedGraph	*pGraph;
	int	i = 0;

	pGraph = createLinkedGraph(MAX_COUNT);
	/* pGraph = createLinkedDirectedGraph(MAX_COUNT); */
	while (i < MAX_COUNT)
	{
		if (i != 3)
			addVertexLG(pGraph, i++);
		else
			i++;
	}
	addEdgeLG(pGraph, 0 , 1);
	addEdgeLG(pGraph, 0 , 2);
	addEdgeLG(pGraph, 1 , 3);
	addEdgeLG(pGraph, 1 , 4);
	addEdgeLG(pGraph, 2 , 5);
	addEdgeLG(pGraph, 2 , 6);
	addEdgeLG(pGraph, 3 , 7);
	addEdgeLG(pGraph, 8 , 7);
	addEdgeLG(pGraph, 4 , 5);
	displayLinkedGraph(pGraph);
	printf("========\n");
	traver_bfs(pGraph);
	/* traver_dfs(pGraph); */
	system("leaks $PPID");
	return (0);
}
