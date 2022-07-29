#include "arraystack.h"
#include <stdlib.h>
#include <stdio.h>

ArrayStack* createArrayStack(int maxElementCount)
{
    ArrayStack  *temp;

    if (maxElementCount <= 0)
        return (NULL);
    temp = (ArrayStack *)malloc(sizeof(ArrayStack));
    temp->pElement = (StackArrayNode *)malloc(sizeof(StackArrayNode) * maxElementCount);
    if (!temp)
        exit(12);
    temp->maxElementCount = maxElementCount;
    temp->currentElementCount = 0;
    return (temp);
}

int pushAS(ArrayStack* pStack, StackArrayNode element)
{
    if (!pStack || pStack->currentElementCount == pStack->maxElementCount)
        return (FALSE);
    pStack->pElement[pStack->currentElementCount] = element;
    pStack->currentElementCount++;
    return (TRUE);
}

StackArrayNode* popAS(ArrayStack* pStack)
{
    if (!pStack || pStack->currentElementCount == 0)
        return (NULL);
    pStack->currentElementCount--;
    return (&(pStack->pElement[pStack->currentElementCount + 1]));
}

StackArrayNode* peekAS(ArrayStack* pStack)
{
    if (!pStack || pStack->currentElementCount == 0)
        return (NULL);
    return (&(pStack->pElement[pStack->currentElementCount + 1]));
}

void deleteArrayStack(ArrayStack* pStack)
{
    if (!pStack)
        return ;
    free(pStack->pElement);
    free(pStack);
}

int isArrayStackFull(ArrayStack* pStack)
{
    if (!pStack || pStack->currentElementCount < pStack->maxElementCount)
        return (FALSE);
    return (TRUE);
}

int isArrayStackEmpty(ArrayStack* pStack)
{
    if (!pStack || pStack->currentElementCount > 0)
        return (FALSE);
    return (TRUE);
}