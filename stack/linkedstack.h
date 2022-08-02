#ifndef _LINKED_STACK_
#define _LINKED_STACK_

#include "mapdef.h"

typedef struct StackNodeType
{
//	char data;
	MapPosition data;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	// 현재 원소의 개수
	int enter[2];
	int	out[2];
	StackNode* pTopElement;		// Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
void ft_makenode(char data, LinkedStack *pStack);

int direc_check(int x, int y, int direc, int map[HEIGHT][WIDTH]);
int pushLSMapPosition(LinkedStack* pStack, int x, int y, int direction);
void    get_enter(LinkedStack *pStack, int map[HEIGHT][WIDTH]);
void    get_out(LinkedStack *pStack, int map[HEIGHT][WIDTH]);
void    get_map(int map[HEIGHT][WIDTH]);
void    ft_print_map(int map[HEIGHT][WIDTH], int x, int y);
int find_direction(int x, int y, int map[HEIGHT][WIDTH]);
void    wall_marking(LinkedStack *pStack, int map[HEIGHT][WIDTH]);
void    visit_marking(LinkedStack *pStack, int map[HEIGHT][WIDTH], int type);
int    find_out(LinkedStack *pStack, int map[HEIGHT][WIDTH]);
#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif