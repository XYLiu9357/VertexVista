/**node-edge.hpp
 *
 * Nodes and edges used in the graph data structure.
 */

#include <initializer_list>
#include <forward_list>
#include <string>

class Edge
{
private:
    int from;
    int to;
    int weight;

public:
    // Constructors
    Edge(int from, int to, int weight);
    Edge(const Edge &other);

    // Assign copy
    Edge operator=(const Edge &other);

    // Utilities
    int getFrom();
    int getTo();
    double getWeight();
    std::string toString();
};

class Node
{
private:
    int id;
    std::forward_list<Edge> edgeList;

public:
    Node(int id);
    void insert(int from, int to, int weight);
    void insert(Edge edge);
    void insertEdges(std::initializer_list<Edge> edges);
    const std::forward_list<Edge> &edgesAt();
};