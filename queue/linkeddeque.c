#include "linkeddeque.h"
#include <stdlib.h>
#include <stdio.h>

LinkedDeque* createLinkedDeque()
{
	LinkedDeque	*pDeque;

	pDeque = malloc(sizeof(LinkedDeque));
	if (!pDeque)
		exit (12);
	pDeque->currentElementCount = 0;
	pDeque->pFrontNode = NULL;
	pDeque->pRearNode = NULL;
	return (pDeque);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *temp;

	temp = malloc(sizeof(DequeNode));
	if (!temp)
		exit (12);
	*temp = element;
	if (pDeque->currentElementCount == 0)
	{
		pDeque->pFrontNode = temp;
		pDeque->pRearNode = temp;
	}
	else
	{
		temp->pRLink = pDeque->pFrontNode;
		pDeque->pFrontNode->pLLink = temp;
		pDeque->pFrontNode = temp;
	}
	pDeque->currentElementCount++;
	return (TRUE);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *temp;

	temp = malloc(sizeof(DequeNode));
	if (!temp)
		exit (12);
	*temp = element;
	if (pDeque->currentElementCount == 0)
	{
		pDeque->pFrontNode = temp;
		pDeque->pRearNode = temp;
	}
	else
	{
		temp->pLLink = pDeque->pRearNode;
		pDeque->pRearNode->pRLink = temp;
		pDeque->pRearNode = temp;
	}
	pDeque->currentElementCount++;
	return (TRUE);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	DequeNode *temp;

	if (!pDeque || pDeque->currentElementCount == 0)
		return (NULL);
	else if (pDeque->currentElementCount == 1)
	{
		temp = pDeque->pFrontNode;
		pDeque->pFrontNode = NULL;
		pDeque->pRearNode = NULL;
	}
	else
	{
		temp = pDeque->pFrontNode;
		temp->pRLink->pLLink = NULL;
		pDeque->pFrontNode = temp->pRLink;
		temp->pRLink = NULL;
	}
	pDeque->currentElementCount--;
	return (temp);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
	DequeNode *temp;

	if (!pDeque || pDeque->currentElementCount == 0)
		return (NULL);
	else if (pDeque->currentElementCount == 1)
	{
		temp = pDeque->pRearNode;
		pDeque->pFrontNode = NULL;
		pDeque->pRearNode = NULL;
	}
	else
	{
		temp = pDeque->pRearNode;
		temp->pLLink->pRLink = NULL;
		pDeque->pRearNode = temp->pLLink;
		temp->pLLink = NULL;
	}
	pDeque->currentElementCount--;
	return (temp);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	if (!pDeque || pDeque->currentElementCount == 0)
		return (NULL);
	return (pDeque->pFrontNode);
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
	if (!pDeque || pDeque->currentElementCount == 0)
		return (NULL);
	return (pDeque->pRearNode);
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
	while (!isLinkedDequeEmpty(pDeque))
		free(deleteFrontLD(pDeque));
	free(pDeque);
}

void	clearLinkdeDeque(LinkedDeque* pDeque)
{
	while (!isLinkedDequeEmpty(pDeque))
		free(deleteFrontLD(pDeque));
}

int isLinkedDequeFull(LinkedDeque* pDeque)
{
	return (FALSE);
}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	if (!pDeque)
		return (FALSE);
	if (pDeque->currentElementCount == 0)
		return (TRUE);
	return (FALSE);
}

void	dispalyLD(LinkedDeque* pDeque)
{
	DequeNode	*temp;

	temp = pDeque->pFrontNode;
	while (temp)
	{
		printf("right : %c\n", temp->data);
		temp = temp->pRLink;
	}
	temp = pDeque->pRearNode;
	while (temp)
	{
		printf("left : %c\n", temp->data);
		temp = temp->pLLink;
	}
}

int	main(void)
{
	LinkedDeque	*pDeque;
	DequeNode temp;
	int	i;

	pDeque = createLinkedDeque();
	i = 0;
	while (i < 10)
	{
		temp.data = i + 48;
		insertFrontLD(pDeque, temp);
		i++;
	}
	dispalyLD(pDeque);
	clearLinkdeDeque(pDeque);
	i = 0;
	while (i < 10)
	{
		temp.data = i + 48;
		insertRearLD(pDeque, temp);
		i++;
	}
	dispalyLD(pDeque);
	printf("peek f test : %c\n",peekFrontLD(pDeque)->data);
	printf("peek r test : %c\n",peekRearLD(pDeque)->data);
	clearLinkdeDeque(pDeque);
	dispalyLD(pDeque);
	printf("end\n");
}