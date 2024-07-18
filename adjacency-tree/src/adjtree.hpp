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
     * Tree Processing
     */

    // Serialize adjacency tree
    std::string toString(const std::string &delim = ",");
};

#endif /*ADJTREE*/