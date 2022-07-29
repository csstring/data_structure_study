#include "doublylist.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

DoublyList* createDoublyList()
{
    DoublyList  *temp = NULL;

    temp = (DoublyList *)malloc(sizeof(DoublyList));
    if (!temp)
        exit(12);
    temp->currentElementCount = 0;
    temp->headerNode.data = 0;
    temp->headerNode.pLLink = &temp->headerNode;
    temp->headerNode.pRLink = &temp->headerNode;
    return (temp);
}

void deleteDoublyList(DoublyList* pList)
{
    if (!pList)
        return ;
    clearDoublyList(pList);
    free(pList);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
    DoublyListNode  *temp = NULL;
    DoublyListNode  *right = NULL;
    DoublyListNode  *left = NULL;
    
    if (!pList || position < 0)
        return (FALSE);
    temp = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    if (!temp)
        exit(12);
    *temp = element;
    if (pList->currentElementCount == 0)
    {
        pList->headerNode.pRLink = temp;
        pList->headerNode.pLLink = temp;
        temp->pLLink = &pList->headerNode;
        temp->pRLink = &pList->headerNode;
    }
    else if (position <= pList->currentElementCount - 1)
    {
        right = getDLElement(pList, position);
        left = right->pLLink;
        right->pLLink = temp;
        temp->pRLink = right;
        temp->pLLink = left;
        left->pRLink = temp;
    }
    else
    {
        left = getDLElement(pList, pList->currentElementCount - 1);
        left->pRLink = temp;
        temp->pLLink = left;
        temp->pRLink = &pList->headerNode;
        pList->headerNode.pLLink = temp;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeDLElement(DoublyList* pList, int position)
{
    DoublyListNode  *temp = NULL;
    DoublyListNode  *right = NULL;
    DoublyListNode  *left = NULL;

    if (!pList || position < 0 || position > pList->currentElementCount - 1 \
        || pList->currentElementCount == 0)
        return (FALSE);
    temp = getDLElement(pList, position);
    right = temp->pRLink;
    left = temp->pLLink;
    left->pRLink = right;
    right->pLLink = left;
    free(temp);
    pList->currentElementCount--;
    return (TRUE);
}

void clearDoublyList(DoublyList* pList)
{
    while (removeDLElement(pList, 0));
}

int getDoublyListLength(DoublyList* pList)
{
    if (!pList)
        return (0);
    return (pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
    int i = 0;
    DoublyListNode  *temp = NULL;

    if (position < 0 || position > pList->currentElementCount - 1)
        return (NULL);
    if (position >= (pList->currentElementCount - 1) / 2)//left
    {
        i = pList->currentElementCount - 1;
        temp = pList->headerNode.pLLink;
        while (i != position)
        {
            temp = temp->pLLink;
            i--;
        }
    }
    else //right
    {
        i = 0;
        temp = pList->headerNode.pRLink;
        while(i != position)
        {
            temp = temp->pRLink;
            i++;
        }
    }
    return (temp);
}

void displayDoublyList(DoublyList* pList)
{
    DoublyListNode  *temp = NULL;
    int i;

    i = 0;
    if (!pList)
        return ;
    temp = pList->headerNode.pRLink;
    while (i < pList->currentElementCount)
    {
        printf("direc_right data : %d\n", temp->data);
        temp = temp->pRLink;
        i++;
    }
    i = 0;
    temp = pList->headerNode.pLLink;
    while (i < pList->currentElementCount)
    {
        printf("direc_left data : %d\n", temp->data);
        temp = temp->pLLink;
        i++;
    }
}

void    list_init(DoublyList *plist)
{
    int i;
    DoublyListNode temp[10];

    i = 0;
    while (i < 10)
    {
        temp[i].data = i;
        addDLElement(plist, i, temp[i]);
        i++;
    }
}
void    main_tool(void)
{
    DoublyList  *plist;

    plist = createDoublyList();
    displayDoublyList(plist);
    list_init(plist);
    displayDoublyList(plist);
    removeDLElement(plist, 0);
    removeDLElement(plist, 8);
    displayDoublyList(plist);
    deleteDoublyList(plist);
    plist = NULL;
    displayDoublyList(plist);
}

int main(void)
{
    main_tool();
   system("leaks a.out");
}