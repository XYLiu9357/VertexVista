/**connected-component.hpp
 *
 * Finds all the maximal sets of connected vertices in an undirected graph
 * and answer queries about these sets.
 */

#include <stdexcept>
#include "connected-component.hpp"

// Process the graph g and find all connected components
void dfsCC() {}

/*!
 * @function ConnectedComponent
 * @abstract Construct ConnectedComponent-type object
 * based on an undirected graph.
 * @param target undirected graph used as input
 */
ConnectedComponent::ConnectedComponent(const Graph &target) {}

/*!
 * @function ConnectedComponent
 * @abstract Copy constructor for ConnectedComponent-type object.
 * @param other another ConnectedComponent-type object
 */
ConnectedComponent::ConnectedComponent(const ConnectedComponent &other)
{
    this->g = DiGraph(other.g);
    this->idMap = std::unordered_map<int, int>(other.idMap);
    this->_count = other._count;
}

/*!
 * @function operator=
 * @abstract Copy-assignment operator for ConnectedComponent-type object.
 * @param other another ConnectedComponent-type object
 * @exception throws std::out_of_range if graph is empty
 */
ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &other)
{
    ConnectedComponent newCopy(other);
    std::swap(this->g, newCopy.g);
    std::swap(this->idMap, newCopy.idMap);
    std::swap(this->_count, newCopy._count);
    return *this;
}

/*!
 *@function count
 *@abstract Return the number of connected components
 *@return the number of connected components
 */
int ConnectedComponent::count() { return _count; }

/*!
 * @function id
 * @abstract Return the connected component id of the queried vertex. Each
 *          connected component has a unique id. This means id[v] == id[w]
 *          implies v and w are in the same connected component.
 * @param v the queried vertex id
 * @return the number of connected components
 * @exception throws std::out_of_range if v is not in the graph
 */
int ConnectedComponent::id(int v)
{
    if (!g.contains(v))
        throw std::out_of_range("Connected Component: vertex " + std::to_string(v) + " is not in graph");
    else
        return idMap.find(v)->second;
}

/*!
 * @function isConnected
 * @abstract Indicates if two vertices are connected, i.e. in the same connected
 *           component. This function has the same effect as id[v] == id[w].
 * @param v the first queried vertex
 * @param w the second queried vertex
 * @return true if both vertices are in the same connected component, false otherwise
 * @exception throws std::out_of_range if v or w is not in the graph
 */
bool ConnectedComponent::isConnected(int v, int w)
{
    if (!g.contains(v))
        throw std::out_of_range("Connected Component: vertex " + std::to_string(v) + " is not in graph");
    if (!g.contains(w))
        throw std::out_of_range("Connected Component: vertex " + std::to_string(w) + " is not in graph");

    return idMap.find(v)->second == idMap.find(w)->second;
}