#include "arraygraph.h"
#include <stdlib.h>
#include <stdio.h>

ArrayGraph* createArrayGraph(int maxVertexCount)
{
	ArrayGraph	*temp;
	int	i;

	i = 0;
	if (maxVertexCount < 0)
		return (NULL);
	temp = malloc(sizeof(ArrayGraph));
	temp->currentVertexCount = 0;
	temp->maxVertexCount = maxVertexCount;
	temp->graphType = UNDIRECTED;
	temp->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = (int *)malloc(sizeof(int) * maxVertexCount);
	temp->pVertex = malloc(sizeof(int) * maxVertexCount);
	return (temp);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph	*temp;
	int	i;

	i = 0;
	if (maxVertexCount < 1)
		return (NULL);
	temp = malloc(sizeof(ArrayGraph));
	temp->currentVertexCount = 0;
	temp->maxVertexCount = maxVertexCount;
	temp->graphType = DIRECTED;
	temp->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
	while (i < maxVertexCount)
		temp->ppAdjEdge[i++] = (int *)malloc(sizeof(int) * maxVertexCount);
	temp->pVertex = malloc(sizeof(int) * maxVertexCount);
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
	int	i;

	i = 0
	if (!pGraph)
		return ;
	while (i < pGraph->maxVertexCount)
		free(pGraph->ppAdjEdge[i++]);
	free(pGraph->ppAdjEdge);
	free(pGraph->pVertex);
	free(pGraph);
}

int isEmptyAG(ArrayGraph* pGraph)
{
	if (!pGraph)
		return (FALSE);
	if (pGraph->currentVertexCount < pGraph->maxVertexCount)
		return (TRUE);
	return (FALSE);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID) || pGraph->pVertex[vertexID])
		return (FALSE);
	pGraph->pVertex[vertexID] = 1;
	pGraph->currentVertexCount++;
	return (TRUE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[fromVertexID] || \
		!pGraph->pVertex[toVertexID])
		return (FALSE);
	if (pGraph->graphType == UNDIRECTED)
	{
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = 1;
	}
	else
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
	return (TRUE);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[fromVertexID] || \
		!pGraph->pVertex[toVertexID] || weight < 1)
		return (FALSE);
	if (pGraph->graphType == UNDIRECTED)
	{
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
	}
	else
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
	return (TRUE);
}

int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph || vertexID >= pGraph->maxVertexCount || vertexID < 0)
		return (FALSE);
	return (TRUE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	int	i;

	i = 0;
	if (!checkVertexValid(pGraph, vertexID) || !pGraph->pVertex[vertexID])
		return (FALSE);
	while (i < pGraph->maxVertexCount)
	{
		pGraph->ppAdjEdge[vertexID][i] = 0;
		pGraph->ppAdjEdge[i][vertexID] = 0;
	}
	pGraph->pVertex[vertexID] = 0;
	pGraph->currentVertexCount--;
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || \
		!checkVertexValid(pGraph, toVertexID) || \
		!pGraph->pVertex[toVertexID] || \
		!pGraph->pVertex[fromVertexID])
		return (FALSE);
	if (pGraph->graphType == UNDIRECTED)
	{
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
		pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
	}
	else
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
	return (TRUE);
}

void displayArrayGraph(ArrayGraph* pGraph)
{
	int	i;
	int	k;

	i = 0;
	if (!pGraph)
		printf("nonexit graph\n");
	printf("max vertex count : %d\n", pGraph->maxVertexCount);
	printf("current vertex count : %d\n", pGraph->currentVertexCount);
	if (pGraph->graphType == 0)
		printf("graphType : undirected\n");
	else
		printf("graphType : directed\n");
	while (i < pGraph->maxVertexCount)
	{
		k = 0;
		while (k < pGraph->maxVertexCount)
		{
			printf("%d ",pGraph->ppAdjEdge[i][k]);
			k++;
		}
		printf("\n");
		i++;
	}
}