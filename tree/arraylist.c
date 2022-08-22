#include "arraylist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ArrayList   *createArrayList(int maxElementCount)
{
    ArrayList   *temp;

    if (maxElementCount < 1)
        return (NULL);
    temp = (ArrayList *)malloc(sizeof(ArrayList) * (1));
    if (!temp)
        exit(12);
    temp->maxElementCount = maxElementCount;
    temp->currentElementCount = 0;
    temp->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * (maxElementCount));
    if (!temp->pElement)
        exit(12);
    return (temp);
}

void    deleteArrayList(ArrayList *pList)
{
    if (!pList)
        return ;
    free(pList->pElement);
    free(pList);
}

int isArrayListFull(ArrayList *pList)
{
    if (pList == NULL)
        return (FALSE);
    else if (pList->maxElementCount == pList->currentElementCount)
        return (TRUE);
    return (FALSE);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
    if (isArrayListFull(pList) || position < 0)
        return (FALSE);
    else if (pList->maxElementCount - 1 < position)
        return (FALSE);
    else if (pList->currentElementCount - 1 >= position)
    {
        memmove(&(pList->pElement[position + 1]), &(pList->pElement[position]), \
            sizeof(ArrayListNode) * (pList->currentElementCount - position));
        pList->pElement[position] = element;
    }
    else
    {
        pList->pElement[pList->currentElementCount] = element;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeALElement(ArrayList* pList, int position)
{
    if (position < 0 || pList->currentElementCount - 1 < position)
        return (FALSE);
    else if (pList->maxElementCount - 1 < position)
        return (FALSE);
    else if (pList->currentElementCount - 1 == position)
        pList->pElement[pList->currentElementCount].data = 0;
    else
    {
        memmove(&(pList->pElement[position]), &(pList->pElement[position + 1]), \
            sizeof(ArrayListNode) * (pList->currentElementCount - 1 - position));
        pList->pElement[pList->currentElementCount - 1].data = 0;
    }
    pList->currentElementCount--;
    return (TRUE);
}

ArrayListNode* getALElement(ArrayList* pList, int position)
{
    if (position < 0)
        return (NULL);
    else if (pList->currentElementCount - 1 < position)
        return (NULL);
    else
        return (&(pList->pElement[position]));
}

void displayArrayList(ArrayList* pList)
{
    int i;

    i = 0;
    while (i <= pList->currentElementCount - 1)
    {
        printf("position : %d data : %d\n", i, pList->pElement[i].data);
        i++;
    }
}

void clearArrayList(ArrayList* pList)
{
    int i;

    i = 0;
    while (i <= pList->maxElementCount - 1)
        pList->pElement[i++].data = 0;
    pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList)
{
    if (!pList)
        return (0);
    else
        return (pList->currentElementCount);
}