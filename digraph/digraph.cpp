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
    for (int i = 0; i < V; i++)
        graphTree[i] = AdjTree();
}

// Constructor: creates a graph with an intializer list of vertices
Digraph::Digraph(std::initializer_list<int> vertices)
    : edgeCount(0)
{
    for (int v : vertices)
        graphTree[v] = AdjTree();
}

// Constructor: deep copy another graph
Digraph::Digraph(Digraph &other)
    : edgeCount(other.edgeCount)
{
    // Reconstruct vertices
    for (std::pair<int, AdjTree> otherGraphTreePair : other.graphTree)
        insertVertex(otherGraphTreePair.first);

    // Iterate through all adjacency trees and reconstruct edges
    for (std::pair<int, AdjTree> otherGraphTreePair : other.graphTree)
        for (std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *> otherAdjTreePair : otherGraphTreePair.second)
            AdjTree::insertGraphTreeEdge(graphTree, otherGraphTreePair.first, otherAdjTreePair.first);
}

/**
 * Accessors
 */

// Return number of vertices
size_t Digraph::V() { return graphTree.size(); }
// Return number of edges
size_t Digraph::E() { return edgeCount; }

// Serialization of the graph
std::string Digraph::toString()
{
    if (graphTree.empty())
        throw std::out_of_range("Invalid serialization of empty container");
    std::string serializedStr = "";
    for (std::pair<int, AdjTree> pair : graphTree)
        serializedStr += std::to_string(pair.first) + ": " + pair.second.toString() + "\n";
    return serializedStr;
}

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
    if (graphTree.contains(v))
        return;

    graphTree[v] = AdjTree();
}

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the vertices do not exist, out_of_range
 *           exception will be thrown.
 * @param v The starting vertex
 * @param w The destination vertex
 */
void Digraph::insertEdge(int v, int w)
{
    if (!graphTree.contains(v) || !graphTree.contains(w))
        throw std::out_of_range("Attempted edge insertion between nonexistent vertices");
    if (graphTree[v].contains(w)) // Edge already exists
        return;

    AdjTree::insertGraphTreeEdge(graphTree, v, w);
    edgeCount++;
}

/*!
 * @function eraseVertex
 * @abstract Remove the vertex with key v. If the vertex does not exist,
 *           out_of_range exception will be thrown.
 * @param v Key of the vertex to remove
 */
void Digraph::eraseVertex(int v)
{
    if (!graphTree.contains(v))
        throw std::out_of_range("Attempted vertex deletion on nonexistent vertex");

    size_t edgesRemoved = AdjTree::eraseGraphTreeVertex(graphTree, v);
    edgeCount -= edgesRemoved;
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
    if (!graphTree.contains(v) || !graphTree.contains(w))
        throw std::out_of_range("Attempted edge deletion between nonexistent vertices");
    if (!graphTree.find(v)->second.contains(w))
        throw std::out_of_range("Attempted edge deletion on nonexistent edge");

    AdjTree::eraseGraphTreeEdge(graphTree, v, w);
    edgeCount--;
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
