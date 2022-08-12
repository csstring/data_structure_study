#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_

typedef enum SimStatusType {arrival, start, end} SimStatus;

typedef struct SimCustomerType
{
	SimStatus status;
	int arrivalTime;
	int serviceTime;
	int startTime;
	int endTime;
} SimCustomer;

typedef struct DequeNodeType
{
	char data;
	SimCustomer custom;
	struct DequeNodeType* pRLink;
	struct DequeNodeType* pLLink;
} DequeNode;

typedef struct LinkedDequeType
{
	int currentElementCount;
	DequeNode* pFrontNode;
	DequeNode* pRearNode;		
} LinkedDeque;

LinkedDeque* createLinkedDeque();
int insertFrontLD(LinkedDeque* pDeque, DequeNode element);
int insertRearLD(LinkedDeque* pDeque, DequeNode element);
DequeNode* deleteFrontLD(LinkedDeque* pDeque);
DequeNode* deleteRearLD(LinkedDeque* pDeque);
DequeNode* peekFrontLD(LinkedDeque* pDeque);
DequeNode* peekRearLD(LinkedDeque* pDeque);
void deleteLinkedDeque(LinkedDeque* pDeque);
int isLinkedDequeFull(LinkedDeque* pDeque);
int isLinkedDequeEmpty(LinkedDeque* pDeque);
void	dispalyLD(LinkedDeque* pDeque);
void	clearLinkdeDeque(LinkedDeque* pDeque);

void insertCutomer(int arrivalTime, int processTime, LinkedDeque *pDeque);
void processArrival(int currentTime, LinkedDeque *pArrivalQueue, LinkedDeque *pWaitQueue); 
DequeNode* processServiceNodeStart(int currentTime, LinkedDeque *pWaitQueue); 
DequeNode* processServiceNodeEnd(int currentTime, DequeNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime); 
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedDeque *pWaitQueue); 
void printReport(LinkedDeque *pWaitQueue, int serviceUserCount, int totalWaitTime);
#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif
