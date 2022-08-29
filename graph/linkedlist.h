#ifndef _LINKEDLIST_
#define _LINKEDLIST_
#include <stdlib.h>

typedef struct ListNodeType
{
	int 	weight;
	int		vertexID;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType
{
	int		visit;
	int 	currentElementCount;	// 현재 저장된 원소의 개수
	ListNode headerNode;		// 헤더 노드
} LinkedList;

LinkedList* createLinkedList();
int addLLElement(LinkedList* pList, int position, ListNode element);
int removeLLElement(LinkedList* pList, int position);
ListNode* getLLElement(LinkedList* pList, int position);

void clearLinkedList(LinkedList* pList);
int getLinkedListLength(LinkedList* pList);
void deleteLinkedList(LinkedList* pList);
void display_list(LinkedList *plist);

//addpolynode
int addPolyNodeLast(LinkedList* pList, float coef, int degree);
void    poly_init(LinkedList *a, LinkedList *b);
int poly_add(ListNode *a, ListNode *b, LinkedList *plist);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif