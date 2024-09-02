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
#include <unordered_map>
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

        // Bipartite condition check
        bool inSet1 = idMap.find(cur) != idMap.end() && !idMap.find(cur)->second;
        bool inSet2 = idMap.find(cur) != idMap.end() && idMap.find(cur)->second;
        if (inSet1 || inSet2)
        {
            if (!setId && inSet2)
                return false;
            else if (setId && inSet1)
                return false;
            else
                continue;
        }
        idMap[cur] = setId;

        // Process neighbors
        for (Edge e : g.adj(cur))
        {
            int next = e.getTo();
            bool nextSetId = !setId;
            if (idMap.find(next) == idMap.end())
                queue.push_back({next, nextSetId});
        }
    }

    return true;
}

// Iterate through all vertices to check if the graph is bipartite
bool Bipartite::bipartiteCheck(const Graph &g)
{
    idMap.clear();
    idMap.reserve(g.V());

    // Check each vertex in case the graph is disconnected
    for (const Node &node : g.getVertices())
    {
        int cur = node.getId();
        // Perform BFS from this vertex if it hasn't been visited
        if (idMap.find(cur) == idMap.end())
        {
            if (!bfsFromSrc(g, cur))
                return false;
        }
    }
    if (idMap.size() != g.V())
        throw std::logic_error("Bipartite check: partition size and graph size are inconsistent");
    return true;
}

/*!
 * @function Bipartite
 * @abstract Construct Bipartite-type object based on an
 * undirected graph.
 * @param target undirected graph used as input
 */
Bipartite::Bipartite(const Graph &target)
{
    this->g = Graph(target); // Copy

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
    this->idMap = std::unordered_map<int, bool>(other.idMap);
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
    std::swap(this->idMap, newCopy.idMap);
    std::swap(this->_isBipartite, newCopy._isBipartite);
    return *this;
}

/*!
 * @function isBipartite
 * @abstract Checks if the Bipartite object is constructed
 * based on a bipartite graph.
 * @return true if the graph is bipartite or empty, false otherwise
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
 * @exception throws std::out_of_range if graph does not contain v or w
 */
bool Bipartite::sameSet(int v, int w)
{
    if (!g.contains(v))
        throw std::out_of_range("Invalid bipartite query: invalid vertex " + std::to_string(v));
    if (!g.contains(w))
        throw std::out_of_range("Invalid bipartite query: invalid vertex " + std::to_string(w));
    if (!_isBipartite)
        return false;

    return idMap.find(v)->second == idMap.find(w)->second;
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
    if (!_isBipartite)
        return part1Set;

    for (auto p : idMap)
        if (!p.second)
            part1Set.insert(p.first);
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
    if (!_isBipartite)
        return part2Set;

    for (auto p : idMap)
        if (p.second)
            part2Set.insert(p.first);
    return part2Set;
}