/**digraph.hpp
 *
 * Header for directed graph container.
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "linked-list/linked-list.hpp"

class Digraph
{
private:
    std::vector<List> adjList;

public:
    /**
     * Constructors
     */

    // Constructor: create empty graph
    Digraph();

    // Constructor: creates a graph with vertices 0 to V - 1
    Digraph(int V);

    // Constructor: creates graph from input stream
    Digraph(std::istream in, char delim);

    /**
     * Accessors
     */

    // Return number of vertices
    int V();

    // Return number of edges
    int E();

    // Serialization of the graph
    std::string toString();

    // Create a directed edge
    void addEdge(int v, int w);

    // Get all neighbors such that v has a link to that neighbor
    std::vector<int> adj(int v);
};