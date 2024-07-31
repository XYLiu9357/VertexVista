/**adjtree.cpp
 *
 * Implementation of adjacency tree. Adjacency tree is used to store the neighbors of a
 * vertex and support ~lgN access during Digraph traversal.
 *
 * To support efficient removal of dead edges when a vertex is removed, the adjacency
 * tree also keeps track of all the incoming vertices. This sacrifices a bit of memory
 * but brings node removal time from ~N to ~2lgN.
 *
 * NOTE: this class is not meant to be accessed directly.
 */

#include "adjtree.hpp"

/**
 * Constructors
 */
AdjTree::AdjTree()
    : outgoing(Map<int, int>()), incoming(Set<int>()) {}

// Deep copy
AdjTree::AdjTree(const AdjTree &that)
{
    // Calls copy constructor of Set and Map
    this->outgoing = Map<int, int>(that.outgoing);
    this->incoming = Set<int>(that.incoming);
}

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
 * @param weight    The weight of the edge inserted
 */
void AdjTree::insertGraphTreeEdge(Map<int, AdjTree> &graphTree, int v, int w, int weight)
{
    graphTree[v].outgoing.insert({w, weight});
    graphTree[w].incoming.insert(v);
}

/*!
 * @function eraseGraphTreeVertex
 * @abstract Remove the vertex with key v. All relevant checks should be
 *           completed before calling this function.
 * @param graphTree The digraph tree to modify
 * @param v         Key of the vertex to remove
 * @return          Number of edges removed
 */
size_t AdjTree::eraseGraphTreeVertex(Map<int, AdjTree> &graphTree, int v)
{
    AdjTree &curAdjTree = graphTree[v];
    size_t edgesErased = 0;

    for (int w : curAdjTree.incoming)
    {
        if (graphTree.find(w) != graphTree.end())
        {
            graphTree[w].outgoing.erase(v);
            edgesErased++;
        }
    }

    edgesErased += curAdjTree.outgoing.size();
    graphTree.erase(v);
    return edgesErased;
}

/*!
 * @function eraseGraphTreeEdge
 * @abstract Remove the edge from v to w if the edge exists. All relevant
 *           checks should be completed before calling this function.
 * @param graphTree The digraph tree to modify
 * @param v         The starting vertex
 * @param w         The destination vertex
 */
void AdjTree::eraseGraphTreeEdge(Map<int, AdjTree> &graphTree, int v, int w)
{
    graphTree[v].outgoing.erase(w);
    graphTree[w].incoming.erase(v);
}

/**
 * Tree Processing
 */

// Serialize adjacency tree
std::string AdjTree::toString(const std::string &delim)
{
    std::string serializedStr = "";
    for (std::pair<int, int> p : this->outgoing)
        serializedStr += std::to_string(p.first) + "[" + std::to_string(p.second) + "]" + delim;

    return serializedStr;
}

/**
 * Destructor
 */
AdjTree::~AdjTree()
{
}