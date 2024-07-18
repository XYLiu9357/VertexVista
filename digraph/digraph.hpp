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

    // Constructor: creates a graph with an intializer list of vertices
    Digraph(std::initializer_list<int> vertices);

    // Constructor: deep copy another graph
    Digraph(Digraph &other);

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
     *           exception will be thrown.
     * @param v The starting vertex
     * @param w The destination vertex
     */
    void insertEdge(int v, int w);
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

    /*!
     * @function adj
     * @abstract Iterates inorder over all the neighbors of v connected by
     *           an outgoing link from v
     * @param v The query vertex
     * @return  An iterator for associated AdjTree
     * @todo
     */
    AdjTree adj(int v);
};

#endif /*DIGRAPH*/