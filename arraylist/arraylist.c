#include "../arraylist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ArrayList   *createArrayList(int maxElementCount)
{
    ArrayList   *temp;

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

int main(void)
{
    ArrayList *list;
    ArrayListNode temp[10];
    ArrayListNode *node;
    int i;

    i = 0;
    list = createArrayList(10);
    while (i < 10)
    {
        temp[i].data = i + 10;
        if (!addALElement(list, i, temp[i]))
            printf("add element fail\n");
        i++;
    }
    displayArrayList(list);
    removeALElement(list, 2);
    displayArrayList(list);
    removeALElement(list, 5);
    displayArrayList(list);
    printf("get alement data: %d\n", (getALElement(list, list->currentElementCount - 1))->data);
    printf("current count : %d max_count : %d\n", list->currentElementCount, list->maxElementCount);
    addALElement(list, 0, temp[9]);
    displayArrayList(list);
    addALElement(list, 9, temp[9]);
    addALElement(list, 9, temp[9]);
    addALElement(list, 9, temp[9]);
    addALElement(list, 9, temp[9]);displayArrayList(list);
    printf("add end\n");
    removeALElement(list, 13);removeALElement(list, 0);removeALElement(list, 0);
    displayArrayList(list);
    clearArrayList(list);
    displayArrayList(list);
    deleteArrayList(list);
    return (0);
}