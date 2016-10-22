
#include "Vertex.hpp"
Vertex::Vertex()
{
	label = -1;
	startTime = endTime = -1;
	parent = -1;
	condition = "";
}

Vertex::Vertex(int label)
{
	this->label = label;
	startTime = endTime = -1;
	parent = -1;
	condition = "";
}
    
void Vertex::connectTo(int end)
{
	Edge newEdge(this->label, end);
	
	// Prevents connecting to the same vertex twice
	bool alreadyConnected (find(edgeList.begin(), edgeList.end(), newEdge) != edgeList.end());
	if (alreadyConnected)
		return;
	
	edgeList.push_back(newEdge);
}

// Compares the two vertices by end time stamp
bool operator<(const Vertex& v1, const Vertex& v2)
{
	if (v1.endTime < v2.endTime)
		return true;
	return false;
}