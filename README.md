<p align="center"><a href="https://github.com/XYLiu9357/VertexVista" target="_blank"><img src="./icons/logo-no-background.svg" width="400" alt="VertexVista Logo"></a></p>

## Overview

VertexVista is a C++ library for the manipulation and analysis of the structure of weighted directed graphs and networks. The library is designed with elegance, performance, and flexibility in mind, while achieving memory and runtime optimality for read, write, and various query operations.

Technical documentations can be found here:

- **Graph**: the skeleton of VertexVista - [Graph](docs/Graph.rst)
- **Routines**: graph analysis and processing routines - [GraphRoutines](docs/GraphRoutines.rst)
- **Performance Analysis**: performance analysis for a subset of graph routines - [Performance](docs/Performance.rst)

VertexVista currently offers a C++ interface with expressive syntax and customizable features. A Python interface with the same structure and style will be developed in the near future.

## About VertexVista

VertexVista provides a comprehensive set of features for working with weighted directed graphs, including support for various graph algorithms and efficient data structures. Still, why reinvent the wheel when there are existing efficient and robust solutions such as the [Boost Graph Library](https://www.boost.org/doc/libs/1_75_0/libs/graph/doc/index.html)?

Indeed, BGL is a fantastic library built by absolute C++ virtuosos. It's versatile and is well-known for its compatibility and robust performance. Yet this comes at a cost: BGL has a steep learning curve and is somewhat bulky. For many use cases, support for ancient or eccentric compilers is unnecessary. Developers have expressed the need for a light-weight alternative for their projects. VertexVista is a performant, light-weight alternative solution that can easily be tailored to your own projects.

## Dependencies & Installation

## Simple Example

Create a directed graph and determine if there exists an [Eulerian path](https://en.wikipedia.org/wiki/Eulerian_path): a path that visits every edge exactly once.

```cpp
#include <iostream>
#include <VertexVista/graph/graph.hpp>
#include <VertexVista/routines/eulerian.hpp>

int main()
{
    // Create a graph
    Graph g = Graph(4);
    g.insertEdges({{0, 1}, {1, 2}, {2, 3}, {3, 0}});

    // Eulerian path query
    Eulerian eu = Eulerian(g);
    if (eu.hasEulerianPath())
        std::cout << "Has Eu-path" << std::endl;
    else
        std::cout << "No Eu-path" << std::endl;

    return 0;
}

/**Output:
 * $ ./a.out
 * Has Eu-path
 */
```

## Reporting Bugs

Our team will be tracking bugs, issues, and other relevant feedback through [GitHub Issues](https://github.com/XYLiu9357/VertexVista/issues). If you encountered trouble using VertexVista or thought of anything that could help us improve, please don't hesitate to post an Issue.

## Call for Contributions

We welcome all changes and suggestions, big or small. If you want to contribute to VertexVista, feel free to fork the repository on GitHub and create a pull request (PR). We want to make VertexVista the #1 choice for light-weight graph analysis library, and we would love to meet people with the same interest and passion!
