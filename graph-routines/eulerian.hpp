/**eulerian.hpp
 *
 * An Eulerian path for a directed graph is a directed path that use
 * every edge exactly once. An Eulerian circuit is an Eulerian path
 * that starts and ends at the same vertex.
 *
 * This routine tests for the existence of Eulerian path and Eulerian
 * cycle in a directed graph and returns such a path as an iterable
 * data type.
 *
 * For undirected graph, each edge is treated as bidirectional edges
 * in a directed graph setting.
 */

#include <vector>
#include "graph/digraph.hpp"

class Eulerian
{
private:
    std::vector<int> path;
    bool hasCycle;

public:
    /*!
     * @function Eulerian
     * @abstract Construct Eulerian-type object based on an
     * undirected graph.
     * @param target undirected graph used as input
     */
    Eulerian(const DiGraph &target);

    /*!
     * @function Eulerian
     * @abstract Copy constructor for Eulerian-type object.
     * @param other another Eulerian-type object
     */
    Eulerian(const Eulerian &other);

    /*!
     * @function operator=
     * @abstract Copy-assignment operator for Eulerian-type object.
     * @param other another Eulerian-type object
     */
    Eulerian &operator=(const Eulerian &other);

    /*!
     * @function getPath
     * @abstract Retrieves the Eulerian path found. If there is no
     *           Eulerian path, then an empty path will be returned.
     *           If there is an Eulerian cycle, then the path returned
     *           will be the Eulerican cycle.
     * @return std::vector<int> with entried being the vertices of the
     *         Eulerian path from start to end
     */
    std::vector<int> getPath();

    /*!
     * @function hasEulerianPath
     * @abstract Checks whether the directed graph has an Eulerian path
     * @return true if there is an Eulerian path, false otherwise
     */
    bool hasEulerianPath();

    /*!
     * @function hasEulerianCycle
     * @abstract Checks whether the directed graph has an Eulerian cycle
     * @return true if there is an Eulerian cycle, false otherwise
     */
    bool hasEulerianCycle();
};