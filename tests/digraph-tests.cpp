/**digraph-tests.cpp
 *
 * Unit tests for directed graph API.
 */

#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "digraph/digraph.hpp"
#include "digraph/digraph-traverse.hpp"

TEST(DigraphTest, DefaultConstructor)
{
    Digraph g;
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
}

TEST(DigraphTest, VertexConstructor)
{
    Digraph g(5);
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.E(), 0);
}

TEST(DigraphTest, AddEdge)
{
    Digraph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    EXPECT_EQ(g.E(), 4);

    std::vector<int> adj0 = g.adj(0);
    EXPECT_EQ(adj0.size(), 2);
    EXPECT_EQ(adj0[0], 2);
    EXPECT_EQ(adj0[1], 1);

    std::vector<int> adj1 = g.adj(1);
    EXPECT_EQ(adj1.size(), 2);
    EXPECT_EQ(adj1[0], 3);
    EXPECT_EQ(adj1[1], 2);
}

TEST(DigraphTest, CopyConstructor)
{
    Digraph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);

    Digraph g2 = g1;

    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);

    std::vector<int> adj0 = g2.adj(0);
    EXPECT_EQ(adj0.size(), 2);
    EXPECT_EQ(adj0[0], 2);
    EXPECT_EQ(adj0[1], 1);
}

TEST(DigraphTest, ToString)
{
    Digraph g(3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);

    std::string expected = "0: 2 1 \n1: 2 \n2: \n";
    EXPECT_EQ(g.toString(), expected);
}
