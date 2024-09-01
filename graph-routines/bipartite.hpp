/**bipartite.hpp
 *
 * A bipartite graph is a graph where all vertices can be divided into two disjoint sets
 * such that no two graph vertices within the same set are adjacent.
 *
 * This routine returns the two partitions as iterable data types.
 */

#ifndef BIPARTITE
#define BIPARTITE

#include <set>
#include <unordered_map>
#include "graph/graph.hpp"
#include "graph/digraph.hpp"

class Bipartite
{
private:
    Graph g;
    std::unordered_map<int, bool> idMap;
    bool _isBipartite;

    // BFS to check if the graph is bipartite starting from one source
    bool bfsFromSrc(const Graph &g, int src);

    // Iterate through all vertices to check if the graph is bipartite
    bool bipartiteCheck(const Graph &g);

public:
    /*!
     * @function Bipartite
     * @abstract Construct Bipartite-type object based on an
     * undirected graph.
     * @param target undirected graph used as input
     */
    Bipartite(const Graph &target);

    /*!
     * @function Bipartite
     * @abstract Copy constructor for Bipartite-type object.
     * @param other another Bipartite-type object
     */
    Bipartite(const Bipartite &other);

    /*!
     * @function operator=
     * @abstract Copy-assignment operator for Bipartite-type object.
     * @param other another Bipartite-type object
     */
    Bipartite &operator=(const Bipartite &other);

    /*!
     * @function isBipartite
     * @abstract Checks if the Bipartite object is constructed
     * based on a bipartite graph.
     * @return true if the graph is bipartite, false otherwise
     */
    bool isBipartite();

    /*!
     * @function sameSet
     * @abstract Checks if two query vertices are in the same set
     * @param v first query vertex
     * @param w second query vertex
     * @return true if v and w are in the same set, false otherwise or if the graph is not bipartite.
     * @exception throws std::out_of_range if graph does not contain v or w
     */
    bool sameSet(int v, int w);

    /*!
     * @function getPart1
     * @abstract Returns the first set of vertices if the graph is bipartite.
     *           Returns empty std::set<int> if graph is not bipartite.
     * @return the first set of vertices. Empty if graph is not bipartite.
     * @exception throws std::out_of_range if graph is empty
     */
    std::set<int> getPart1();

    /*!
     * @function getPart2
     * @abstract Returns the second (other) set of vertices if the graph is bipartite.
     *           Returns empty std::set<int> if graph is not bipartite.
     * @return the second set of vertices. Empty if graph is not bipartite.
     * @exception throws std::out_of_range if graph is empty
     */
    std::set<int> getPart2();
};

#endif /*BIPARTITE*/