#ifndef _LINKED_STACK_
#define _LINKED_STACK_

typedef enum PrecedenceType 
{
    lparen, rparen, times, divide, plus, minus, operand 
} Precedence;

typedef struct ExprTokenType 
{ 
    float value;
    Precedence type;
} ExprToken;

typedef struct StackNodeType
{
//	char data;
	ExprToken data;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;	// 현재 원소의 개수
	StackNode* pTopElement;		// Top 노드의 포인터
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);
void ft_makenode(char data, LinkedStack *pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif