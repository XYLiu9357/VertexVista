<p align="center"><a href="https://github.com/XYLiu9357/VertexVista" target="_blank"><img src="./icons/logo-no-background.svg" width="400" alt="VertexVista Logo"></a></p>

## Overview

VertexVista is a C++ library for the manipulation and analysis of the structure of weighted directed graphs and networks. The library achieves memory and runtime optimality for read, write, and various query operations.

Technical documentations can be found here:

- **Graph**: the skeleton of VertexVista - [Graph](docs/Graph.md)
- **Routines**: graph analysis and processing routines - [GraphRoutines](docs/GraphRoutines.md)

\*Development is ongoing...

## About VertexVista

VertexVista provides a comprehensive set of features for working with weighted directed graphs, including support for graph algorithms and efficient data structures. Still, why reinvent the wheel when there are existing efficient and robust solutions such as the [Boost Graph Library](https://www.boost.org/doc/libs/1_75_0/libs/graph/doc/index.html)?

Indeed, BGL is a fantastic library built by absolute C++ virtuosos. It's versatile and is well-known for its compatibility and robust performance. Yet this comes at a cost: BGL has a steep learning curve and is somewhat bulky. For many use cases, support for ancient or older compilers is unnecessary. Developers have expressed the need for a light-weight alternative for their projects. VertexVista is a performant, flexible alternative solution that can easily be tailored to our own projects.

## Dependencies & Installation

## Example

Create a undirected graph and determine if it is [Bipartite](https://en.wikipedia.org/wiki/Bipartite_graph).

```cpp
#include <iostream>
#include <VertexVista/graph/graph.hpp>
#include <VertexVista/routines/bipartite.hpp>

int main()
{
    // Fully connected network
    Graph smallGraph = Graph(12);
    for (int i = 0; i <= 3; i++)
        smallGraph.insertEdge({{i, 4 + i}, {4 + i, 8 + i}});

    Bipartite b(smallGraph);
    if (b.isBipartite())
        std::cout << "Graph is bipartite." << std::endl;

    // Print partition
    std::cout << "Part 1: ";
    if (int v : b.getPart1())
        std::cout << v << ", ";
    std::cout << endl;

    std::cout << "Part 2: ";
    if (int v : b.getPart2())
        std::cout << v << ", ";
    std::cout << endl;

    return 0;
}

/**
 * Graph is bipartite.
 * Part 1: 0, 1, 2, 3, 8, 9, 10, 11
 * Part 2: 4, 5, 6, 7
 */
```

## Reporting Bugs

Our team will be tracking bugs, issues, and other relevant feedback through [GitHub Issues](https://github.com/XYLiu9357/VertexVista/issues). If you encountered trouble using VertexVista or thought of anything that could help us improve, please don't hesitate to post an Issue.

## Call for Contributions

We welcome all changes and suggestions, big or small. If you want to contribute to VertexVista, feel free to fork the repository on GitHub and create a pull request (PR).

## Licensing

[MIT license](LICENSE.txt)
