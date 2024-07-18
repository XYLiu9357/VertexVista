/**digraph-tests.cpp
 *
 * Unit tests for directed graph API.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "digraph/digraph.hpp" // Include the header file for the Digraph class

// Test the default constructor
TEST(DigraphTest, DefaultConstructor)
{
    Digraph g;
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
    EXPECT_THROW(g.toString(), std::out_of_range);
}

// Test the constructor with a specified number of vertices
TEST(DigraphTest, VertexCountConstructor)
{
    int V = 5;
    Digraph g(V);
    EXPECT_EQ(g.V(), V);
    EXPECT_EQ(g.E(), 0);
}

// Test the copy constructor
TEST(DigraphTest, CopyConstructor)
{
    Digraph g1(5);
    g1.insertEdge(0, 1);
    g1.insertEdge(1, 2);
    Digraph g2(g1);
    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);
    EXPECT_EQ(g1.toString(), g2.toString());
}

// Test inserting a vertex
TEST(DigraphTest, InsertVertex)
{
    Digraph g;
    g.insertVertex(1);
    EXPECT_EQ(g.V(), 1);
}

// Test inserting an edge
TEST(DigraphTest, InsertEdge)
{
    Digraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    EXPECT_EQ(g.E(), 1);
}

// Test removing a vertex
TEST(DigraphTest, EraseVertex)
{
    Digraph g;
    g.insertVertex(1);
    g.eraseVertex(1);
    EXPECT_EQ(g.V(), 0);
}

// Test removing an edge
TEST(DigraphTest, EraseEdge)
{
    Digraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    g.eraseEdge(1, 2);
    EXPECT_EQ(g.E(), 0);
}

// Test serialization of the graph
TEST(DigraphTest, ToString)
{
    Digraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    std::string expected = "1: 2,\n2: \n"; // Adjust this to match the expected serialization format
    EXPECT_EQ(g.toString(), expected);
}
