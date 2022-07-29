#include "linkedlist.h"
#include <stdio.h>
#include <math.h>

int addPolyNodeLast(LinkedList* pList, float coef, int degree)
{
    ListNode    temp;

    if (!pList)
        return (FALSE);
    temp.pLink = NULL;
    temp.coef = coef;
    temp.degree = degree;
    return (addLLElement(pList, pList->currentElementCount, temp));
}

void    poly_init(LinkedList *a, LinkedList *b)
{
    addPolyNodeLast(a, 6, 6);
    addPolyNodeLast(a, -4, 5);
    addPolyNodeLast(a, 2, 2);
    addPolyNodeLast(a, 2, -1);
    addPolyNodeLast(a, 2, -4);
    addPolyNodeLast(b, 1, 5);
    addPolyNodeLast(b, -2, 4);
    addPolyNodeLast(b, 3, 2);
    addPolyNodeLast(b, 0, 4);
}

int poly_add(ListNode *a, ListNode *b, LinkedList *plist)
{
    if (!a && !b)
        return (0);
    else if (!a || (b && b->degree > a->degree))
    {
        addPolyNodeLast(plist, b->coef, b->degree);
        poly_add(a, b->pLink, plist);
    }
    else if (!b || (a && a->degree > b->degree))
    {
        addPolyNodeLast(plist, a->coef, a->degree);
        poly_add(a->pLink, b, plist);
    }
    else
    {
        addPolyNodeLast(plist, a->coef + b->coef, a->degree);
        poly_add(a->pLink, b->pLink, plist);
    }
    return (0);
}

static void display_addpoly(LinkedList* plist)
{
    ListNode    *temp;

    temp = plist->headerNode.pLink;
    while (temp)
    {
        if (temp->coef < 0)
            printf("%dx^%d", (int)temp->coef, temp->degree);
        else
            printf("+%dx^%d", (int)temp->coef, temp->degree);
        temp = temp->pLink;
    }
    printf("\n");
}

void    main_tool(void)
{
    LinkedList  *a;
    LinkedList  *b;
    LinkedList  *c;

    a = createLinkedList();
    b = createLinkedList();
    c = createLinkedList();
    poly_init(a, b);
    poly_add(a->headerNode.pLink, b->headerNode.pLink, c);
    display_addpoly(a);
    display_addpoly(b);
    display_addpoly(c);
    deleteLinkedList(a);
    deleteLinkedList(b);
    deleteLinkedList(c);   
}
int main(void)
{
    main_tool();
    system("leaks a.out | grep 'Process'");
}