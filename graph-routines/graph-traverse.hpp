/**graph-traverse.hpp
 *
 * Directed graph path search & traversal class.
 * Supports elementary path query using
 * depth-first and breadth-first traversal.
 */

#ifndef GRAPH_TRAVERSE
#define GRAPH_TRAVERSE

#include "digraph.hpp"

class DigraphPaths
{
private:
    // Keep track of path used to visit a vertex
    Map<int, int> edgeTo;
    int queryVertex;
    size_t connectedCount;

    // Reset the storage by clearing visited and edgeTo
    void reset();

    // Iterative DFS that updates visted and edgeTo
    void dfs(const Graph &G, int queryVertex);

    // Iterative BFS that updates visted and edgeTo
    void bfs(const Graph &G, int queryVertex);

public:
    /*!
     * @function DigraphPaths
     * @abstract Constructor for a DigraphPaths object that processes
     *           a digraph G and supports path query.
     * @param G           Digraph pending processing
     * @param queryVertex Vertex to initiate query
     * @param useDfs      Use depth-first traversal to process graph. Setting
     *                    it to false will invoke bread-first traversal.
     * @return DigraphPaths object that has already processed Digraph G
     */
    DigraphPaths(const Graph &G, int queryVertex, bool useDfs = true);

    /*!
     * @function hasPathTo
     * @abstract Checks whether the query vertex is connected to v
     * @param v Connectivity query vertex
     * @return True if v is connected to queryVertex, false otherwise
     */
    bool hasPathTo(int v);

    /*!
     * @function pathTo
     * @abstract Returns a sequence of vertices that represents the first
     *           path found from queryVertex to v
     * @param v Connectivity query vertex
     * @return A sequence of vertices from queryVertex to v. Empty if no
     *         such path exists.
     */
    std::vector<int> pathTo(int v);

    /*!
     * @function count
     * @abstract Returns the number of vertices connected to queryVertex
     * @return Number of vertices connected to queryVertex in graph G
     */
    size_t count();
};

#endif /*GRAPH_TRAVERSE*/