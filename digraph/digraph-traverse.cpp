/**digraph-traverse.cpp
 *
 * Directed graph path search & traversal class.
 * Supports elementary path query using
 * depth-first and breadth-first traversal.
 */

#include <stdexcept>
#include "deque.hpp"
#include "digraph-traverse.hpp"

// Reset the storage by clearing edgeTo
void DigraphPaths::reset()
{
    // Automatically calls destructor ~RedBlackTree
    edgeTo = Map<int, int>();
}

// Iterative DFS that updates edgeTo
void DigraphPaths::dfs(const Digraph &G, int queryVertex)
{
    // TODO: take advantage of the pointers somehow
    Deque<int> stack;
    edgeTo[queryVertex] = queryVertex;
    stack.push_back(queryVertex);
    connectedCount++;

    while (stack.size() > 0)
    {
        int cur = stack.pop_back();
        for (std::pair<int, int> neighbor : G.adj(cur))
        {
            if (!edgeTo.contains(neighbor.first))
            {
                connectedCount++;
                stack.push_back(neighbor.first);
                edgeTo[neighbor.first] = cur;
            }
        }
    }
}

// Iterative BFS that updates edgeTo
void DigraphPaths::bfs(const Digraph &G, int queryVertex)
{
    // TODO: take advantage of the pointers somehow
    Deque<int> queue;
    edgeTo[queryVertex] = queryVertex;
    queue.push_back(queryVertex);
    connectedCount++;

    while (queue.size() > 0)
    {
        int cur = queue.pop_front();
        for (int neighbor : G.adj(cur))
        {
            if (!edgeTo.contains(neighbor))
            {
                connectedCount++;
                queue.push_back(neighbor);
                edgeTo[neighbor] = cur;
            }
        }
    }
}

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
DigraphPaths::DigraphPaths(const Digraph &G, int queryVertex, bool useDfs)
    : queryVertex(queryVertex), connectedCount(0)
{
    if (G.V() < 1)
        throw std::out_of_range("Attempt to build paths on empty graph");

    if (!G.contains(queryVertex))
        throw std::out_of_range("Query vertex is not in graph");

    if (useDfs)
        dfs(G, queryVertex);
    else
        bfs(G, queryVertex);
}

/*!
 * @function hasPathTo
 * @abstract Checks whether the query vertex is connected to v
 * @param v Connectivity query vertex
 * @return True if v is connected to queryVertex, false otherwise
 */
bool DigraphPaths::hasPathTo(int v) { return edgeTo.contains(v); }

/*!
 * @function pathTo
 * @abstract Returns a sequence of vertices that represents the first
 *           path found from queryVertex to v
 * @param v Connectivity query vertex
 * @return A sequence of vertices from queryVertex to v. Empty if no
 *         such path exists.
 */
std::vector<int> DigraphPaths::pathTo(int v)
{
    std::vector<int> path;

    // No path from queryVertex to v
    if (!hasPathTo(v))
        return path;

    // TODO: take advantage of the pointers somehow
    // Reverse traversal direction puts path in order
    for (int cur = v; cur != queryVertex; cur = edgeTo[cur])
        path.push_back(cur);
    path.push_back(queryVertex);

    size_t pathLen = path.size();
    for (int i = 0; i < pathLen - 1 - i; i++)
        std::swap(path[i], path[pathLen - 1 - i]);

    return path;
}

/*!
 * @function count
 * @abstract Returns the number of vertices connected to queryVertex
 * @return Number of vertices connected to queryVertex in graph G
 */
size_t DigraphPaths::count() { return connectedCount; }
