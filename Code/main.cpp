#include "Graph.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
	Graph gr (0);
	
	gr.buildGraph();
	
	cout << "Run DFS on Original Graph:" << endl;
	gr.DFS();
	gr.displayGraph();
	
	cout << "\nRun DFS on Transpose Graph" << endl;
	gr.transposeGraph();
	gr.DFS();
	gr.displayGraph();
	
	cout << "\nDisplay Acyclic Graph" << endl;
	gr.displayAcyclic();
	
    return 0;
}
