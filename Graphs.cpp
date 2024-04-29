// Name: Saif Ahmed Elsayed Abd Elfattah
// ID: 900225535

// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

#include <fstream>		// For reading file from disk
#include <iostream>
#include <string>		// For file name
#include <iomanip>
#include "Edge.h"		// Deinition of an Edge
#include "Graphs.h"
#include <vector>
#include <climits>
#include <limits>

using namespace std;

// Constructor
Graphs::Graphs()
{
	E = V = order = 0;
}

// Destructor
Graphs::~Graphs()
{
}


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Graphs::Vname(const int s) const
{
	return char(s+65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname)
{   
    // Local data ...
    ifstream source(fname); // Use the constructor directly

    if (!source.is_open())
    {
        cerr << "Error: Unable to open file " << fname << endl;
        exit(EXIT_FAILURE);
    }

    // Count the number of lines in the file
    V = 0;
    string line;
    while (getline(source, line))
    {
        V++;
    }

    // Reopen the file to read from the beginning
    source.clear();
    source.seekg(0, ios::beg);

    // Input weights from the file into a 2-D
    // Adjacency Matrix of V rows and V columns
    for (int r = 0; r < V; r++)
    {
        for (int c = 0; c < V; c++)
        {
            source >> AdjMatrix[r][c];
        }
    }

    source.close();
    getEdges();
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[]. 
void Graphs::getEdges()			
{
	int r , c;
	int i = 0;
	weightType weight;

	// Only examine weights above the diagonal 
	for (r = 0; r <= V-2; r++)
		for (c = r+1; c <= V-1; c++)
		{
			weight = AdjMatrix[r][c];
			if (weight > 0)
			{
				// save (r,c,weight) in edges[i]
				edges[i].u = r;
				edges[i].v = c;
				edges[i].w = weight;
				i++;
			}
		}

	E = i;		// Number of non-zero edges
	
}

// Get number of vertices (V)	
int Graphs::No_of_Verices() const 				
{
	return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const 					
{
	return E;
}

// Output an edge (e): Vertex names and weight
void Graphs::printEdge(std::ofstream& outputFile, Edge e) const
{
    outputFile << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}
void Graphs::dispEdges(std::ofstream& outputFile) const
{
    for (int i = 0; i < E; i++) 
        printEdge(outputFile, edges[i]); // Assuming printEdge is defined
}

int Graphs::leastDis(int d[], bool group[])
{
    // Initialize minimum value and index
    int min_val = std::numeric_limits<int>::max(); // use std::numeric_limits<int>::max() for maximum integer value
    int min = -1; // Initialize min to an invalid index

    // Find the vertex with the minimum distance
    for (int v = 0; v < V; v++)
    {
        if (!group[v] && d[v] < min_val)
        {
            min_val = d[v];
            min = v;
        }
    }

    return min;
}

// Display Graph Edges
void Graphs::dispGraph(std::ofstream& outputFile) const
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            outputFile << setw(3) << AdjMatrix[i][j] << " ";
        }
        outputFile << endl;
    }
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
void Graphs::shPath(int s, std::ofstream& outputFile)
{
    // Initialize arrays for distances (d), inclusion status (Tset), and previous vertices (via)
    int d[V];
    bool Tset[V];
    int via[V];

    // Initialize arrays with default values
    for (int i = 0; i < V; i++)
    {
        d[i] = std::numeric_limits<int>::max();
        Tset[i] = false;
        via[i] = -1;
    }

    // Set the distance to the source vertex to 0
    d[s] = 0;

    // Iterate to find the shortest paths
    for (int count = 0; count < V - 1; count++)
    {
        // Find the vertex with the minimum distance
        int m = leastDis(d, Tset);
        Tset[m] = true;

        // Update distances for adjacent vertices if a shorter path is found
        for (int i = 0; i < V; i++)
        {
            if (!Tset[i] && AdjMatrix[m][i] && d[m] != std::numeric_limits<int>::max() && d[m] + AdjMatrix[m][i] < d[i])
            {
                d[i] = d[m] + AdjMatrix[m][i];
                via[i] = m;
            }
        }
    }

    // Output the shortest paths to the specified output file
    outputFile << "Shortest Paths from " << Vname(s) << " to each vertex:" << std::endl;
    outputFile << "Vertex\t\tDistance\tPath" << std::endl;

    for (int i = 0; i < V; i++)
    {
        outputFile << Vname(i) << "\t\t" << d[i] << "\t\t";

        if (d[i] != std::numeric_limits<int>::max())
        {
            // Reconstruct the path using the via array
            std::vector<int> path;
            int current = i;

            while (current != -1)
            {
                path.push_back(current);
                current = via[current];
            }

            // Print the reconstructed path in reverse order
            for (int j = path.size() - 1; j >= 0; j--)
            {
                outputFile << Vname(path[j]);
                if (j > 0)
                    outputFile << " -> ";
            }
        }

        outputFile << std::endl;
    }
}

// Print path (vertex names) from source (s) to destination (i)
void Graphs::printPath(int s, int i) const
{
	cout << setw(3) << distance[i] << " ";
	cout << Vname(s);
	while (via[i] != -1)
	{
		cout << " " << Vname(via[i]);
		i = via[i];
	}
	cout << endl;
}

// Node Visit Function
void Graphs::visit(int k)
{ 
	val[order++] = k;
}

// Depth First Search Traversal
void Graphs::DFS()
{
	// Initialize visit order array
	order = 0;
	
	// Initialize processed array to false
	for (int i = 0; i < V; i++)
		processed[i] = false;
	
	// Traverse the graph using DFS
	for (int i = 0; i < V; i++)
	{
		if (!processed[i])
		{
			visit(i);
			processed[i] = true;
		}
	}
}

int main()
{
    Graphs graph;
    string filename = "CitiesG.txt";

    // Read the graph from the file
    graph.getGraph(filename);

    // Open the output file
    ofstream outputFile("Output.txt");
    outputFile << "Name: Saif Ahmed Elsayed Abd Elfattah" << endl;
    outputFile << "ID: 900225535 " << endl;
    // Display the number of vertices and edges in the output file
    outputFile << "Number of Vertices = " << graph.No_of_Verices() << endl;
    outputFile << "Number of Edges = " << graph.No_of_Edges() << endl << endl;

    // Display the adjacency matrix in the output file
    outputFile << "Adjacency Matrix\n";
    graph.dispGraph(outputFile); 
    outputFile << endl;

    // Display the graph edges in the output file
    outputFile << "Graph Edges\n";
    graph.dispEdges(outputFile);  // Pass the output file stream to the function
    outputFile << endl;

    // Perform DFS traversal 
    graph.DFS();

    // Perform Dijkstra's Algorithm for shortest paths
    int sourceNode = 0;
    graph.shPath(sourceNode, outputFile);

    // Close the output file
    outputFile.close();

    return 0;
}