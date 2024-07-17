/**digraph.hpp
 *
 * Header for directed graph container.
 */

#include <vector>
#include <string>

#include "linked-list/linked-list.hpp"

#ifndef DIGRAPH
#define DIGRAPH

class Digraph
{
private:
    std::vector<List> adjVec;
    size_t edgeCount;

public:
    /**
     * Constructors
     */

    // Constructor: create empty graph
    Digraph();

    // Constructor: creates a graph with vertices 0 to V - 1
    Digraph(int V);

    // Constructor: copy graph "other"
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

    // Create a directed edge from v to w
    void addEdge(int v, int w);

    // Get all neighbors such that v has a link to that neighbor
    std::vector<int> adj(int v);
};

#endif /*DIGRAPH*/