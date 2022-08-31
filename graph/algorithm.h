#ifndef ALGORITHM_H
# define ALGORITHM_H
#include "linkedgraph.h"
#define	MAX_COUNT 6

int	dfs_recursive_edge(int fromVertexID, int toVertexID, LinkedGraph *pGraph, int start_ID);
void	node_visit_clear(LinkedGraph *pGraph);
int	cycle_check(LinkedGraph *kruskal);
LinkedGraph	*init_origin_graph(enum e_arraygraph_type type);
void	node_visit_clear(LinkedGraph *pGraph);
#endif