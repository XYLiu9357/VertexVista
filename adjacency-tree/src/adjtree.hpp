/**adjtree.hpp
 *
 * Interface of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support O(1) access during Digraph traversal.
 */

#ifndef ADJTREE
#define ADJTREE

#include "rbtree.hpp"

class AdjTree : private RedBlackTree<int, RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>>
{
public:
    /**
     * Constructors
     */
    AdjTree();
    AdjTree(const std::initializer_list<std::pair<int, RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>>> &init);
    AdjTree(const AdjTree &that);

    /**
     * Insertion
     */
    void insertVertex(int v);
    void insertEdge(int v, int w);

    /**
     * Removal
     */
    void eraseVertex(int v);
    void eraseEdge(int v, int w);

    /**
     * Tree Processing
     */

    // Serialize adjacency tree
    std::string toString();
};

#endif /*ADJTREE*/