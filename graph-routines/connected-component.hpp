/**connected-component.hpp
 *
 * Finds all the maximal sets of connected vertices in an undirected graph
 * and answer queries about these sets.
 */

#include <unordered_map>
#include <unordered_set>
#include "graph/graph.hpp"

class ConnectedComponent
{
private:
    Graph g;
    std::unordered_map<int, int> idMap;
    int _count;

    // Process the graph g and find all connected components
    void dfsCC();

public:
    /*!
     * @function ConnectedComponent
     * @abstract Construct ConnectedComponent-type object
     * based on an undirected graph.
     * @param target undirected graph used as input
     */
    ConnectedComponent(const Graph &target);

    /*!
     * @function ConnectedComponent
     * @abstract Copy constructor for ConnectedComponent-type object.
     * @param other another ConnectedComponent-type object
     */
    ConnectedComponent(const ConnectedComponent &other);

    /*!
     * @function operator=
     * @abstract Copy-assignment operator for ConnectedComponent-type object.
     * @param other another ConnectedComponent-type object
     * @exception throws std::out_of_range if graph is empty
     */
    ConnectedComponent &operator=(const ConnectedComponent &other);

    /*!
     *@function count
     *@abstract Return the number of connected components
     *@return the number of connected components
     */
    int count();

    /*!
     * @function id
     * @abstract Return the connected component id of the queried vertex. Each
     *          connected component has a unique id. This means id[v] == id[w]
     *          implies v and w are in the same connected component.
     * @param v the queried vertex id
     * @return the number of connected components
     * @exception throws std::out_of_range if v is not in the graph
     */
    int id(int v);

    /*!
     * @function isConnected
     * @abstract Indicates if two vertices are connected, i.e. in the same connected
     *           component. This function has the same effect as id[v] == id[w].
     * @param v the first queried vertex
     * @param w the second queried vertex
     * @return true if both vertices are in the same connected component, false otherwise
     * @exception throws std::out_of_range if v or w is not in the graph
     */
    bool isConnected(int v, int w);
};
