# VertexVista Directed Graph

To support the dynamic insertion and removal of vertices and edges, VertexVista uses an unorthodox data structure to represent a directed graph: [adjacency tree](../adjacency-tree/README.md). This comes with benefits and drawbacks.

The `Digraph` class uses a nested symbol table `Map<int, AdjTree>` to store the vertices and edges in the directed graph. This provides support for dynamic insertion and deletion with reasonable runtime efficiency. This comes at the cost of doubled memory usage (quadrupled in the worst case).

## Runtime

Let $T$ be the runtime, $N$ be the total number of vertices present in `Digraph`, and $e_i$ be the number of directed edges from vertex $i: 1\leq i \leq N$.

- Insert new vertex $v$: $T \sim\lg N$
- Insert new directed edge from vertex $v$ to vertex $w$: $T \sim 2\lg N + \lg e_v + \lg e_w$
- Delete directed edge from $v$ to vertex $w$: $T \sim 2\lg N + \lg e_v + \lg e_w$
- Delete vertex $v$: $T \sim 4\lg N + \sum_{w\in S}[\lg N\lg e_w]$ where $S$ is the set of vertices that have an edge to $v$

Edge insertion and deletion takes $T \sim 2 \lg N$ in the worst case when every node is connected to one another and $T \sim \lg N$ for sparse graphs. Vertex deletion takes $T = O(N(\lg N)^2)$ time in the same worst case with a dense, fully-connected graph. However, the same process will take $T \sim 4\lg N$ for general sparse graphs.

## Space

Let $s_i$ be the size of an integer on the given system, the total memory use $M$ of `Digraph` with $N$ vertices such that each vertex $i$ has $e_i$ outgoing edges and $g_i$ incoming edges satisfies (assuming no overhead)

$$M = s_iN + s_i\sum^n_{i=1}[2e_i + g_i]$$

which is $\Theta(N)$ for sparse graphs and $O(N^2)$. From the analysis above, it is clear that the runtime and space usage of `Digraph` varies significantly with the "density" and connectivity of the graph constructed.

### Proof of Space Usage Expression

The derivation for memory usage is as follows. A `Digraph` object contains a `graphTree` that stores an integer key and an `AdjTree` object. Hence, each vertex $i$ has size

$$m_i = s_i + s(tree_i)$$

The size of the adjacency tree depends on the number of neighbors $i$ has. For each outgoing neighbor of $i$, i.e. $i$ has a directed edge pointing to that vertex, `AdjTree` stores both the key of the neighbor and the weight of the link, taking up $2s_i$ space for each neighbor. Then, for each incoming link, i.e. that vertex has a directed edge pointing to $i$, `AdjTree` only stores the neighbor's key,, taking up $s_i$ space. Hence, we have

$$m_i = s_i + 2e_is_i + g_is_i$$

If we sum over all $N$ vertices, we get the memory usage expression above.
