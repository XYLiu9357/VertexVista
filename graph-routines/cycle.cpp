/**cycle.hpp
 *
 * A cycle in a directed graph is a non-empty path in which only the
 * start and last vertices are the same. In particular, empty graphs
 * are not cyclic.
 *
 * This function checks if there exists a cycle in the directed graph.
 *
 * For undirected graph, each edge is treated as bidirectional edges
 * in a directed graph setting.
 */
#include <stack>
#include <queue>
#include <unordered_map>
#include "cycle.hpp"
#include "graph/digraph.hpp"

/*!
 *@function isCyclic
 * @abstract Checks whether the directed graph is cyclic.
 * @param target the target DiGraph
 * @return True if the graph is cyclic, false otherwise.
 */
bool isCyclic(const DiGraph &target)
{
    std::unordered_map<int, int> inDegree;
    for (const Node &node : target.getVertices())
    {
        inDegree[node.getId()] = 0;
    }

    for (const Node &node : target.getVertices())
    {
        int v = node.getId();
        for (const Edge &e : target.adj(v))
        {
            int neighbor = e.getTo();
            inDegree[neighbor]++;
        }
    }

    std::stack<int> stk;
    for (const Node &node : target.getVertices())
    {
        int v = node.getId();
        if (inDegree[v] == 0)
            stk.push(v);
    }

    int visitedCount = 0;
    while (!stk.empty())
    {
        int node = stk.top();
        stk.pop();
        visitedCount++;

        for (const Edge &e : target.adj(node))
        {
            int neighbor = e.getTo();
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                stk.push(neighbor);
        }
    }

    return visitedCount != target.V();
}

// Cycle check helper for undirected graphs
bool bfsCycleCheck(int start, const Graph &target, std::unordered_map<int, bool> &visited)
{
    std::queue<std::pair<int, int>> q; // Pair of (current node, parent node)
    visited[start] = true;
    q.push({start, -1}); // Start node has no parent

    while (!q.empty())
    {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        // Traverse all adjacent vertices
        for (const Edge &e : target.adj(node))
        {
            int neighbor = e.getTo();
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push({neighbor, node});
            }
            // If an adjacent vertex is visited and isn't the parent, we have a cycle
            else if (neighbor != parent)
            {
                return true;
            }
        }
    }
    return false;
}

/*!
 *@function isCyclic
 * @abstract Checks whether the undirected graph is cyclic.
 * @param target the target Graph
 * @return True if the graph is cyclic, false otherwise.
 */
bool isCyclic(const Graph &target)
{
    std::unordered_map<int, bool> visited;
    for (const Node &node : target.getVertices())
        visited[node.getId()] = false;

    // Check all components of the graph (important for disconnected graphs)
    for (const Node &node : target.getVertices())
    {
        int v = node.getId();
        if (!visited[v])
        {
            if (bfsCycleCheck(v, target, visited))
                return true;
        }
    }
    return false;
}