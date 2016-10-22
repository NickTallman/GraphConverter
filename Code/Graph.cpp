#include "Graph.hpp"

Graph::Graph(int size)
{
	transpose = false;
}

// Builds the graph using an input file
void Graph::buildGraph()
{
	ifstream inputFile {"input.txt"};
	
	string line;
	stringstream ss;
	int index = 0;
	while (getline(inputFile, line))
	{
		ss << line;
		
		// Create a new vertex using the first number in the line
		int num;
		ss >> num;
		Vertex newVertex (num);
		
		// Add connections to the vertex
		while(ss >> num && num != -1)
		{
			newVertex.connectTo(num);
		}
		vertices.push_back(newVertex);
		ss.clear();
		index++;
	}
}

// Displays the graph
void Graph::displayGraph()
{
	for (int i = 0; i < vertices.size(); ++i) // For each vertex
	{
		cout << vertices[i].label;
		// Print each edge
		for (list<Edge>::iterator it = vertices[i].edgeList.begin(); it != vertices[i].edgeList.end(); ++it)
		{
			cout << " -> " << (*it).end;
		}
		// Print DFS timestamps for the vertex
		cout << " : " << vertices[i].startTime << "/" << vertices[i].endTime << endl;
	}
}

// Both functions are used to calculate DFS times for each vertex
void Graph::DFS()
{
	for (int i =0; i < vertices.size(); ++i)
		vertices[i].visited = false;
	
	// If the graph is transposed, run DFS in order of decreasing finishing time
	if (transpose)
	{
		vector<Vertex> orderedVertices = vertices;
		sort(orderedVertices.begin(), orderedVertices.end());
		reverse(orderedVertices.begin(), orderedVertices.end());
		
		int time = 0;
		for (int i = 0; i < vertices.size(); ++i)
		{
			int index = orderedVertices[i].label - 1;
			DFSVisit(vertices[index], time);
		}
	}
	else // Otherwise, run DFS normally
	{
		int time = 0;
		for (int i = 0; i < vertices.size(); ++i)
		{
			DFSVisit(vertices[i], time);
		}
	}
}

void Graph::DFSVisit(Vertex& v, int& time)
{
	if (!v.visited) // Only visit if the vertex is unvisited
	{
		v.visited = true;
		time++;
		v.startTime = time;
		
		// For each vertex edge
		for (list<Edge>::iterator it = v.edgeList.begin(); it != v.edgeList.end(); ++it)
		{
			int index = (*it).end - 1;
			if (!vertices[index].visited) // Only visit vertices not already visited
			{
				DFSVisit(vertices[index], time);
			}
		}
		time++;
		v.endTime = time;
	}
}

// Transposes the graph
void Graph::transposeGraph()
{
	vector<Vertex> newVert(vertices.size());
	
	// Set the tranpose variable to either true or false
	if (!transpose) transpose = true;
	else transpose = false;
	
	// For each vertex in the graph
	for (int i = 0; i < vertices.size(); ++i)
	{
		// Create a new vertex, copy all vertex variables except for edge list
		int startVertex = vertices[i].label;
		newVert[i].label = startVertex;
		newVert[i].startTime = vertices[i].startTime;
		newVert[i].endTime = vertices[i].endTime;
		newVert[i].condition = vertices[i].condition;
		newVert[i].parent = vertices[i].parent;
		newVert[i].children = vertices[i].children;
		
		// Construct the new edge list for the transposed vertex
		for (list<Edge>::iterator it = vertices[i].edgeList.begin(); it != vertices[i].edgeList.end(); ++it)
		{
			int endVertex = (*it).end;
			newVert[endVertex - 1].connectTo(startVertex);
		}
	}
	vertices = newVert;
}

// Displays the acyclic graph
void Graph::displayAcyclic()
{
	// For each vertex in the graph, determine the vertex's condition 
	for (int i = 0; i < vertices.size(); ++i)
	{
		Vertex& v1 = vertices[i];
		
		if (v1.condition == "Deleted")
			continue;
		
		if (v1.startTime != v1.endTime - 1) // If the vertex is a contraction vertex
		{
			v1.condition = "Contraction"; // Set its condition
			for (int j = 0; j < vertices.size(); ++j) // Find its children in the vertex list
			{
				Vertex& v2 = vertices[j];
				
				// Set v2's parent to v1, add v2 to v1's children list
				if ((v2.startTime > v1.startTime) && (v2.endTime < v1.endTime))
				{
					v1.children.push_back(v2.label);
					v2.condition = "Deleted";
					v2.parent = v1.label;
				}
			}
		}
	}
	
	vector<Vertex> acyclicVertices (vertices.size());
	
	// Set the graph back to the original
	this->transposeGraph();
	
	//for each vertex in the graph
	for (int i = 0; i < vertices.size(); ++i)
	{
		// Create a new vertex with an empty edge list, keep label and condition
		Vertex& v = acyclicVertices[i];
		v.label = vertices[i].label;
		v.condition = vertices[i].condition;
		
		// For each vertex connection
		for (list<Edge>::iterator it = vertices[i].edgeList.begin(); it != vertices[i].edgeList.end(); ++it)
		{
			// If the vertex is a contraction vertex
			if (vertices[i].condition == "Contraction")
			{
				// If it connects to a deleted child
				if (find(vertices[i].children.begin(), vertices[i].children.end(), (*it).end) != vertices[i].children.end())
				{
					continue; // Do not add the connection	
				}
				
				// If it connects to a deleted node with a different parent
				Vertex& otherNode = vertices[(*it).end - 1];
				if ((otherNode.condition == "Deleted") && (otherNode.parent != vertices[i].label))
				{
					v.connectTo(otherNode.parent); // Instead connect to the different parent
					continue;
				}	
				// Otherwise
				v.connectTo((*it).end); // Keep connection
			}
			// If the vertex is a deleted node
			if (vertices[i].condition == "Deleted")
			{
				// If it connects to a regular or contraction vertex that's not its parent
				Vertex& otherNode = vertices[(*it).end - 1];
				if (((otherNode.condition == "Contraction") || (otherNode.condition == "")) && (vertices[i].parent != otherNode.label))
				{
					// Add its connections to the parent
					acyclicVertices[vertices[i].parent - 1].connectTo((*it).end);
					continue;
				}
				  
				// If it connects to a deleted node with a different parent
				if ((otherNode.condition == "Deleted") && (otherNode.parent != vertices[i].parent))
				{
					// Parent connects to other node's parent
					acyclicVertices[vertices[i].parent - 1].connectTo(otherNode.parent);
					continue;
				}
				// Otherwise, do not add the connection
			}
			// If the vertex is a regular node
			if (vertices[i].condition == "")
			{
				// If it connects to a deleted vertex
				Vertex& otherNode = vertices[(*it).end - 1];
				if (otherNode.condition == "Deleted")
				{
					// Connect instead to the vertex's parent 
					v.connectTo(otherNode.parent);
					continue;
				}
					
				// Otherwise
				v.connectTo((*it).end);	// Keep connection
			}
		}
		acyclicVertices[i] = v;
	}
	
	// Print the acyclic graph
	for (int i = 0; i < acyclicVertices.size(); ++i)
	{
		// Do not print vertices that have been deleted
		if (acyclicVertices[i].condition == "Deleted")
			continue;
		
		cout << acyclicVertices[i].label;
		for (list<Edge>::iterator it = acyclicVertices[i].edgeList.begin(); it != acyclicVertices[i].edgeList.end(); ++it)
		{
			cout << " -> " << (*it).end;
		}
		cout << endl;
	}
}