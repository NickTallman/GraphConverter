#ifndef Vertex_hpp
#define Vertex_hpp

#include <stdio.h>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

#include "Edge.hpp"
using namespace std;

class Vertex {
public:
    // Vertex variables
    int label;
	
	 // Used in DFS
	bool visited;
	int startTime; // Beginning time stamp
	int endTime; // End time stamp
	
	// Used to display acyclic graph
	int parent; // If the vertex has a parent, this equals it's label, otherwise, -1
	vector<int> children; // If the node has children, this contains all the children's labels
	
	// Condition of the vertex in the acyclic graph
	// "Deleted" if the vertex has a parent
	// "Contraction" if the vertex has children
	// "" if the vertex is a normal vertex
	string condition;
	
    // List of edges of the vertex
    list<Edge> edgeList;
    
	Vertex();
    Vertex(int label);
    
    // Connect this vertex to another vertex
    void connectTo(int end);
};

	// Compares the two vertices by end time stamp
	bool operator<(const Vertex& v1, const Vertex& v2);

#endif /* Vertex_hpp */
