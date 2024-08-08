/**bipartite.cpp
 *
 * A bipartite graph is a graph where all vertices can be divided into two disjoint sets
 * such that no two graph vertices within the same set are adjacent.
 *
 * This routine returns the two partitions as iterable data types.
 */

#include <string>
#include <stdexcept>
#include <algorithm>

#include "bipartite.hpp"
#include "graph/graph.hpp"

// DFS to check if the graph is bipartite
bool Bipartite::dfsBipartite(int curId)
{
}

/*!
 * @function Bipartite
 * @abstract Construct Bipartite-type object based on a
 * directed graph.
 * @param target directed graph used as input
 */
Bipartite::Bipartite(const Graph &target)
{
    this->g = target;
}

/*!
 * @function Bipartite
 * @abstract Copy constructor for Bipartite-type object.
 * @param other another Bipartite-type object
 */
Bipartite::Bipartite(const Bipartite &other)
{
    this->g = Graph(other.g);
    this->vertexSet1 = std::set<int>(other.vertexSet1);
    this->vertexSet2 = std::set<int>(other.vertexSet2);
    this->_isBipartite = other._isBipartite;
}

/*!
 * @function operator=
 * @abstract copy-assignment operator for Bipartite-type object.
 * @param other another Bipartite-type object
 */
Bipartite &Bipartite::operator=(const Bipartite &other)
{
    Bipartite newCopy(other);
    std::swap(this->g, newCopy.g);
    std::swap(this->vertexSet1, newCopy.vertexSet1);
    std::swap(this->vertexSet2, newCopy.vertexSet2);
    std::swap(this->_isBipartite, newCopy._isBipartite);
    return *this;
}

/*!
 * @function isBipartite
 * @abstract Checks if the Bipartite object is constructed
 * based on a bipartite graph.
 * @return true if the graph is bipartite or empty, false otherwise
 * @exception throws std::out_of_range if graph is empty
 */
bool Bipartite::isBipartite()
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");
    return _isBipartite;
}

/*!
 * @function sameSet
 * @abstract Checks if two query vertices are in the same set
 * @param v first query vertex
 * @param w second query vertex
 * @return true if v and w are in the same set, false otherwise or if the graph is not bipartite.
 * @exception throws std::out_of_range if graph is empty
 */
bool Bipartite::sameSet(int v, int w)
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");
    if (!_isBipartite)
        return false;

    bool set1HasV = vertexSet1.find(v) != vertexSet1.end();
    bool set1HasW = vertexSet1.find(w) != vertexSet1.end();
    return set1HasV ^ set1HasW;
}

/*!
 * @function getPart1
 * @abstract Returns the first set of vertices
 * @return the second set of vertices. Empty if graph is not bipartite.
 * @exception throws std::out_of_range if graph is empty
 */
const std::set<int> &Bipartite::getPart1()
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");

    if (_isBipartite)
        return vertexSet1;
    else
        return std::set<int>();
}

/*!
 * @function getPart2
 * @abstract Returns the second (other) set of vertices
 * @return the second set of vertices. Empty if graph is not bipartite.
 * @exception throws std::out_of_range if graph is empty
 */
const std::set<int> &Bipartite::getPart2()
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");

    if (_isBipartite)
        return vertexSet2;
    else
        return std::set<int>();
}