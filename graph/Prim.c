#include "linkedgraph.h"
#include <stdio.h>
#define	MAX_COUNT 6

int	main(void)
{
	LinkedGraph	*origin;
	LinkedGraph *prim;

	origin = init_origin_graph();
	displayLinkedGraph(origin);
	return (0);
}