# Cities-Shortest-Path-Finder

## Problem Statement

In a network of highways connecting N cities, determining all shortest paths in a weighted graph is crucial for optimizing transportation routes. This project addresses this need by providing a tool to analyze the network graph and compute shortest paths efficiently.

## Input

The input data is provided in the form of an Excel sheet named "CitiesG.xlsx", containing the adjacency matrix representation of the weighted graph. Each cell in the matrix represents the distance between pairs of cities.

## Output

The program generates an output file containing the following information:
- Number of Vertices in the graph.
- Number of Edges in the graph.
- Adjacency Matrix representing the connections between cities.
- List of Graph Edges.
- Shortest Paths from a specified city to all other cities in the graph.

## Implementation

The program is implemented in C++, utilizing the following components:
- **Edge class**: Defines an edge in the graph with attributes such as source, destination, and weight.
- **Graph class**: Handles operations related to the graph, including reading input from a file, extracting edges, and performing algorithms like Depth First Search (DFS) and Dijkstra's Algorithm for finding shortest paths.
- **Main function**: Orchestrates the execution flow, reads input data, performs graph analysis, and writes results to an output file.

## Usage

To use the program:
1. Ensure the input Excel sheet "CitiesG.xlsx" is in the correct format.
2. Compile and run the program, providing the necessary input file.
3. Retrieve the output file "Output.txt" containing the analysis results.

## About

- **Author**: Saif Ahmed Elsayed Abd Elfattah

---

Feel free to contribute, suggest improvements, or report issues!
