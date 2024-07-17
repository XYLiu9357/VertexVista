/**digraph.cpp
 *
 * Implementation for directed graph container.
 */

#include <vector>
#include <string>
#include <stdexcept>

#include "linked-list/linked-list.hpp"
#include "digraph.hpp"

// Constructor: create empty graph
Digraph::Digraph() : edgeCount(0) {}

// Constructor: creates a graph with vertices 0 to V - 1
Digraph::Digraph(int V)
    : edgeCount(0)
{
    adjVec.reserve(V);
    for (int i = 0; i < V; i++)
        adjVec.push_back(List());
}

// Constructor: copy graph "other"
Digraph::Digraph(const Digraph &other) : edgeCount(other.edgeCount)
{
    adjVec.resize(other.adjVec.size());
    for (size_t i = 0; i < other.adjVec.size(); ++i)
        adjVec[i] = other.adjVec[i];
}

/**
 * Accessors
 */

// Return number of vertices
size_t Digraph::V() { return adjVec.size(); }

// Return number of edges
size_t Digraph::E() { return edgeCount; }

// Serialization of the graph
std::string Digraph::toString()
{
    std::string graphStr = "";
    for (int i = 0; i < V(); i++)
    {
        graphStr += std::to_string(i) + ": ";
        for (int v : adjVec[i])
            graphStr += std::to_string(v) + " ";
        graphStr += "\n";
    }
    return graphStr;
}

// Create a directed edge from v to w
void Digraph::addEdge(int v, int w)
{
    if (V() < 1)
        throw std::out_of_range("Cannot add edge to empty graph");
    if (v < 0 || w < 0 || v >= V() || w >= V())
        throw std::out_of_range("Vertex index out of bounds [0, V)");

    adjVec[v].insert(w);
    edgeCount++;
}

// Get all neighbors such that v has a link to that neighbor
std::vector<int> Digraph::adj(int v)
{
    if (V() < 1)
        throw std::out_of_range("Cannot add edge to empty graph");
    if (v < 0 || v >= V())
        throw std::out_of_range("Vertex index out of bounds [0, V)");

    std::vector<int> neighbors;
    neighbors.reserve(adjVec[v].size());
    for (int vNum : adjVec[v])
        neighbors.push_back(vNum);

    return neighbors;
}