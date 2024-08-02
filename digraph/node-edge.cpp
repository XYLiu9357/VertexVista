/**node-edge.cpp
 *
 * Nodes and edges used in the graph data structure.
 */

#include "node-edge.hpp"

/**
 * Edges
 */

// Constructors
Edge::Edge(int from, int to, int weight)
    : from(from), to(to), weight(weight) {}
Edge::Edge(const Edge &other)
    : from(other.from), to(other.to), weight(other.weight) {}

// Assign copy
Edge Edge::operator=(const Edge &other) { return Edge(other); }

// Utilities
int Edge::getFrom() { return from; }
int Edge::getTo() { return to; }
double Edge::getWeight() { return weight; }
std::string Edge::toString() { return std::to_string(from) + " -> " + std::to_string(to) + "[" + std::to_string(weight) + "]"; }

/**
 * Edges
 */
Node::Node(int id) : id(id), edgeList(std::forward_list<Edge>()) {}
void Node::insert(int from, int to, int weight) { edgeList.emplace_front(Edge(from, to, weight)); }
void Node::insert(Edge edge) { edgeList.emplace_front(edge); }
void Node::insertEdges(std::initializer_list<Edge> edges)
{
    for (Edge edge : edges)
        insert(edge);
}
const std::forward_list<Edge> &Node::edgesAt() { return edgeList; }
