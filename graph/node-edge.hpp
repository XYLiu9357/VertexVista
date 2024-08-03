/**node-edge.hpp
 *
 * Nodes and edges used in the graph data structure.
 */

#ifndef EDGE
#define EDGE

#include <initializer_list>
#include <forward_list>
#include <string>

class Edge
{
private:
    int from;
    int to;
    double weight;

public:
    // Constructors
    Edge(int from, int to, double weight);
    Edge(const Edge &other);

    // Assign copy
    Edge operator=(const Edge &other);

    // Utilities
    int getFrom() const;
    int getTo() const;
    double getWeight() const;
    void setWeight(double weight);
    std::string toString(int precision) const;
};

#endif /*EDGE*/

#ifndef NODE
#define NODE

class Node
{
private:
    int id;
    int outDegree;
    std::forward_list<Edge> edgeList;

public:
    Node(int id);
    Node(const Node &other);
    Node(Node &&other);
    Node &operator=(const Node &other);
    Node &operator=(Node &&other);

    // Accessors
    int getId() const;
    int getOutDeg() const;
    bool hasEdgeTo(int v) const;

    // Mutators
    void setWeight(int to, double weight);
    void insertEdge(int to, double weight);
    void insertEdge(Edge edge);
    void insertEdges(std::initializer_list<Edge> edges);
    void eraseEdgeTo(int to);
    const std::forward_list<Edge> &edges() const;
};

#endif /*NODE*/