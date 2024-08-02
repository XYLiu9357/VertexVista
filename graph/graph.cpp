/**graph.cpp
 *
 * Weighted directed graph container.
 */

#include <algorithm>
#include <string>
#include <stdexcept>

#include "graph.hpp"

/**
 * Constructors
 */

// Constructor: create empty graph
Graph::Graph()
    : edgeCount(0), vertices(std::vector<Node>()), idToIndex(std::unordered_map<int, int>())
{
    vertices.reserve(32);
}

// Constructor: creates a graph with vertices 0 to V - 1
Graph::Graph(int V)
    : edgeCount(0), vertices(std::vector<Node>()), idToIndex(std::unordered_map<int, int>())
{
    vertices.reserve(V);
    for (int id = 0; id < V; id++)
    {
        vertices.emplace_back(Node(id));
        idToIndex[id] = id;
    }
}

// Constructor: creates a graph with an initializer list of vertices
Graph::Graph(const std::initializer_list<int> &vertices)
    : edgeCount(0), vertices(std::vector<Node>()), idToIndex(std::unordered_map<int, int>())
{
    this->vertices.reserve(vertices.size());
    for (int id = 0; id < vertices.size(); id++)
    {
        this->vertices.emplace_back(Node(id));
        idToIndex[id] = id;
    }
}

// Constructor: deep copy another graph
Graph::Graph(const Graph &other)
    : edgeCount(other.edgeCount), vertices(other.vertices), idToIndex(other.idToIndex) {}

/**
 * Accessors
 */

// Return number of vertices
size_t Graph::V() const { return vertices.size(); }
// Return number of edges
size_t Graph::E() const { return edgeCount; }

// Check if the graph contains v
bool Graph::contains(int v) const { return idToIndex.find(v) != idToIndex.end(); }

// Serialization of the graph
std::string Graph::toString(std::string delim, int weightPrecision)
{
    // Obtain sorted copy of vertices
    std::string graphStr = "";
    std::vector<Node> sortedVertices(vertices);
    std::sort(sortedVertices.begin(), sortedVertices.end(),
              [](const Node &n1, const Node &n2)
              { return n1.getId() < n2.getId(); });

    // Construct string
    for (Node node : sortedVertices)
    {
        graphStr += std::to_string(node.getId()) + ": ";
        for (Edge edge : node.edges())
            graphStr += edge.toString(weightPrecision) + delim;
        graphStr += "\n";
    }
    return graphStr;
}

// Return the indegree of a vertex
int Graph::indegree(int v) const { return vertices[idToIndex.at(v)].getOutDeg(); }

// Return the outdegree of a vertex
int Graph::outdegree(int v) const
{
    int outdeg = 0;
    for (Node node : vertices)
    {
        if (node.hasEdgeTo(v))
            outdeg++;
    }
    return outdeg;
}

/**
 * Mutators
 */

/*!
 * @function insertVertex
 * @abstract Insert a vertex with key v
 * @param v Key of the new vertex
 */
void Graph::insertVertex(int v)
{
    if (idToIndex.find(v) == idToIndex.end())
    {
        idToIndex.insert({v, vertices.size()});
        vertices.emplace_back(Node(v));
    }
}

/*!
 * @function insertEdge
 * @abstract Insert an edge between vertex v and w if the vertices
 *           exist. If the vertices do not exist, out_of_range
 *           exception will be thrown.
 * @param from The starting vertex
 * @param to The destination vertex
 * @param weight Weight of the edge, default to 1
 */
void Graph::insertEdge(int from, int to, double weight)
{
    if (idToIndex.find(from) == idToIndex.end())
        throw std::out_of_range("Edge insertion error: vertex " + std::to_string(from) + " is not in graph");
    if (idToIndex.find(to) == idToIndex.end())
        throw std::out_of_range("Edge insertion error: vertex " + std::to_string(to) + " is not in graph");

    int fromIdx = idToIndex.at(from);
    Node &node = vertices[fromIdx];

    // Insert new if no such edge, overwrite weight otherwise
    if (!node.hasEdgeTo(to))
    {
        node.insertEdge(to, weight);
        edgeCount++;
    }
    else
        node.setWeight(to, weight);
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

    // Erase all edges to v
    int vIdx = idToIndex.at(v);
    for (Node other : vertices)
    {
        other.eraseEdgeTo(v);
        edgeCount--;
    }

    // Erase v
    edgeCount -= vertices[vIdx].getOutDeg();
    vertices.erase(vertices.begin() + vIdx);
    idToIndex.erase(v);

    // Update idToIndex map
    for (auto pair : idToIndex)
    {
        if (pair.first > vIdx)
            pair.second--;
    }
}

/*!
 * @function eraseEdge
 * @abstract Remove the edge from v to w if the edge exists. If the
 *           directed edge does not exist, out_of_range exception will
 *           be thrown.
 * @param from The starting vertex
 * @param to The destination vertex
 */
void Graph::eraseEdge(int from, int to)
{
    if (idToIndex.find(from) == idToIndex.end())
        throw std::out_of_range("Edge removal error: vertex " + std::to_string(from) + " is not in graph");
    if (idToIndex.find(to) == idToIndex.end())
        throw std::out_of_range("Edge removal error: vertex " + std::to_string(to) + " is not in graph");

    int fromIdx = idToIndex.at(from);
    Node &node = vertices[fromIdx];
    if (node.hasEdgeTo(to))
    {
        node.eraseEdgeTo(to);
        edgeCount--;
    }
    else
        return;
}

// Initializer list equivalents
void Graph::insertVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        insertVertex(v);
}

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

/*!
 * @function adj
 * @abstract Iterates inorder over all the neighbors of v connected by
 *           an outgoing link from v
 * @param v The query vertex
 * @return  The outgoing map in adjacency tree of v
 */
const std::forward_list<Edge> &Graph::adj(int v) const { return vertices[idToIndex.at(v)].edges(); }
