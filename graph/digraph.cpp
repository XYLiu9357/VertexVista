/**digraph.cpp
 *
 * Weighted directed graph container.
 */

#include <algorithm>
#include <string>
#include <stdexcept>

#include "digraph.hpp"

/**
 * Constructors
 */

// Constructor: create empty graph
DiGraph::DiGraph()
    : edgeCount(0), vertices(std::vector<Node>()), idToIndex(std::unordered_map<int, int>())
{
    vertices.reserve(32);
}

// Constructor: creates a graph with vertices 0 to V - 1
DiGraph::DiGraph(int V)
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
DiGraph::DiGraph(const std::initializer_list<int> &vertices)
    : edgeCount(0), vertices(std::vector<Node>()), idToIndex(std::unordered_map<int, int>())
{
    this->vertices.reserve(vertices.size());
    int curIdx = 0;
    for (int id : vertices)
    {
        this->vertices.emplace_back(Node(id));
        idToIndex[id] = curIdx;
        curIdx++;
    }
}

// Constructor: deep copy another graph
DiGraph::DiGraph(const DiGraph &other)
    : edgeCount(other.edgeCount), vertices(other.vertices), idToIndex(other.idToIndex) {}

// Operator=: deep copy-and-swap
DiGraph &DiGraph::operator=(const DiGraph &other)
{
    // Copy and swap
    DiGraph newCopy(other);
    std::swap(this->vertices, newCopy.vertices);
    std::swap(this->idToIndex, newCopy.idToIndex);
    std::swap(this->edgeCount, newCopy.edgeCount);
    return *this;
}

/**
 * Accessors
 */

// Return number of vertices
size_t DiGraph::V() const { return vertices.size(); }
// Return number of edges
size_t DiGraph::E() const { return edgeCount; }

// Return const reference to vertices vectors
const std::vector<Node> &DiGraph::getVertices() const { return vertices; }

// Check if the graph contains v
bool DiGraph::contains(int v) const { return idToIndex.find(v) != idToIndex.end(); }

// Serialization of the graph
std::string DiGraph::toString(std::string delim, bool doSort, int weightPrecision)
{
    // Obtain sorted copy of vertices
    std::string graphStr = "";
    std::vector<Node> toStringVertices(vertices);

    // Sort vertices if needed
    if (doSort)
    {
        std::sort(toStringVertices.begin(), toStringVertices.end(),
                  [](const Node &n1, const Node &n2)
                  { return n1.getId() < n2.getId(); });
    }

    // Construct string
    for (const Node &node : toStringVertices)
    {
        graphStr += std::to_string(node.getId()) + ": ";
        std::forward_list<Edge> toStringEdges(node.edges());

        // Sort edges if needed
        if (doSort)
        {
            toStringEdges.sort([](const Edge &e1, const Edge &e2)
                               { return e1.getTo() < e2.getTo(); });
        }
        for (const Edge &edge : toStringEdges)
            graphStr += edge.toString(weightPrecision) + delim;
        graphStr += "\n";
    }
    return graphStr;
}

// Return the indegree of a vertex
int DiGraph::indegree(int v) const { return vertices[idToIndex.at(v)].getOutDeg(); }

// Return the outdegree of a vertex
int DiGraph::outdegree(int v) const
{
    int outdeg = 0;
    for (Node node : vertices)
    {
        if (node.hasEdgeTo(v))
            outdeg++;
    }
    return outdeg;
}

/*!
 * @function adj
 * @abstract Iterates inorder over all the neighbors of v connected by
 *           an outgoing link from v
 * @param v The query vertex
 * @return  The outgoing map in adjacency tree of v
 */
const std::forward_list<Edge> &DiGraph::adj(int v) const { return vertices[idToIndex.at(v)].edges(); }

/**
 * Mutators
 */

/*!
 * @function insertVertex
 * @abstract Insert a vertex with key v
 * @param v Key of the new vertex
 */
void DiGraph::insertVertex(int v)
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
void DiGraph::insertEdge(int from, int to, double weight)
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
void DiGraph::eraseVertex(int v)
{
    if (idToIndex.find(v) == idToIndex.end())
        throw std::out_of_range("Vertex removal error: vertex " + std::to_string(v) + " is not in graph");

    // Erase all edges to v from other vertices
    int vIdx = idToIndex.at(v);
    for (Node &other : vertices)
    {
        // Skip if it's v itself
        if (other.getId() == v)
            continue;
        // Erase only if there is such an edge
        if (!other.hasEdgeTo(v))
            continue;
        other.eraseEdgeTo(v);
        edgeCount--;
    }

    // Erase v itself
    edgeCount -= vertices[vIdx].getOutDeg();
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
 * @abstract Remove the edge from v to w if the edge exists. If the
 *           directed edge does not exist, out_of_range exception will
 *           be thrown.
 * @param from The starting vertex
 * @param to The destination vertex
 */
void DiGraph::eraseEdge(int from, int to)
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
void DiGraph::insertVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        insertVertex(v);
}

void DiGraph::insertEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        insertEdge(edge.first, edge.second);
}
void DiGraph::eraseVertex(std::initializer_list<int> vertices)
{
    for (int v : vertices)
        eraseVertex(v);
}

void DiGraph::eraseEdge(std::initializer_list<std::pair<int, int>> edges)
{
    for (std::pair<int, int> edge : edges)
        eraseEdge(edge.first, edge.second);
}
