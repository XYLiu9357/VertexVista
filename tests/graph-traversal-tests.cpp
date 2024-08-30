/**graph-paths-tests.cpp
 *
 * Unit tests for directed graph path-finding data structure.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "graph/graph.hpp"
#include "graph-routines/traversal.hpp"

class GraphPathsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up some basic graphs for testing
        smallGraph.insertVertex({0, 1, 2, 3, 4, 5});
        smallGraph.insertEdge({{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}});

        cycleGraph.insertVertex({0, 1, 2, 3});
        cycleGraph.insertEdge({{0, 1}, {1, 2}, {2, 3}, {3, 0}});
    }

    Graph smallGraph;
    Graph cycleGraph;
};

TEST_F(GraphPathsTest, ConstructorDFS)
{
    GraphPaths dp(smallGraph, 0);
    EXPECT_EQ(dp.count(), 6);
    EXPECT_TRUE(dp.hasPathTo(5));
    EXPECT_FALSE(dp.hasPathTo(6));
}

TEST_F(GraphPathsTest, ConstructorBFS)
{
    GraphPaths dp(smallGraph, 0, false);
    EXPECT_EQ(dp.count(), 6);
    EXPECT_TRUE(dp.hasPathTo(5));
    EXPECT_FALSE(dp.hasPathTo(6));
}

TEST_F(GraphPathsTest, HasPathTo)
{
    GraphPaths dp(smallGraph, 0);
    EXPECT_TRUE(dp.hasPathTo(5));
    EXPECT_FALSE(dp.hasPathTo(6));
}

TEST_F(GraphPathsTest, PathTo)
{
    GraphPaths dp(smallGraph, 0);
    std::vector<int> path = dp.pathTo(5);
    std::vector<int> expectedPath = {0, 1, 2, 3, 4, 5};
    EXPECT_EQ(path, expectedPath);
}

TEST_F(GraphPathsTest, Count)
{
    GraphPaths dp(smallGraph, 0);
    EXPECT_EQ(dp.count(), 6);
}

TEST_F(GraphPathsTest, CycleDetectionDFS)
{
    GraphPaths dp(cycleGraph, 0, true);
    EXPECT_TRUE(dp.hasPathTo(3));
    std::vector<int> path = dp.pathTo(3);
    std::vector<int> expectedPath = {0, 1, 2, 3};
    EXPECT_EQ(path, expectedPath);
}

TEST_F(GraphPathsTest, CycleDetectionBFS)
{
    GraphPaths dp(cycleGraph, 0, false);
    EXPECT_TRUE(dp.hasPathTo(3));
    std::vector<int> path = dp.pathTo(3);
    std::vector<int> expectedPath = {0, 1, 2, 3};
    EXPECT_EQ(path, expectedPath);
}

TEST_F(GraphPathsTest, DisconnectedGraph)
{
    Graph disconnectedGraph;
    disconnectedGraph.insertVertex({0, 1, 2});
    disconnectedGraph.insertEdge({{0, 1}});

    GraphPaths dp(disconnectedGraph, 0);
    EXPECT_TRUE(dp.hasPathTo(1));
    EXPECT_FALSE(dp.hasPathTo(2));
}

TEST_F(GraphPathsTest, ComplexGraph)
{
    Graph complexGraph;
    complexGraph.insertVertex({0, 1, 2, 3, 4, 5});
    complexGraph.insertEdge({{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}});

    GraphPaths dp(complexGraph, 0);
    EXPECT_TRUE(dp.hasPathTo(5));
    std::vector<int> path = dp.pathTo(5);
    std::vector<int> expectedPath = {0, 2, 5};
    EXPECT_EQ(path, expectedPath);
}

TEST_F(GraphPathsTest, StressTestSimpleCyclic)
{
    Graph simpleCylicGraph;
    int numVertices = 100000;
    for (int i = 0; i < numVertices; ++i)
    {
        simpleCylicGraph.insertVertex(i);
        if (i > 0)
            simpleCylicGraph.insertEdge(i - 1, i);
    }

    GraphPaths dp(simpleCylicGraph, 0);
    EXPECT_TRUE(dp.hasPathTo(numVertices - 1));
    std::vector<int> path = dp.pathTo(numVertices - 1);
    EXPECT_EQ(path.size(), numVertices);
}

TEST_F(GraphPathsTest, StressTestComplexCyclic)
{
    Graph complexCyclicGraph;

    // Running with 100,000 vertices takes about 20 seconds in O3 mode
    int numVertices = 40000;
    for (int i = 0; i < numVertices; ++i)
    {
        complexCyclicGraph.insertVertex(i);

        // Bidirection
        complexCyclicGraph.insertEdge(i % 3, i);
        complexCyclicGraph.insertEdge(i, i % 3);

        // Mono-direction
        complexCyclicGraph.insertEdge(i % 5, i);
        complexCyclicGraph.insertEdge(i % 7, i);
    }

    GraphPaths dp1(complexCyclicGraph, 0);
    EXPECT_TRUE(dp1.hasPathTo(numVertices - 1));

    GraphPaths dp2(complexCyclicGraph, numVertices - 1);
    EXPECT_TRUE(dp2.hasPathTo(3));

    std::vector<int> path = dp1.pathTo(numVertices - 1);
    EXPECT_EQ(path.size(), 2);
}
