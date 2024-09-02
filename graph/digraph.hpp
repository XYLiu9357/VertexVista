/**digraph.hpp
 *
 * Weighted directed graph container. Parallel edges
 * with the same direction are not supported.
 */

#ifndef DIGRAPH
#define DIGRAPH

#include <unordered_map>
#include <forward_list>
#include <vector>
#include <string>

#include "node-edge.hpp"

class DiGraph
{
protected:
    std::vector<Node> vertices;
    std::unordered_map<int, int> idToIndex;
    size_t edgeCount;

public:
    /**
     * Constructors
     */

    // Constructor: create empty graph
    DiGraph();

    // Constructor: creates a graph with vertices 0 to V - 1
    DiGraph(int V);

    // Constructor: creates a graph with an initializer list of vertices
    DiGraph(const std::initializer_list<int> &vertices);

    // Constructor: deep copy another graph
    DiGraph(const DiGraph &other);

    // Operator=: deep copy-and-swap
    DiGraph &operator=(const DiGraph &other);

    /**
     * Accessors
     */

    // Return number of vertices
    size_t V() const;
    // Return number of edges
    size_t E() const;

    // Return const reference to vertices vectors
    const std::vector<Node> &getVertices() const;

    // Check if the graph contains v
    bool contains(int v) const;

    // Serialization of the graph
    std::string toString(std::string delim = ",", bool doSort = false, int weightPrecision = 2);

    // Return the indegree of vertex v
    int indegree(int v) const;

    // Return the outdegree of a vertex
    int outdegree(int v) const;

    /*!
     * @function adj
     * @abstract Iterates inorder over all the neighbors of v connected by
     *           an outgoing link from v
     * @param v The query vertex
     * @return  The outgoing map in adjacency tree of v
     */
    const std::forward_list<Edge> &adj(int v) const;

    /**
     * Mutators
     */

    /*!
     * @function insertVertex
     * @abstract Insert a vertex with key v
     * @param v Key of the new vertex
     */
    void insertVertex(int v);
    void insertVertex(std::initializer_list<int> vertices);

    /*!
     * @function insertEdge
     * @abstract Insert an edge between vertex v and w if the vertices
     *           exist. If the vertices do not exist, out_of_range
     *           exception will be thrown. Weights are all set to 1
     * @param v The starting vertex
     * @param w The destination vertex
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
     * @function insertEdge
     * @abstract Insert an edge between vertex v and w if the vertices
     *           exist. If the directed edge does not exist, the function
     *           will return true.
     * @param v The starting vertex
     * @param w The destination vertex
     */
    void eraseEdge(int v, int w);
    void eraseEdge(std::initializer_list<std::pair<int, int>> edges);
};

#endif /*DIGRAPH*/