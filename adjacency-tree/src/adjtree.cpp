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
 * Mutators
 */

/*!
 * @function insertGraphTreeEdge
 * @abstract Insert an edge between vertex v and w. All relevant checks should be
 *           completed before calling this function.
 * @param graphTree The digraph tree to modify
 * @param v         The starting vertex
 * @param w         The destination vertex
 */
void AdjTree::insertGraphTreeEdge(RedBlackTree<int, AdjTree> &graphTree, int v, int w)
{
    RedBlackTree<int, AdjTree>::TreeNode *queryPtr = graphTree._at(graphTree.root, v);
    graphTree[v].insert({w, queryPtr});
}

/*!
 * @function eraseGraphTreeVertex
 * @abstract Remove the vertex with key v. All relevant checks should be
 *           completed before calling this function.
 * @param graphTree The digraph tree to modify
 * @param v         Key of the vertex to remove
 * @return          Number of edges removed
 */
size_t AdjTree::eraseGraphTreeVertex(RedBlackTree<int, AdjTree> &graphTree, int v)
{
    RedBlackTree<int, AdjTree>::TreeNode *cur = graphTree.root;
    Deque<RedBlackTree<int, AdjTree>::TreeNode *> stack;
    size_t edgesRemoved = 0;

    // Erase all links to vertex v
    while (cur || !stack.empty())
    {
        while (cur)
        {
            stack.push_back(cur);
            cur = cur->left;
        }
        cur = stack.pop_back();
        if (cur->p.second.contains(v))
        {
            cur->p.second.erase(v);
            edgesRemoved++;
        }
        cur = cur->right;
    }

    // Erase vertex v
    edgesRemoved += graphTree[v].size();
    graphTree.erase(v);

    return edgesRemoved;
}

/*!
 * @function eraseGraphTreeEdge
 * @abstract Remove the edge from v to w if the edge exists. All relevant
 *           checks should be completed before calling this function.
 * @param graphTree The digraph tree to modify
 * @param v         The starting vertex
 * @param w         The destination vertex
 */
void AdjTree::eraseGraphTreeEdge(RedBlackTree<int, AdjTree> &graphTree, int v, int w)
{
    graphTree.find(v)->second.erase(w);
}

/**
 * Tree Processing
 */

// Serialize adjacency tree
std::string AdjTree::toString(const std::string &delim)
{
    std::string serializedStr = "";
    for (std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *> pair : *this)
        serializedStr += std::to_string(pair.first) + delim;

    return serializedStr;
}