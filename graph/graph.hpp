/**graph.hpp
 *
 * Weighted undirected graph container.
 * Implemented as a child class of DiGraph.
 */

#ifndef GRAPH
#define GRAPH

#include <unordered_map>
#include <vector>

#include "digraph.hpp"
#include "node-edge.hpp"

class Graph : public DiGraph
{
public:
    /**
     * Constructors
     */

    // Constructor: create empty graph
    Graph();

    // Constructor: creates a graph with vertices 0 to V - 1
    Graph(int V);

    // Constructor: creates a graph with an initializer list of vertices
    Graph(const std::initializer_list<int> &vertices);

    // Constructor: extract the underlying representation of a directed graph
    Graph(const DiGraph &digraph);

    // Constructor: deep copy another graph
    Graph(const Graph &other);

    // Operator=: deep copy-and-swap
    Graph &operator=(const Graph &other);

    /**
     * Accessors
     */

    // Return the degree of vertex v
    int degree(int v) const;

    /**
     * Mutators
     *
     * Overwrited DiGraph mutators
     */

    /*!
     * @function insertEdge
     * @abstract Insert an edge between vertex v and w if the vertices
     *           exist. If the vertices do not exist, out_of_range
     *           exception will be thrown.
     * @param v The first vertex
     * @param w The second vertex
     * @param weight Weight of the edge, default to 1
     */
    void insertEdge(int v, int w, double weight = 1);
    void insertEdge(std::initializer_list<std::pair<int, int>> edges);

    /*!
     * @function eraseVertex
     * @abstract Remove the vertex with key v. If the vertex does not exist,
     *           out_of_range exception will be thrown.
     * @param v Key of the vertex to remove
     */
    void eraseVertex(int v);
    void eraseVertex(std::initializer_list<int> vertices);

    /*!
     * @function eraseEdge
     * @abstract Remove the edge between vertices v and w if the edge exists. If the
     *           edge does not exist, out_of_range exception will be thrown.
     * @param v The first vertex
     * @param w The second vertex
     */
    void eraseEdge(int v, int w);
    void eraseEdge(std::initializer_list<std::pair<int, int>> edges);
};

#endif /*GRAPH*/