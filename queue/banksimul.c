#include "linkeddeque.h"
#include <stdio.h>
#include <stdlib.h>

void insertCutomer(int arrivalTime, int processTime, LinkedDeque *pDeque)
{
	DequeNode	temp;

	temp.custom.status = -1;
	temp.custom.arrivalTime = arrivalTime;
	temp.custom.serviceTime = processTime;
	temp.custom.startTime = -1;
	temp.custom.endTime = -1;
	insertRearLD(pDeque, temp);
}

void processArrival(int currentTime, LinkedDeque *pArrivalQueue, LinkedDeque *pWaitQueue)
{
	if (!peekFrontLD(pArrivalQueue))
		return ;
	if (peekFrontLD(pArrivalQueue)->custom.arrivalTime == currentTime)
		insertRearLD(pWaitQueue, *deleteFrontLD(pArrivalQueue));
}

DequeNode* processServiceNodeStart(int currentTime, LinkedDeque *pWaitQueue)
{
	DequeNode *temp;

	if (!peekFrontLD(pWaitQueue))
		return (NULL);
	temp = deleteFrontLD(pWaitQueue);
	temp->custom.status = start;
	temp->custom.startTime = currentTime;
	temp->custom.endTime = temp->custom.startTime + temp->custom.serviceTime;
	return (temp);
}

DequeNode* processServiceNodeEnd(int currentTime, DequeNode *pServiceNod, int *pServiceUserCount, int *pTotalWaitTime)
{
	(*pServiceUserCount)++;
	pServiceNod->custom.status = end;
	(*pTotalWaitTime) += pServiceNod->custom.startTime - pServiceNod->custom.arrivalTime;
	return (pServiceNod);
}

void printSimCustomer(int currentTime, SimCustomer customer)
{
	if (customer.arrivalTime < currentTime)
		printf("not arrival\n");
	else if (customer.startTime == -1 && customer.arrivalTime >= currentTime)
		printf("arrival\n");
	else if (customer.startTime != -1 && customer.endTime == -1)
		printf("start\n");
	else if (customer.endTime != -1)
		printf("receive service");
	else
		printf("end\n");
}

void printWaitQueueStatus(int currentTime, LinkedDeque *pWaitQueue)
{
	if (!peekFrontLD(pWaitQueue))
		printf("no one wait\n");
	else
	{
		printf("arrival time : %d, wait time : %d\n", \
		peekFrontLD(pWaitQueue)->custom.arrivalTime, currentTime - peekFrontLD(pWaitQueue)->custom.arrivalTime);
	}
}
void printReport(LinkedDeque *pWaitQueue, int serviceUserCount, int totalWaitTime)
{
	(void)pWaitQueue;
	printf("serviceUserCount : %d\n", serviceUserCount);
	printf("totalWaitTime : %d\n", totalWaitTime);
}

void	init_tot_coustom(LinkedDeque *coustom_arrival)
{
	insertCutomer(0, 3, coustom_arrival);
	insertCutomer(2, 2, coustom_arrival);
	insertCutomer(4, 1, coustom_arrival);
	insertCutomer(6, 1, coustom_arrival);
	insertCutomer(8, 3, coustom_arrival);
}

void	main_loop(LinkedDeque *coustom_arrival, LinkedDeque *coustom_wait)
{
	int	time;
	DequeNode	*temp;
	int pServiceUserCount = 0;
	int pTotalWaitTime = 0;

	temp = NULL;
	for (time = 0 ; ; time++)
	{
		printWaitQueueStatus(time, coustom_wait);
		processArrival(time, coustom_arrival, coustom_wait);
		if (!temp && !peekFrontLD(coustom_arrival) && !peekFrontLD(coustom_wait))
			break;
		if (temp && temp->custom.endTime == time)
		{
			free(processServiceNodeEnd(time, temp, &pServiceUserCount, &pTotalWaitTime));
			temp = NULL;
		}
		if (!temp)
			temp = processServiceNodeStart(time, coustom_wait);
	}
	printReport(coustom_wait, pServiceUserCount, pTotalWaitTime);
}

int	main(void)
{
	LinkedDeque	*coustom_wait;
	LinkedDeque	*coustom_arrival;

	coustom_wait = createLinkedDeque();
	coustom_arrival = createLinkedDeque();
	init_tot_coustom(coustom_arrival);
	main_loop(coustom_arrival, coustom_wait);
	deleteLinkedDeque(coustom_wait);
	deleteLinkedDeque(coustom_arrival);
	return (0);
}