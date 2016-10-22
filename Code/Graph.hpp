#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Vertex.hpp"

using namespace std;

class Graph {
public:

	bool transpose; // Keeps track if the graph is transposed or not
    vector<Vertex> vertices; // Vector of vertices in the graph
	
    Graph(int size);
	
    void buildGraph(); // Builds the graph using an input file
    void displayGraph(); // Displays the graph
	
	// Both functions are used to calculate DFS times for each vertex
	void DFS();
	void DFSVisit(Vertex& v, int& time);
	
	void transposeGraph(); // Transposes the graph
	
	void displayAcyclic(); // Displays the acyclic graph
};

#endif /* Graph_hpp */
