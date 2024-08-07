/**bipartite.cpp
 *
 * A bipartite graph is a graph where all vertices can be divided into two disjoint sets
 * such that no two graph vertices within the same set are adjacent.
 *
 * This routine returns the two partitions as iterable data types.
 */

#include "graph/graph.hpp"
#include "bipartite.hpp"

// DFS to check if the graph is bipartite
bool dfsBipartite() {}

/*!
 * @function Bipartite
 * @abstract Construct Bipartite-type object based on a
 * directed graph.
 * @param target directed graph used as input
 */
Bipartite::Bipartite(const Graph &target)
{
    this->g = target;
    this->_isBipartite = dfsBipartite();
}

/*!
 * @function Bipartite
 * @abstract Copy constructor for Bipartite-type object.
 * @param other another Bipartite-type object
 */
Bipartite::Bipartite(const Bipartite &other) {}

/*!
 * @function isBipartite
 * @abstract Checks if the Bipartite object is constructed
 * based on a bipartite graph.
 * @return true if the graph is bipartite, false otherwise
 */
bool Bipartite::isBipartite() {}

/*!
 * @function sameSet
 * @abstract Checks if two query vertices are in the same set
 * @param v first query vertex
 * @param w second query vertex
 * @return true if v and w are in the same set, false otherwise
 */
bool Bipartite::sameSet(int v, int w) {}

/*!
 * @function getPart1
 * @abstract Returns the first set of vertices
 * @return the first set of vertices
 */
const std::set<int> &Bipartite::getPart1() {}

/*!
 * @function getPart2
 * @abstract Returns the second (other) set of vertices
 * @return the second set of vertices
 */
const std::set<int> &Bipartite::getPart2() {}