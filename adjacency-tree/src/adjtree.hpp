/**adjtree.hpp
 *
 * Interface of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support ~lgN access during Digraph traversal.
 *
 * To support efficient removal of dead edges when a vertex is removed, the adjacency
 * tree also keeps track of all the incoming vertices. This sacrifices a bit of memory
 * but brings node removal time from ~N to ~2lgN.
 *
 * NOTE: this class is not meant to be accessed directly.
 */

#ifndef ADJTREE
#define ADJTREE

#include "map.hpp"
#include "set.hpp"

class AdjTree
{
public:
    // Use two sets to keep track of incoming and outgoing links
    Set<int> outgoing;
    Set<int> incoming;

    /**
     * Constructors
     */
    AdjTree();
    AdjTree(const AdjTree &that);

    /**
     * Mutators (called by Digraph)
     *
     * The functions operate on the graphTree passeed as reference instead of this
     * AdjTree. This design choice minimizes exposure of AdjTree implementation to
     * dependent classes, e.g. Digraph.
     */

    /*!
     * @function insertGraphTreeEdge
     * @abstract Insert an edge between vertex v and w. All relevant checks should be
     *           completed before calling this function.
     * @param graphTree The digraph tree to modify
     * @param v         The starting vertex
     * @param w         The destination vertex
     */
    static void insertGraphTreeEdge(Map<int, AdjTree> &graphTree, int v, int w);

    /*!
     * @function eraseGraphTreeVertex
     * @abstract Remove the vertex with key v. All relevant checks should be
     *           completed before calling this function.
     * @param graphTree The digraph tree to modify
     * @param v         Key of the vertex to remove
     * @return          Number of edges removed
     */
    static size_t eraseGraphTreeVertex(Map<int, AdjTree> &graphTree, int v);

    /*!
     * @function eraseGraphTreeEdge
     * @abstract Remove the edge from v to w if the edge exists. All relevant
     *           checks should be completed before calling this function.
     * @param graphTree The digraph tree to modify
     * @param v         The starting vertex
     * @param w         The destination vertex
     */
    static void eraseGraphTreeEdge(Map<int, AdjTree> &graphTree, int v, int w);

    /**
     * Tree Processing
     */

    // Serialize adjacency tree
    std::string toString(const std::string &delim = ",");

    /**
     * Destructor
     */
    ~AdjTree();
};

#endif /*ADJTREE*/