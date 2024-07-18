/**digraph.hpp
 *
 * Header for directed graph container.
 */

#ifndef DIGRAPH
#define DIGRAPH

#include <vector>
#include <string>

#include "adjacency-tree/src/adjtree.hpp"

class Digraph
{
private:
    RedBlackTree<int, AdjTree> graphTree;
    size_t edgeCount;

public:
    /**
     * Constructors
     */

    // Constructor: create empty graph
    Digraph();

    // Constructor: creates a graph with vertices 0 to V - 1
    Digraph(int V);

    // Constructor: deep copy another graph
    Digraph(const Digraph &other);

    /**
     * Accessors
     */

    // Return number of vertices
    size_t V();
    // Return number of edges
    size_t E();

    // Serialization of the graph
    std::string toString();

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
    void insertEdge(int v, int w);

    /*!
     * @function insertEdge
     * @abstract Insert an edge between vertex v and w if the vertices
     *           exist. If the directed edge does not exist, the function
     *           will return true.
     * @param v The starting vertex
     * @param w The destination vertex
     */
    void eraseEdge(int v, int w);

    // Get all neighbors such that v has a link to that neighbor
    std::vector<int> adj(int v);
};

#endif /*DIGRAPH*/