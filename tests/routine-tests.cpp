/**routine-tests.cpp
 *
 * Unit tests for directed graph routines.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <set>
#include "graph/digraph.hpp"
#include "graph-routines/bipartite.hpp"

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

    b = Bipartite(largeGraph);
    ASSERT_TRUE(b.isBipartite());
    smallGraph.insertEdge(3, 12);
    ASSERT_TRUE(b.isBipartite());
}

TEST_F(BipartiteTest, SmallGraphModified)
{
    Bipartite b(smallGraph);
    ASSERT_TRUE(b.isBipartite());

    smallGraph.insertEdge(3, 11);
    ASSERT_TRUE(b.isBipartite());
}