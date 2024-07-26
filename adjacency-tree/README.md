# Adjacency tree

Adjacency tree `AdjTree` contains two instantiated containers implemented using a left-learning red-black tree. The first container is a `Map<int, int>` that stores the neighbor pointed by the current vertex, and the second is a `Set<int>` that stores the neighbor pointing tothe current vertex.

`AdjTree` uses integer-valued keys to represent the neighbors of a given node. This allows `Digraph` to support $\Theta(lgN)$ vertex access during graph traversal and maintain graph integrity in near-logarithmic time in the case of vertex removal. See [implementation](../digraph/README.md) of `Digraph` for complete runtime and space usage analysis.

## Left-learning Red-Black Tree

Binary search tree symbol that supports logarithmic time insertion, search, and removal. See [my previous project](https://github.com/XYLiu9357/left-leaning-red-black-tree) for complete documentation.
