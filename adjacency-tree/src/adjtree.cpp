/**adjtree.hpp
 *
 * Implementation of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support O(1) access during Digraph traversal.
 */

#include "adjtree.hpp"

/**
 * Constructors
 */
AdjTree::AdjTree() {}
AdjTree::AdjTree(const std::initializer_list<std::pair<int, RedBlackTree<int, RedBlackTree<int, AdjTree>::TreeNode *>>> &init) {}

// TODO: deep copy fix
AdjTree::AdjTree(const AdjTree &that) {}

/**
 * Insertion
 */
void AdjTree::insertVertex(int v) {}
void AdjTree::insertEdge(int v, int w) {}

/**
 * Removal
 */
void AdjTree::eraseVertex(int v) {}
void AdjTree::eraseEdge(int v, int w) {}

/**
 * Tree Processing
 */

// Serialize adjacency tree
std::string AdjTree::toString() {}