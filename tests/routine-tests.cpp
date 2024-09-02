/**routine-tests.cpp
 *
 * Unit tests for directed graph routines.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <set>

#include "graph/digraph.hpp"
#include "graph-routines/bipartite.hpp"
#include "graph-routines/connected-component.hpp"

/**
 * Bipartite
 */
class BipartiteTest : public ::testing::Test
{
protected:
    DiGraph smallGraph;
    DiGraph largeGraph;

    void SetUp() override
    {
        // Both are bipartite
        smallGraph = DiGraph(12);
        largeGraph = DiGraph(50);

        // Set up graphs
        for (int i = 0; i <= 3; i++)
            smallGraph.insertEdge({{i, 4 + i}, {4 + i, 8 + i}}); // Fully connected network

        for (int i = 1; i < 50; i++)
            largeGraph.insertEdge(i - 1, i); // 50-node cycle
        largeGraph.insertEdge(49, 0);
    }
};

TEST_F(BipartiteTest, EmptyGraph)
{
    DiGraph g;
    Bipartite b(g);
    EXPECT_TRUE(b.isBipartite());
    EXPECT_THROW(b.getPart1(), std::out_of_range);
    EXPECT_THROW(b.getPart2(), std::out_of_range);
    EXPECT_THROW(b.sameSet(0, 1), std::out_of_range);
}

TEST_F(BipartiteTest, SmallGraphQuery)
{
    Bipartite b(smallGraph);
    EXPECT_TRUE(b.isBipartite());

    std::set<int> part1 = {0, 1, 2, 3, 8, 9, 10, 11};
    std::set<int> part2 = {4, 5, 6, 7};

    // Check partition
    if (b.getPart1() == part1)
    {
        EXPECT_EQ(b.getPart1(), part1);
        EXPECT_EQ(b.getPart2(), part2);
    }
    else
    {
        EXPECT_EQ(b.getPart1(), part2);
        EXPECT_EQ(b.getPart2(), part1);
    }

    // Check same set query
    EXPECT_TRUE(b.sameSet(0, 1));
    EXPECT_TRUE(b.sameSet(1, 3));
    EXPECT_TRUE(b.sameSet(4, 7));
    EXPECT_TRUE(b.sameSet(9, 11));
    EXPECT_TRUE(!b.sameSet(0, 6));
    EXPECT_TRUE(!b.sameSet(5, 8));
    EXPECT_TRUE(b.sameSet(0, 8));
    EXPECT_TRUE(b.sameSet(2, 11));
}

TEST_F(BipartiteTest, LargeGraphQuery)
{
    Bipartite b(largeGraph);
    EXPECT_TRUE(b.isBipartite());

    std::set<int> part1;
    std::set<int> part2;
    for (int i = 0; i < 50; i++)
    {
        if (i % 2 == 0)
            part1.insert(i);
        else
            part2.insert(i);
    }

    // Check partition
    if (b.getPart1() == part1)
    {
        EXPECT_EQ(b.getPart1(), part1);
        EXPECT_EQ(b.getPart2(), part2);
    }
    else
    {
        EXPECT_EQ(b.getPart1(), part2);
        EXPECT_EQ(b.getPart2(), part1);
    }

    // Check same set query
    EXPECT_TRUE(!b.sameSet(0, 1));
    EXPECT_TRUE(b.sameSet(0, 2));
    EXPECT_TRUE(b.sameSet(48, 18));
    EXPECT_TRUE(b.sameSet(9, 33));
    EXPECT_TRUE(b.sameSet(0, 6));
    EXPECT_TRUE(b.sameSet(26, 8));
}

TEST_F(BipartiteTest, CheckImmutable)
{
    Bipartite b(smallGraph);
    ASSERT_TRUE(b.isBipartite());
    smallGraph.insertEdge(3, 11);
    ASSERT_TRUE(b.isBipartite());

    b = Bipartite(smallGraph);
    ASSERT_TRUE(!b.isBipartite());
}

TEST_F(BipartiteTest, StressTestUndirectedGraph)
{
    int numVertices = 4000;
    Graph g(numVertices);

    // First Component: Connect even-indexed vertices to odd-indexed vertices
    for (int i = 0; i < numVertices / 2; i += 2)
        for (int j = i + 1; j < numVertices / 2; j += 2)
            g.insertEdge(i, j);

    // Second Component: Connect the remaining vertices similarly
    for (int i = numVertices / 2; i < numVertices; i += 2)
        for (int j = i + 1; j < numVertices; j += 2)
            g.insertEdge(i, j);

    Bipartite b(g);
    ASSERT_TRUE(b.isBipartite());
}

/**
 * Connected Component
 */

TEST(ConnectedComponentTest, EmptyGraph)
{
    Graph g;
    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 0);
    EXPECT_THROW(cc.id(0), std::out_of_range);
    EXPECT_THROW(cc.id(-1), std::out_of_range);
    EXPECT_THROW(cc.isConnected(0, 1), std::out_of_range);
    EXPECT_THROW(cc.isConnected(0, 0), std::out_of_range);
}

TEST(ConnectedComponentTest, SmallAcyclicGraph)
{
    Graph g(5);
    g.insertEdge({{0, 1}, {0, 2}, {3, 4}});

    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 2);

    EXPECT_EQ(cc.id(0), 0);
    EXPECT_EQ(cc.id(1), 0);
    EXPECT_EQ(cc.id(2), 0);
    EXPECT_EQ(cc.id(3), 1);
    EXPECT_EQ(cc.id(4), 1);
    EXPECT_THROW(cc.id(-1), std::out_of_range);
    EXPECT_THROW(cc.id(5), std::out_of_range);

    EXPECT_TRUE(cc.isConnected(0, 1));
    EXPECT_TRUE(cc.isConnected(0, 2));
    EXPECT_TRUE(cc.isConnected(1, 2));
    EXPECT_TRUE(!cc.isConnected(0, 3));
    EXPECT_TRUE(!cc.isConnected(2, 3));
    EXPECT_TRUE(cc.isConnected(3, 4));
    EXPECT_TRUE(cc.isConnected(0, 0)); // Check connectivity with self
    EXPECT_TRUE(cc.isConnected(3, 3)); // Check connectivity with self
    EXPECT_THROW(cc.isConnected(-1, 4), std::out_of_range);
    EXPECT_THROW(cc.isConnected(3, 5), std::out_of_range);
}

TEST(ConnectedComponentTest, NegativeVertices)
{
    Graph g = {0, -1, -2, -3, -4};
    g.insertEdge({{0, -1}, {0, -2}, {-3, -4}});

    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 2);

    EXPECT_EQ(cc.id(0), 0);
    EXPECT_EQ(cc.id(-1), 0);
    EXPECT_EQ(cc.id(-2), 0);
    EXPECT_EQ(cc.id(-3), 1);
    EXPECT_EQ(cc.id(-4), 1);
    EXPECT_THROW(cc.id(1), std::out_of_range);
    EXPECT_THROW(cc.id(5), std::out_of_range);

    EXPECT_TRUE(cc.isConnected(0, -1));
    EXPECT_TRUE(cc.isConnected(0, -2));
    EXPECT_TRUE(cc.isConnected(-1, -2));
    EXPECT_TRUE(!cc.isConnected(0, -3));
    EXPECT_TRUE(!cc.isConnected(-2, -3));
    EXPECT_TRUE(cc.isConnected(-3, -4));
    EXPECT_TRUE(cc.isConnected(0, 0));   // Check connectivity with self
    EXPECT_TRUE(cc.isConnected(-3, -3)); // Check connectivity with self
    EXPECT_THROW(cc.isConnected(-1, 1), std::out_of_range);
    EXPECT_THROW(cc.isConnected(-3, -5), std::out_of_range);
}

TEST(ConnectedComponentTest, SmallCyclicGraph)
{
    Graph g(5);
    g.insertEdge({{0, 1}, {0, 2}, {1, 2}, {3, 2}, {4, 0}});
    EXPECT_EQ(g.degree(0), 3);
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.E(), 5);

    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 1);

    EXPECT_EQ(cc.id(0), 0);
    EXPECT_EQ(cc.id(4), 0);
    EXPECT_THROW(cc.id(-1), std::out_of_range);
    EXPECT_THROW(cc.id(5), std::out_of_range);

    EXPECT_TRUE(cc.isConnected(0, 2));
    EXPECT_TRUE(cc.isConnected(0, 3));
    EXPECT_TRUE(cc.isConnected(2, 4));
    EXPECT_TRUE(cc.isConnected(3, 4));
    EXPECT_THROW(cc.isConnected(0, 10), std::out_of_range);
    EXPECT_THROW(cc.isConnected(3, 5), std::out_of_range);
}

TEST(ConnectedComponentTest, LargeCyclicGraph)
{
    int n = 50;
    Graph g(n);
    for (int i = 0; i < n; i++)
        g.insertEdge(i, (i - 2 + n) % n);

    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 2);

    EXPECT_EQ(cc.id(0), 0);
    EXPECT_EQ(cc.id(1), 1);
    EXPECT_EQ(cc.id(3), 1);
    EXPECT_EQ(cc.id(4), 0);
    EXPECT_EQ(cc.id(24), 0);
    EXPECT_EQ(cc.id(48), 0);
    EXPECT_EQ(cc.id(49), 1);

    EXPECT_THROW(cc.id(50), std::out_of_range);
    EXPECT_THROW(cc.id(-1), std::out_of_range);

    EXPECT_TRUE(cc.isConnected(0, 2));
    EXPECT_TRUE(cc.isConnected(6, 14));
    EXPECT_TRUE(cc.isConnected(38, 42));
    EXPECT_TRUE(cc.isConnected(19, 3));

    EXPECT_TRUE(!cc.isConnected(0, 43));
    EXPECT_TRUE(!cc.isConnected(14, 15));
    EXPECT_TRUE(!cc.isConnected(33, 34));
    EXPECT_TRUE(!cc.isConnected(48, 49));
    EXPECT_TRUE(!cc.isConnected(49, 0));

    EXPECT_TRUE(cc.isConnected(0, 0)); // Check connectivity with self
    EXPECT_THROW(cc.isConnected(0, 50), std::out_of_range);
    EXPECT_THROW(cc.isConnected(1, 50), std::out_of_range);
}

TEST(ConnectedComponentTest, FullyDisconnected)
{
    Graph g(20);
    ASSERT_EQ(g.V(), 20);
    ASSERT_EQ(g.E(), 0);

    ConnectedComponent cc(g);
    EXPECT_EQ(cc.count(), 20);
    EXPECT_EQ(cc.id(2), 2);
    EXPECT_EQ(cc.id(18), 18);
    EXPECT_THROW(cc.id(20), std::out_of_range);

    EXPECT_TRUE(!cc.isConnected(0, 1));
    EXPECT_TRUE(!cc.isConnected(1, 2));
    EXPECT_TRUE(!cc.isConnected(2, 3));
    EXPECT_TRUE(!cc.isConnected(2, 16));
    EXPECT_THROW(cc.isConnected(5, 20), std::out_of_range);
    EXPECT_THROW(cc.isConnected(0, 20), std::out_of_range);
    EXPECT_THROW(cc.isConnected(-1, 5), std::out_of_range);
    EXPECT_THROW(cc.isConnected(-1, 20), std::out_of_range);
}

TEST(ConnectedComponentTest, CheckImmutable)
{
    Graph g(5);
    g.insertEdge({{0, 1}, {0, 2}, {3, 4}});

    ConnectedComponent cc(g);
    ASSERT_EQ(cc.count(), 2);

    g.insertEdge(2, 3);
    EXPECT_EQ(cc.count(), 2);
    EXPECT_TRUE(cc.isConnected(0, 2));
    EXPECT_TRUE(cc.isConnected(4, 3));
    EXPECT_TRUE(!cc.isConnected(0, 3));

    cc = ConnectedComponent(g);
    EXPECT_EQ(cc.count(), 1);
    EXPECT_TRUE(cc.isConnected(0, 2));
    EXPECT_TRUE(cc.isConnected(3, 4));
    EXPECT_TRUE(cc.isConnected(0, 3));
}

TEST(ConnectedComponentTest, StressTest)
{
    // Create graph
    int graphSize = 10000;
    Graph graph(graphSize);

    for (int i = 0; i < graphSize / 2; ++i)
        graph.insertEdge(i, (i + 1) % (graphSize / 2)); // Component 1 (simple cycle)
    for (int i = graphSize / 2; i < graphSize - 5; ++i)
        graph.insertEdge(i, i + 1); // Component 2 (line graph)
    // We still have 4 isolated nodes left -> total of 6

    ConnectedComponent cc(graph);
    ASSERT_EQ(cc.count(), 6);

    // All in the first component
    for (int i = 0; i < graphSize / 2; ++i)
        EXPECT_EQ(cc.id(i), cc.id(0));

    // All in the second component
    for (int i = graphSize / 2; i < graphSize - 4; ++i)
        EXPECT_EQ(cc.id(i), cc.id(graphSize / 2));

    // Isolated nodes, different components
    for (int i = graphSize - 4; i < graphSize; ++i)
    {
        EXPECT_NE(cc.id(i), cc.id(0));
        EXPECT_NE(cc.id(i), cc.id(graphSize / 2));
    }

    // Check connectivity queries
    EXPECT_TRUE(cc.isConnected(0, graphSize / 2 - 1));
    EXPECT_TRUE(cc.isConnected(graphSize / 2, graphSize - 5));
    EXPECT_TRUE(!cc.isConnected(0, graphSize / 2));

    // Check for isolated nodes
    for (int i = graphSize - 4; i < graphSize; ++i)
        for (int j = 0; j < graphSize - 4; ++j)
            EXPECT_TRUE(!cc.isConnected(i, j));
}
