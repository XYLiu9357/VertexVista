/**digraph.cpp
 *
 * Implementation for directed graph container.
 */

#include <string>
#include <stdexcept>

#include "digraph.hpp"

/**
 * Constructors
 */

// Constructor: create empty graph
Digraph::Digraph()
    : edgeCount(0) {}

// Constructor: creates a graph with vertices 0 to V - 1
Digraph::Digraph(int V)
    : edgeCount(0)
{
}

// Constructor: creates a graph with an initializer list of vertices
Digraph::Digraph(std::initializer_list<int> vertices)
    : edgeCount(0)
{
}

// Constructor: deep copy another graph
Digraph::Digraph(Digraph &other)
    : edgeCount(other.edgeCount)
{
}

/**
 * Accessors
 */

// Return number of vertices
size_t Digraph::V() const {}
// Return number of edges
size_t Digraph::E() const {}

// Check if the graph contains v
bool Digraph::contains(int v) const {}

// Serialization of the graph
std::string Digraph::toString()
{
}

// Return minimum vertex
int Digraph::min() const {}
// Return maximum vertex
int Digraph::max() const {}

// Return the indegree of a vertex
int Digraph::indegree(int v) const {}

// Return the outdegree of a vertex
int Digraph::outdegree(int v) const {}

/**
 * Mutators
 */

/*!
 * @function insertVertex
 * @abstract Insert a vertex with key v
 * @param v Key of the new vertex
 */
void Digraph::insertVertex(int v)
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
void Digraph::insertEdge(int v, int w, int weight)
{
}

/*!
 * @function eraseVertex
 * @abstract Remove the vertex with key v. If the vertex does not exist,
 *           out_of_range exception will be thrown.
 * @param v Key of the vertex to remove
 */
void Digraph::eraseVertex(int v)
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
void Digraph::eraseEdge(int v, int w)
{
}

// Initializer list equivalents
void Digraph::insertVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        insertVertex(v);
}

void Digraph::insertEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        insertEdge(edge.first, edge.second);
}
void Digraph::eraseVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        eraseVertex(v);
}

void Digraph::eraseEdge(std::initializer_list<std::pair<int, int>> edges)
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
