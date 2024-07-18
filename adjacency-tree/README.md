# Adjacency tree

Adjacency tree `AdjTree` is an instantiated _left-learning red-black tree_ symbol table. It will be used to support flexible insertion and removal of vertices with a `Digraph`.

`AdjTree` uses integer-valued keys and `TreeNode*` values to represent the neighbors of a given node. This allows `Digraph` to support $\Theta(1)$ vertex access during graph traversal and maintain graph integrity in near-linear time in the case of vertex removal. See [implementation](../digraph/README.md) of `Digraph` for complete runtime and space usage analysis.

## Left-learning Red-Black Tree

Binary search tree symbol that supports logarithmic time insertion, search, and removal. See [my previous project](https://github.com/XYLiu9357/left-leaning-red-black-tree) for complete documentation.
