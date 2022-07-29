#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

typedef struct StackNodeType
{
	char data;
} StackArrayNode;

typedef struct LinkedStackType
{
	int maxElementCount;			// 최대 원소 개수
	int currentElementCount;		// 현재 원소의 개수
	StackArrayNode* pElement;		// Top 노드의 포인터
} ArrayStack;

ArrayStack* createArrayStack(int maxElementCount);
int pushAS(ArrayStack* pStack, StackArrayNode element);
StackArrayNode* popAS(ArrayStack* pStack);
StackArrayNode* peekAS(ArrayStack* pStack);
void deleteArrayStack(ArrayStack* pStack);
int isArrayStackFull(ArrayStack* pStack);
int isArrayStackEmpty(ArrayStack* pStack);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif