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
Digraph::Digraph() {}

// Constructor: creates a graph with vertices 0 to V - 1
Digraph::Digraph(int V) {}

// Constructor: deep copy another graph
Digraph::Digraph(const Digraph &other) {}

/**
 * Accessors
 */

// Return number of vertices
size_t Digraph::V() {}
// Return number of edges
size_t Digraph::E() {}

// Serialization of the graph
std::string Digraph::toString() {}

/**
 * Mutators
 */

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the directed edge already exists, the function
 *           will return true.
 * @param v The starting vertex
 * @param w The destination vertex
 */
void Digraph::insertEdge(int v, int w) {}

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the directed edge does not exist, the function
 *           will return true.
 * @param v The starting vertex
 * @param w The destination vertex
 */
void Digraph::eraseEdge(int v, int w) {}

// Get all neighbors such that v has a link to that neighbor
std::vector<int> Digraph::adj(int v) {}