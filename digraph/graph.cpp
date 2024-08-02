/**graph.cpp
 *
 * Weighted directed graph container.
 */

#include <string>
#include <stdexcept>

#include "digraph.hpp"

/**
 * Constructors
 */

// Constructor: create empty graph
Graph::Graph()
    : edgeCount(0) {}

// Constructor: creates a graph with vertices 0 to V - 1
Graph::Graph(int V)
    : edgeCount(0)
{
}

// Constructor: creates a graph with an initializer list of vertices
Graph::Graph(std::initializer_list<int> vertices)
    : edgeCount(0)
{
}

// Constructor: deep copy another graph
Graph::Graph(Graph &other)
    : edgeCount(other.edgeCount)
{
}

/**
 * Accessors
 */

// Return number of vertices
size_t Graph::V() const {}
// Return number of edges
size_t Graph::E() const {}

// Check if the graph contains v
bool Graph::contains(int v) const {}

// Serialization of the graph
std::string Graph::toString()
{
}

// Return minimum vertex
int Graph::min() const {}
// Return maximum vertex
int Graph::max() const {}

// Return the indegree of a vertex
int Graph::indegree(int v) const {}

// Return the outdegree of a vertex
int Graph::outdegree(int v) const {}

/**
 * Mutators
 */

/*!
 * @function insertVertex
 * @abstract Insert a vertex with key v
 * @param v Key of the new vertex
 */
void Graph::insertVertex(int v)
{
}

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the vertices do not exist, out_of_range
 *           exception will be thrown.
 * @param v The starting vertex
 * @param w The destination vertex
 * @param weight Weight of the edge, default to 1
 */
void Graph::insertEdge(int v, int w, int weight)
{
}

/*!
 * @function eraseVertex
 * @abstract Remove the vertex with key v. If the vertex does not exist,
 *           out_of_range exception will be thrown.
 * @param v Key of the vertex to remove
 */
void Graph::eraseVertex(int v)
{
}

/*!
 * @function eraseEdge
 * @abstract Remove the edge from v to w if the edge exists. If the
 *           directed edge does not exist, out_of_range exception will
 *           be thrown.
 * @param v The starting vertex
 * @param w The destination vertex
 */
void Graph::eraseEdge(int v, int w)
{
}

// Initializer list equivalents
void Graph::insertVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        insertVertex(v);
}

void Graph::insertEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        insertEdge(edge.first, edge.second);
}
void Graph::eraseVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        eraseVertex(v);
}

void Graph::eraseEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        eraseEdge(edge.first, edge.second);
}

/*!
 * @function adj
 * @abstract Iterates inorder over all the neighbors of v connected by
 *           an outgoing link from v
 * @param v The query vertex
 * @return  The outgoing map in adjacency tree of v
 */
