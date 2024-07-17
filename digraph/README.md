# Directed Graph

The `Digraph` class uses a nested symbol table `RedBlackTree<int, AdjTree>` to store the vertices and edges in the directed graph.

## Runtime

Let $T$ be the runtime, $N$ be the total number of vertices present in `Digraph`, and $e_i$ be the number of directed edges from vertex $i: 1\leq i \leq N$.

- Insert new vertex $v$: $T \sim\lg N$
- Insert new directed edge from vertex $v$ to vertex $w$: $T \sim 2\lg N + \lg e_v$
- Delete directed edge from $v$ to vertex $w$: $T \sim \lg N + \lg e_v$
- Delete vertex $v$: $T \sim N + \sum_{w\in S}\lg e_w$ where $S$ is the set of all vertices that have a directed edge to $v$

Edge insertion and deletion takes $T \sim 2 \lg N$ in the worst case when every node is connected to one another and $T \sim \lg N$ for sparse graphs. Vertex deletion takes $T = O(N\lg N)$ time in the same worst case and $T \sim N$ for sparse graphs.

## Space
