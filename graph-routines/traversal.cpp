/**traversal.cpp
 *
 * Directed graph path search & traversal class.
 * Supports elementary path query using
 * depth-first and breadth-first traversal.
 */

#include <stdexcept>
#include "utils/deque.hpp"
#include "traversal.hpp"

// Reset the storage by clearing edgeTo
void GraphPaths::reset() { edgeTo.clear(); }

// Iterative DFS that updates edgeTo
void GraphPaths::dfs(const DiGraph &G, int queryVertex)
{
    reset();
    Deque<int> stack;
    edgeTo[queryVertex] = queryVertex;
    stack.push_back(queryVertex);
    connectedCount++;

    while (stack.size() > 0)
    {
        int cur = stack.pop_back();
        for (const Edge &edge : G.adj(cur))
        {
            if (edgeTo.find(edge.getTo()) == edgeTo.end())
            {
                connectedCount++;
                stack.push_back(edge.getTo());
                edgeTo[edge.getTo()] = cur;
            }
        }
    }
}

// Iterative BFS that updates edgeTo
void GraphPaths::bfs(const DiGraph &G, int queryVertex)
{
    // TODO: take advantage of the pointers somehow
    Deque<int> queue;
    edgeTo[queryVertex] = queryVertex;
    queue.push_back(queryVertex);
    connectedCount++;

    while (queue.size() > 0)
    {
        int cur = queue.pop_front();
        for (const Edge &edge : G.adj(cur))
        {
            if (edgeTo.find(edge.getTo()) == edgeTo.end())
            {
                connectedCount++;
                queue.push_back(edge.getTo());
                edgeTo[edge.getTo()] = cur;
            }
        }
    }
}

/*!
 * @function GraphPaths
 * @abstract Constructor for a GraphPaths object that processes
 *           a digraph G and supports path query.
 * @param G           Graph pending processing
 * @param queryVertex Vertex to initiate query
 * @param useDfs      Use depth-first traversal to process graph. Setting
 *                    it to false will invoke bread-first traversal.
 * @return GraphPaths object that has already processed Graph G
 */
GraphPaths::GraphPaths(const DiGraph &G, int queryVertex, bool useDfs)
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
bool GraphPaths::hasPathTo(int v) { return edgeTo.find(v) != edgeTo.end(); }

/*!
 * @function pathTo
 * @abstract Returns a sequence of vertices that represents the first
 *           path found from queryVertex to v
 * @param v Connectivity query vertex
 * @return A sequence of vertices from queryVertex to v. Empty if no
 *         such path exists.
 */
std::vector<int> GraphPaths::pathTo(int v)
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
size_t GraphPaths::count() { return connectedCount; }
