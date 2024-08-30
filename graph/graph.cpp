/**graph.cpp
 *
 * Weighted undirected graph container.
 * Implemented as a child class of DiGraph.
 */

#include <algorithm>
#include <stdexcept>

#include "digraph.hpp"
#include "graph.hpp"

// Constructor: create empty graph
Graph::Graph() : DiGraph() {}

// Constructor: creates a graph with vertices 0 to V - 1
Graph::Graph(int V) : DiGraph(V) {}

// Constructor: creates a graph with an initializer list of vertices
Graph::Graph(const std::initializer_list<int> &vertices) : DiGraph(vertices) {}

// Constructor: extract the underlying representation of a directed graph
Graph::Graph(const DiGraph &digraph)
{
    // Copy all vertices from the directed graph to the undirected graph
    for (const Node &vertex : digraph.getVertices())
        this->insertVertex(vertex.getId());

    // Iterate over all vertices
    for (const Node &vertex : digraph.getVertices())
    {
        int v = vertex.getId();
        const std::forward_list<Edge> &edges = digraph.adj(v);
        for (const Edge &edge : edges)
        {
            int w = edge.getTo();
            double weight = edge.getWeight();
            this->insertEdge(v, w, weight);

            // Insert the reverse edge w -> v to make it undirected
            if (!digraph.contains(w) ||
                std::find_if(digraph.adj(w).begin(), digraph.adj(w).end(),
                             [v](const Edge &e)
                             { return e.getTo() == v; }) == digraph.adj(w).end())
            {
                this->insertEdge(w, v, weight);
            }
        }
    }
}

// Constructor: deep copy another graph
Graph::Graph(const Graph &other) : DiGraph(other) {}

// Operator=: deep copy-and-swap
Graph &Graph::operator=(const Graph &other)
{ // Copy and swap
    Graph newCopy(other);
    std::swap(this->vertices, newCopy.vertices);
    std::swap(this->idToIndex, newCopy.idToIndex);
    std::swap(this->edgeCount, newCopy.edgeCount);
    return *this;
}

/**
 * Accessors
 */

// Return the degree of a vertex
int Graph::degree(int v) const
{
    if (indegree(v) != outdegree(v))
        throw std::logic_error("Graph: undirected graph has inconsistent degrees");
    return indegree(v);
}

/**
 * Mutators
 */

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the vertices do not exist, out_of_range
 *           exception will be thrown.
 * @param v The first vertex
 * @param w The second vertex
 * @param weight Weight of the edge, default to 1
 */
void Graph::insertEdge(int v, int w, double weight)
{
    if (idToIndex.find(v) == idToIndex.end())
        throw std::out_of_range("Edge insertion error: vertex " + std::to_string(v) + " is not in graph");
    if (idToIndex.find(w) == idToIndex.end())
        throw std::out_of_range("Edge insertion error: vertex " + std::to_string(w) + " is not in graph");

    int vIdx = idToIndex.at(v);
    int wIdx = idToIndex.at(w);
    Node &nodeV = vertices[vIdx];
    Node &nodeW = vertices[wIdx];

    // Insert new edges if they do not exist, overwrite weights otherwise
    if (!nodeV.hasEdgeTo(w))
    {
        nodeV.insertEdge(w, weight);
        nodeW.insertEdge(v, weight); // Insert reverse edge
        edgeCount++;
    }
    else
    {
        nodeV.setWeight(w, weight);
        nodeW.setWeight(v, weight); // Update reverse edge weight
    }
}

/*!
 * @function eraseVertex
 * @abstract Remove the vertex with key v. If the vertex does not exist,
 *           out_of_range exception will be thrown.
 * @param v Key of the vertex to remove
 */
void Graph::eraseVertex(int v)
{
    if (idToIndex.find(v) == idToIndex.end())
        throw std::out_of_range("Vertex removal error: vertex " + std::to_string(v) + " is not in graph");

    int vIdx = idToIndex.at(v);
    Node &nodeV = vertices[vIdx];

    // Erase all edges from other vertices to v
    for (Node &other : vertices)
    {
        // Skip if it's v itself
        if (other.getId() == v)
            continue;
        // If there's an edge from other to v, remove it and the reverse edge
        if (other.hasEdgeTo(v))
        {
            other.eraseEdgeTo(v);
            nodeV.eraseEdgeTo(other.getId()); // Erase reverse edge
            edgeCount--;
        }
    }

    // Erase vertex v itself
    edgeCount -= nodeV.getOutDeg();
    vertices.erase(vertices.begin() + vIdx);
    idToIndex.erase(v);

    // Update idToIndex map
    for (auto &pair : idToIndex)
    {
        if (pair.second > vIdx)
            pair.second--;
    }
}

/*!
 * @function eraseEdge
 * @abstract Remove the edge between vertices v and w if the edge exists. If the
 *           edge does not exist, out_of_range exception will be thrown.
 * @param v The first vertex
 * @param w The second vertex
 */
void Graph::eraseEdge(int v, int w)
{
    if (idToIndex.find(v) == idToIndex.end())
        throw std::out_of_range("Edge removal error: vertex " + std::to_string(v) + " is not in graph");
    if (idToIndex.find(w) == idToIndex.end())
        throw std::out_of_range("Edge removal error: vertex " + std::to_string(w) + " is not in graph");

    int vIdx = idToIndex.at(v);
    int wIdx = idToIndex.at(w);
    Node &nodeV = vertices[vIdx];
    Node &nodeW = vertices[wIdx];

    if (nodeV.hasEdgeTo(w))
    {
        nodeV.eraseEdgeTo(w);
        nodeW.eraseEdgeTo(v); // Remove reverse edge
        edgeCount--;
    }
    else
        return;
}

// Initializer list equivalents
void Graph::insertEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        insertEdge(edge.first, edge.second);
}
void Graph::eraseVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        eraseVertex(v);
}

void Graph::eraseEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        eraseEdge(edge.first, edge.second);
}
