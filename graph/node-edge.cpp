/**node-edge.cpp
 *
 * Nodes and edges used in the graph data structure.
 */

#include <stdexcept>
#include "node-edge.hpp"

/**
 * Edges
 */

// Constructors
Edge::Edge(int from, int to, double weight)
    : from(from), to(to), weight(weight) {}
Edge::Edge(const Edge &other)
    : from(other.from), to(other.to), weight(other.weight) {}

// Assign copy
Edge Edge::operator=(const Edge &other) { return Edge(other); }

// Utilities
bool Edge::operator==(const Edge &other) const { return this->from == other.from && this->to == other.to && this->weight == other.weight; }
int Edge::getFrom() const { return from; }
int Edge::getTo() const { return to; }
double Edge::getWeight() const { return weight; }
void Edge::setWeight(double weight) { this->weight = weight; }
std::string Edge::toString(int precision) const
{
    std::string weightStr = std::to_string(weight);
    weightStr = weightStr.substr(0, weightStr.find(".") + precision + 1);
    return std::to_string(from) + " -> " + std::to_string(to) + "[" + weightStr + "]";
}

/**
 * Nodes
 */
Node::Node(int id) : id(id), edgeList(std::forward_list<Edge>()), outDegree(0) {}
Node::Node(const Node &other) : id(other.id), edgeList(std::forward_list<Edge>(other.edgeList)), outDegree(other.outDegree) {}
Node::Node(Node &&other) : id(other.id), outDegree(other.outDegree), edgeList(std::move(other.edgeList)) {}

Node &Node::operator=(const Node &other)
{
    if (this != &other)
    {
        id = other.id;
        outDegree = other.outDegree;
        edgeList = other.edgeList;
    }
    return *this;
}

Node &Node::operator=(Node &&other)
{
    if (this != &other)
    {
        id = other.id;
        outDegree = other.outDegree;
        edgeList = std::move(other.edgeList);
    }
    return *this;
}

bool Node::operator==(const Node &other) const { return this->id == other.id && this->edgeList == other.edgeList; }

int Node::getId() const { return id; }
int Node::getOutDeg() const { return outDegree; }

bool Node::hasEdgeTo(int v) const
{
    for (Edge edge : edgeList)
        if (edge.getTo() == v)
            return true;
    return false;
}

void Node::setWeight(int to, double weight)
{
    auto it = edgeList.begin();
    for (; it != edgeList.end(); ++it)
    {
        if (it->getTo() == to)
        {
            it->setWeight(weight);
            return;
        }
    }
}

void Node::insertEdge(int to, double weight)
{
    edgeList.emplace_front(Edge(id, to, weight));
    outDegree++;
}

void Node::insertEdge(Edge edge)
{
    if (edge.getFrom() != id)
        throw std::logic_error("Edge to insert does not match current vertex");
    edgeList.emplace_front(edge);
    outDegree++;
}

void Node::insertEdges(std::initializer_list<Edge> edges)
{
    for (Edge edge : edges)
        insertEdge(edge);
    outDegree += edges.size();
}

void Node::eraseEdgeTo(int to)
{
    auto prev = edgeList.before_begin();
    auto it = edgeList.begin();
    for (; it != edgeList.end(); ++prev, ++it)
    {
        // Erase first match
        if (it->getTo() == to)
        {
            edgeList.erase_after(prev);
            outDegree--;
            return;
        }
    }
}

const std::forward_list<Edge> &Node::edges() const { return edgeList; }

/**
 * Hashing
 */

// Cantor pairing function uniquely maps two natural numbers to one
// This is used for hashing edges
int cantorPair(int k1, int k2)
{
    return (k1 + k2) * (k1 + k2 + 1) / 2 + k2;
}

namespace std
{
    std::size_t hash<Edge>::operator()(const Edge &edge) const
    {
        // Use integer hash on node id
        int key = cantorPair(edge.getFrom(), edge.getTo());
        return std::hash<int>()(key);
    }
    std::size_t hash<Node>::operator()(const Node &node) const
    {
        // Use integer hash on node id
        return std::hash<int>()(node.getId());
    }
}