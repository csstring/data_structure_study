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
    temp->headerNode.pLink = NULL;
    temp->headerNode.data = 0;
    return (temp);    
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    ListNode    *temp;

    if (position < 0)
        return (FALSE);
    temp = (ListNode *)malloc(sizeof(ListNode));
    if (!temp)
        exit(12);
    *(temp) = element;
    if (position == 0)
    {
        temp->pLink = pList->headerNode.pLink;
        pList->headerNode.pLink = temp;
    }
    else if (pList->currentElementCount - 1 < position)
        getLLElement(pList, pList->currentElementCount - 1)->pLink = temp;
    else
    {
        temp->pLink = getLLElement(pList, position);
        getLLElement(pList, position - 1)->pLink = temp;
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
    if (position == 0)
    {
        temp = pList->headerNode.pLink;
        pList->headerNode.pLink = getLLElement(pList, 1);
        free(temp);
    }
    else if (pList->currentElementCount - 1 == position)
    {
        temp = getLLElement(pList, position - 1);
        free(temp->pLink);
        temp->pLink = NULL;
    }   
    else
    {
        temp = getLLElement(pList, position);
        getLLElement(pList, position - 1)->pLink = getLLElement(pList, position + 1);
        temp->pLink = NULL;
        free(temp);
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
void deleteLinkedList(LinkedList* pList)
{
    clearLinkedList(pList);
    free(pList);
}

void    list_init(LinkedList    *pList)
{
    ListNode    temp[10];
    int i;

    i = 0;
    while (i < 10)
    {
        temp[i].data = i;
        temp[i].pLink = NULL;
        addLLElement(pList, i, temp[i]);
        i++;
    }
}

void    display_list(LinkedList *plist)
{
    ListNode    *temp;

    temp = plist->headerNode.pLink;
    while (temp)
        {
            printf("data : %d\n", temp->data);
            temp = temp->pLink;
        }
}

void    main_tool(void)
{    
    LinkedList  *list;
    int i;
  
    list = createLinkedList();
    list_init(list);
    display_list(list);
    clearLinkedList(list);
    display_list(list);
    printf("re_init\n");
    list_init(list);
    removeLLElement(list, 3);
    removeLLElement(list, 13);
    removeLLElement(list, 1);
    display_list(list);
    clearLinkedList(list);
    list_init(list);
    list_init(list);
    display_list(list);
    clearLinkedList(list);
    printf("count : %d\n",list->currentElementCount);
    deleteLinkedList(list);
}

int main(void)
{
    main_tool();
    system("leaks a.out");
    return (0);
}