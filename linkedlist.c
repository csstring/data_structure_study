#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

LinkedList* createLinkedList()
{
    LinkedList  *temp;

    temp = (LinkedList *)malloc(sizeof(LinkedList));
    if (!temp)
        exit(12);
    temp->currentElementCount = 0;
    temp->headerNode.pLink = (ListNode *)malloc(sizeof(ListNode));
    temp->headerNode.data = 0;
    return (temp);    
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{//지들 들어갈 자리 malloc하고 들어가는게 맞는듯
    ListNode    *temp;

    temp = NULL;
    if (position < 0)
        return (FALSE);
    if (pList->currentElementCount == 0)
        *(pList->headerNode.pLink) = element;
    else if (pList->currentElementCount - 1 < position)
    {
        temp = getLLElement(pList, pList->currentElementCount - 1);
        *(temp->pLink) = element;
    }
    else if (position == 0)
    {
        element.pLink = pList->headerNode.pLink;
        *(pList->headerNode.pLink) = element;
    }
    else
    {
        element.pLink = getLLElement(pList, position);
        temp = getLLElement(pList, position - 1);
        *(temp->pLink) = element;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeLLElement(LinkedList* pList, int position)
{
    ListNode    *temp;

    temp = NULL;
    if (position < 0 || pList->currentElementCount - 1 < position)
        return (FALSE);
    if (pList->currentElementCount == 1)//????프리 하면 다음 노드 못붙이고 NULL처리도 못하고
    {

        free(pList->headerNode.pLink);
    }
    else if (pList->currentElementCount - 1 == position)
        getLLElement(pList, position - 1)->pLink = NULL;
    else if (position == 0)
    {
        temp = getLLElement(pList, 0);
        pList->headerNode.pLink = getLLElement(pList, 1);
        free(temp->pLink);
    }
    else
    {
        temp = getLLElement(pList, position);
        getLLElement(pList, position - 1)->pLink = getLLElement(pList, position + 1);
        free(temp->pLink);
    }
    pList->currentElementCount--;
    return (TRUE);
}

ListNode* getLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode    *temp;

    i = 0;
    temp = pList->headerNode.pLink;
    if (position < 0)
        return (NULL);
    while (temp && i != position)
    {
        temp = temp->pLink;
        i++;
    }
    return (temp);
}

void clearLinkedList(LinkedList* pList)
{
    while (removeLLElement(pList, 0));
}

//int getLinkedListLength(LinkedList* pList)
/*oid deleteLinkedList(LinkedList* pList)
{

}*/
void    list_init(LinkedList    *pList)
{
    ListNode    temp[10];
    int i;

    i = 0;
    while (i < 10)
    {
        temp[i].data = i;
        temp[i].pLink = (ListNode *)malloc(sizeof(ListNode));
        addLLElement(pList, i, temp[i]);
        i++;
        write(1,"1",1);
        printf("init : %d\n",i);
    }
}
int main(void)
{
    LinkedList  *list;
    int i;

    list = createLinkedList();
    list_init(list);
    while(i < 9)
        printf("%d\n", getLLElement(list, i++)->data);
    return (0);
}