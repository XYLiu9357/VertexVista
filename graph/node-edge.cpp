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
 * Edges
 */
Node::Node(int id) : id(id), edgeList(std::forward_list<Edge>()), outDegree(0) {}
Node::Node(const Node &other) : id(other.id), edgeList(std::forward_list<Edge>(other.edgeList)), outDegree(other.outDegree) {}
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
    for (auto it = edgeList.begin(); it != edgeList.end(); ++it)
        if (std::next(it)->getTo() == to)
            it->setWeight(weight);
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
    for (auto it = edgeList.begin(); it != edgeList.end(); ++it)
        if (std::next(it) != edgeList.end() && std::next(it)->getTo() == to)
            edgeList.erase_after(it);
}

const std::forward_list<Edge> &Node::edges() const { return edgeList; }
