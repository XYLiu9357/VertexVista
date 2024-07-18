/**adjtree.hpp
 *
 * Interface of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support O(1) access during Digraph traversal.
 */

#ifndef ADJTREE
#define ADJTREE

#include "rbtree.hpp"

class AdjTree : public RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>
{
    /**
     * The integer key represents a neighbor
     * RedBlackTree<int, AdjTree>::TreeNode * points to the neighbor's TreeNode in the
     * Digraph tree. The Digraph tree itself is RedBlackTree<int, AdjTree>.
     */
public:
    /**
     * Constructors
     */
    AdjTree();
    AdjTree(const std::initializer_list<std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *>> &init);
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
    static void insertGraphTreeEdge(RedBlackTree<int, AdjTree> &graphTree, int v, int w);

    /*!
     * @function eraseGraphTreeVertex
     * @abstract Remove the vertex with key v. All relevant checks should be
     *           completed before calling this function.
     * @param graphTree The digraph tree to modify
     * @param v         Key of the vertex to remove
     * @return          Number of edges removed
     */
    static size_t eraseGraphTreeVertex(RedBlackTree<int, AdjTree> &graphTree, int v);

    /*!
     * @function eraseGraphTreeEdge
     * @abstract Remove the edge from v to w if the edge exists. All relevant
     *           checks should be completed before calling this function.
     * @param graphTree The digraph tree to modify
     * @param v         The starting vertex
     * @param w         The destination vertex
     */
    static void eraseGraphTreeEdge(RedBlackTree<int, AdjTree> &graphTree, int v, int w);

    /**
     * Tree Processing
     */

    // Serialize adjacency tree
    std::string toString(const std::string &delim = ",");
};

#endif /*ADJTREE*/