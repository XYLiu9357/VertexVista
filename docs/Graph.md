# Graph API Documentation

## Constructors

### `Graph()`

Creates an empty graph.

**Parameters**

None

**Return**

None

**Example**

```cpp
#include "graph.hpp"

int main() {
    Graph g;
    return 0;
}
```

---

### `Graph(int V)`

Creates a graph with vertices from 0 to V - 1.

**Parameters**

- `int V`: The number of vertices.

**Return**

None

**Example**

```cpp
#include "graph.hpp"

int main() {
    Graph g(5);
    return 0;
}
```

---

### `Graph(const Graph &other)`

Performs a deep copy of another graph.

**Parameters**

`const Graph&`: Reference to the graph to copy.

**Return**

None

**Example**

```cpp
#include "graph.hpp"

int main() {
    Graph g1({1, 2, 3, 4});
    Graph g2(g1);
    return 0;
}
```

## Accessors

### `size_t V() const`

Returns the number of vertices.

**Parameters**

None

**Return**

`size_t`: The number of vertices.

**Example**

```cpp
#include "graph.hpp"
#include <iostream>

int main() {
    Graph g({1, 2, 3, 4});
    std::cout << "Number of vertices: " << g.V() << std::endl;
    return 0;
}
```

---

### `size_t E() const`

Returns the number of edges.

**Parameters**

None

**Return**

`size_t`: The number of edges.

**Example**

```cpp
#include "graph.hpp"
#include <iostream>

int main() {
    Graph g;
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    std::cout << "Number of edges: " << g.E() << std::endl;
    return 0;
}
```

---

### `bool contains(int v) const`

Checks if the graph contains vertex `v`.

**Parameters**

`int v`: The vertex to check.

**Return**

`bool`: True if the graph contains vertex `v`, false otherwise.

---
