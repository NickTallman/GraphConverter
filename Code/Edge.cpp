#include "Edge.hpp"

Edge::Edge(int start, int end, int weight)
{
	this->start = start;
	this->end = end;
	this->weight = weight;
}

// Compares the two edges by start and end labels
bool operator==(const Edge& e1, const Edge& e2)
{
	if ((e1.start == e2.start) && (e1.end == e2.end))
		return true;
	
	return false;
}