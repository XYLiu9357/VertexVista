/**cycle.hpp
 *
 * A cycle in a directed graph is a non-empty path in which only the
 * start and last vertices are the same. In particular, empty graphs
 * are not cyclic.
 *
 * This function checks if there exists a cycle in the directed graph.
 *
 * For undirected graph, each edge is treated as bidirectional edges
 * in a directed graph setting.
 */
#include "graph/digraph.hpp"

/*!
 *@function isCyclic
 * @abstract Checks whether the directed graph.
 * @param target the target DiGraph
 * @return True if the graph is cyclic, false otherwise.
 */
bool isCyclic(const DiGraph &target);