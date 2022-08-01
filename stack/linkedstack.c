#include "linkedstack.h"
#include <stdlib.h>
#include <stdio.h>

LinkedStack* createLinkedStack(void)
{
    LinkedStack *temp;

    temp = (LinkedStack *)malloc(sizeof(LinkedStack));
    if (!temp)
        exit(12);
    temp->currentElementCount = 0;
    temp->pTopElement = NULL;
    return (temp);
}

int pushLS(LinkedStack* pStack, StackNode element)
{
    StackNode   *temp;

    if (!pStack)
        return (FALSE);
    temp = (StackNode *)malloc(sizeof(StackNode));
    *temp = element;
    temp->pLink = pStack->pTopElement;
    pStack->pTopElement = temp;
    pStack->currentElementCount++;
    return (TRUE);    
}

StackNode* popLS(LinkedStack* pStack)
{
    StackNode   *temp;

    if (!pStack || !pStack->pTopElement)
        return (NULL);
    temp = pStack->pTopElement;
    pStack->pTopElement = temp->pLink;
    pStack->currentElementCount--;
    return (temp);
}

StackNode* peekLS(LinkedStack* pStack)
{
    if (!pStack)
        return (NULL);
    else
        return (pStack->pTopElement);
}

void deleteLinkedStack(LinkedStack* pStack)
{
    while (pStack->currentElementCount != 0)
        free(popLS(pStack));
    free(pStack);
}

int isLinkedStackEmpty(LinkedStack* pStack)
{
    if (!pStack)
        return (FALSE);
    if (pStack->currentElementCount == 0)
        return (TRUE);
    else
        return (FALSE);
}