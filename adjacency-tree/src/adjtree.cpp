/**adjtree.hpp
 *
 * Implementation of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support O(1) access during Digraph traversal.
 */

#include "adjtree.hpp"

/**
 * Constructors
 */
AdjTree::AdjTree()
    : RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>() {}

AdjTree::AdjTree(const std::initializer_list<std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *>> &init)
    : RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>(init) {}

// This makes a deep copy because operator= in RedBlackTree makes a deep-copied assignment
AdjTree::AdjTree(const AdjTree &that)
    : RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>(that) {}

/**
 * Tree Processing
 */

// Serialize adjacency tree
std::string AdjTree::toString(const std::string &delim)
{
    if (empty())
        throw std::out_of_range("Invalid serialization of empty container");

    std::string serializedStr = "";
    for (std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *> pair : *this)
        serializedStr += std::to_string(pair.first) + delim;

    return serializedStr;
}