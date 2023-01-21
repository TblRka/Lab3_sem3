#include <iostream>
#include "UndirectedGraph.h"

int main()
{
    UndirectedGraph<int, int> undgraph;
    for (int i = 1; i < 7; ++i) 
    {
        undgraph.add_vertex(i);
    }
    undgraph.add_edge(1, 2, 12);
    undgraph.add_edge(2, 3, 1);
    undgraph.add_edge(1, 4, 5);
    undgraph.add_edge(4, 3, 10);
    undgraph.add_edge(6, 5, 2);
    undgraph.add_edge(5, 2, 1);
    undgraph.add_edge(1, 6, 7);

    undgraph.min_path(1, 3);
	
	return 0;
}