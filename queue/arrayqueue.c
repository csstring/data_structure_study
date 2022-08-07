#include "arrayqueue.h"
#include <stdlib.h>
#include <stdio.h>

ArrayQueue* createArrayQueue(int maxElementCount)
{
	ArrayQueue	*temp;

	if (maxElementCount <= 0)
		return (NULL);
	temp = (ArrayQueue *)malloc(sizeof(ArrayQueue *));
	if (!temp)
		exit(12);
	temp->pElement = malloc(sizeof(ArrayQueueNode) * maxElementCount);
	if (!temp->pElement)
		exit (12);
	temp->maxElementCount = maxElementCount;
	temp->currentElementCount = 0;
	temp->front = 0;
	temp->rear = 0;
	return (temp);
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
	if (!pQueue || pQueue->currentElementCount == pQueue->maxElementCount)
		return (FALSE);
	pQueue->pElement[pQueue->rear] = element;
	pQueue->currentElementCount++;
	pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount;
	return (TRUE);
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{	
	ArrayQueueNode	*front_node;

	if (!pQueue || pQueue->currentElementCount == 0)
		return (NULL);
	front_node = &(pQueue->pElement[pQueue->front]);
	pQueue->currentElementCount--;
	pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
	return (front_node);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
	if (!pQueue || pQueue->currentElementCount == 0)
		return (NULL);
	else
		return (&(pQueue->pElement[pQueue->front]));
}

void deleteArrayQueue(ArrayQueue* pQueue)
{
	if (!pQueue)
		return ;
	while (!isArrayQueueEmpty(pQueue))
		dequeueAQ(pQueue);
	free(pQueue->pElement);
	free(pQueue);
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	if (pQueue->currentElementCount == pQueue->maxElementCount)
		return (TRUE);
	return (FALSE);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
	if (!pQueue)
		return (FALSE);
	if (pQueue->currentElementCount == 0)
		return(TRUE);
	return (FALSE);
}

void	displayArrayQueue(ArrayQueue *pQueue)
{
	int	i = 0;

	if (!pQueue)
		return ;
	while (i < pQueue->currentElementCount)
	{
		printf("%c\n", pQueue->pElement[(pQueue->front + i) % pQueue->maxElementCount].data);
		i++;
	}
}

int	main(void)
{
	ArrayQueue *temp;
	int	i = 0;
	ArrayQueueNode element;

	temp = createArrayQueue(10);
	while (i < 15)
	{
		element.data = i + 48;
		enqueueAQ(temp, element);
		i++;
	}
	displayArrayQueue(temp);
	printf("one\n");
	while (!isArrayQueueEmpty(temp))
		dequeueAQ(temp);
	displayArrayQueue(temp);
	printf("two\n");
	i = 0;
	while (i < 5)
	{
		element.data = i + 48;
		enqueueAQ(temp, element);
		i++;
	}
	displayArrayQueue(temp);
	printf("three\n");
	i = 0;
	while (i < 20)
	{
		element.data = i + 48;
		enqueueAQ(temp, element);
		i++;
	}
	printf("four\n");
	displayArrayQueue(temp);
	return (0);
}