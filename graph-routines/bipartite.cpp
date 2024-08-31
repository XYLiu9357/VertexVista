/**bipartite.cpp
 *
 * A bipartite graph is a graph where all vertices can be divided into two disjoint sets
 * such that no two graph vertices within the same set are adjacent.
 *
 * This routine returns the two partitions as iterable data types.
 */

#include <string>
#include <deque>
#include <set>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>
#include <utility>

#include "bipartite.hpp"
#include "graph/graph.hpp"
#include "graph/digraph.hpp"

// BFS to check if the graph is bipartite starting from one source
bool Bipartite::bfsFromSrc(const Graph &g, int src)
{
    std::deque<std::pair<int, bool>> queue;

    queue.push_back({src, false});
    while (!queue.empty())
    {
        std::pair<int, bool> curPair = queue.front();
        queue.pop_front();
        int cur = curPair.first;
        bool setId = curPair.second;
        bool inSet1 = vertexSet1.find(cur) != vertexSet1.end();
        bool inSet2 = vertexSet2.find(cur) != vertexSet2.end();

        // Bipartite condition check
        if (inSet1 || inSet2)
        {
            if (!setId && inSet2)
                return false;
            else if (setId && inSet1)
                return false;
            else
                continue;
        }

        if (setId)
            vertexSet2.insert(cur);
        else
            vertexSet1.insert(cur);

        // Process neighbors
        for (Edge e : g.adj(cur))
        {
            int next = e.getTo();
            bool nextSetId = !setId;
            bool nextInSet1 = vertexSet1.find(next) != vertexSet1.end();
            bool nextInSet2 = vertexSet2.find(next) != vertexSet2.end();
            if (!nextInSet1 && !nextInSet2)
                queue.push_back({next, nextSetId});
        }
    }

    return true;
}

// Iterate through all vertices to check if the graph is bipartite
bool Bipartite::bipartiteCheck(const Graph &g)
{
    vertexSet1.clear();
    vertexSet2.clear();

    // Check each vertex in case the graph is disconnected
    for (const Node &node : g.getVertices())
    {
        int cur = node.getId();
        bool inSet1 = vertexSet1.find(cur) != vertexSet1.end();
        bool inSet2 = vertexSet2.find(cur) != vertexSet2.end();

        // Perform BFS from this vertex if it hasn't been visited
        if (!inSet1 && !inSet2)
        {
            if (!bfsFromSrc(g, cur))
                return false;
        }
    }

    if (vertexSet1.size() + vertexSet2.size() != g.V())
        throw std::logic_error("Bipartite check: partition size and graph size are inconsistent");
    return true;
}

/*!
 * @function Bipartite
 * @abstract Construct Bipartite-type object based on a
 * directed graph.
 * @param target directed graph used as input
 */
Bipartite::Bipartite(const DiGraph &target)
{
    this->g = Graph(target); // Copy and extract undirected representation

    // Trivially bipartite
    if (g.V() == 0 || g.V() == 1)
        this->_isBipartite = true;
    else
        this->_isBipartite = bipartiteCheck(g);
}

/*!
 * @function Bipartite
 * @abstract Copy constructor for Bipartite-type object.
 * @param other another Bipartite-type object
 */
Bipartite::Bipartite(const Bipartite &other)
{
    this->g = DiGraph(other.g);
    this->vertexSet1 = std::unordered_set<int>(other.vertexSet1);
    this->vertexSet2 = std::unordered_set<int>(other.vertexSet2);
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
    return !(set1HasV ^ set1HasW);
}

/*!
 * @function getPart1
 * @abstract Returns the first set of vertices if the graph is bipartite.
 *           Returns empty std::set<int> if graph is not bipartite.
 * @return the first set of vertices. Empty if graph is not bipartite.
 * @exception throws std::out_of_range if graph is empty
 */
std::set<int> Bipartite::getPart1()
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");

    std::set<int> part1Set;
    if (_isBipartite)
        for (int id : vertexSet1)
            part1Set.insert(id);
    return part1Set;
}

/*!
 * @function getPart2
 * @abstract Returns the second (other) set of vertices if the graph is bipartite.
 *           Returns empty std::set<int> if graph is not bipartite.
 * @return the second set of vertices. Empty if graph is not bipartite.
 * @exception throws std::out_of_range if graph is empty
 */
std::set<int> Bipartite::getPart2()
{
    if (g.V() == 0)
        throw std::out_of_range("Invalid bipartite query: graph is empty");

    std::set<int> part2Set;
    if (_isBipartite)
        for (int id : vertexSet2)
            part2Set.insert(id);
    return part2Set;
}