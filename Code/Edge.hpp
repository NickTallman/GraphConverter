#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>

class Edge {
public:
    // start vertex's label
    int start;
    // end vertex's label
    int end;
    // the weight of this edge
    int weight;
    
    Edge(int start, int end, int weight = 0);

};

	// Compares the two edges by start and end labels
	bool operator==(const Edge& e1, const Edge& e2);

#endif /* Edge_hpp */
