/**digraph-tests.cpp
 *
 * Unit tests for directed graph data structure.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "graph/graph.hpp"

constexpr unsigned int STRESS_TEST_SAMPLE_COUNT = 10000;

TEST(DigraphTest, DefaultConstructor)
{
    Graph g;
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
    EXPECT_EQ(g.toString(",", true), "");
}

TEST(DigraphTest, VertexCountConstructor)
{
    int V = 5;
    Graph g(V);
    EXPECT_EQ(g.V(), V);
    EXPECT_EQ(g.E(), 0);
    EXPECT_NO_THROW(g.insertEdge(1, 2));
}

TEST(DigraphTest, ToString)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    std::string expected = "1: 1 -> 2[1.00],\n2: \n";
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(DigraphTest, CopyConstructor)
{
    Graph g1(5);
    g1.insertEdge(0, 1);
    g1.insertEdge(1, 2);
    Graph g2(g1);
    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);
    EXPECT_EQ(g1.toString(",", true), g2.toString(",", true));

    for (int i = 0; i < 5; i++)
        g1.eraseVertex(i);
    EXPECT_EQ(g1.V(), 0);
    EXPECT_EQ(g2.V(), 5);
}

TEST(DigraphTest, InsertVertex)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    EXPECT_EQ(g.V(), 3);
    g.insertEdge(1, 2);
    g.insertEdge(2, 1);
    g.insertEdge(3, 1);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n3: 3 -> 1[1.00],\n");
}

TEST(DigraphTest, InsertEdge)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    EXPECT_EQ(g.E(), 1);
}

TEST(DigraphTest, EraseEdge)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);

    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);

    g.eraseEdge(2, 4);
    EXPECT_EQ(g.E(), 2);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 3[1.00],\n3: \n4: \n");
    EXPECT_THROW(g.eraseEdge(1, 5), std::out_of_range);
    EXPECT_NO_THROW(g.eraseEdge(1, 4));
}

TEST(DigraphTest, EraseVertex)
{
    int N = 10;
    Graph g(N);

    // Each vertex connects to every vertex (including itself)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            g.insertEdge(i, j);

    g.eraseVertex(N - 1);
    EXPECT_EQ(g.V(), N - 1);
    EXPECT_EQ(g.E(), (N - 1) * (N - 1));

    std::string expected = "";
    for (int i = 0; i < N - 1; i++)
    {
        expected += std::to_string(i) + ": ";
        for (int j = 0; j < N - 1; j++)
            expected += std::to_string(i) + " -> " + std::to_string(j) + "[1.00]" + ",";
        expected += "\n";
    }
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(DigraphTest, MixedOpsWithIntializerList)
{
    Graph g = {0, 2, 4, 6, 8, 10};

    // Mixed insertion followed by edge removal
    g.insertEdge({{0, 2}, {0, 4}, {2, 6}, {2, 8}, {4, 8}, {4, 10}, {6, 10}});
    EXPECT_EQ(g.V(), 6);
    EXPECT_EQ(g.E(), 7);
    for (int i = 1; i < 10; i += 2)
    {
        g.insertVertex(i);
        g.insertEdge(i - 1, i);
        g.insertEdge(i + 1, i);
    }
    EXPECT_EQ(g.V(), 11);
    EXPECT_EQ(g.E(), 17);
    g.eraseEdge({{0, 2}, {0, 4}, {2, 6}, {2, 8}, {4, 8}, {4, 10}, {6, 10}});

    std::string expected = "0: 0 -> 1[1.00],\n1: \n2: 2 -> 1[1.00],2 -> 3[1.00],\n3: \n4: 4 -> 3[1.00],4 -> 5[1.00],\n5: \n6: 6 -> 5[1.00],6 -> 7[1.00],\n7: \n8: 8 -> 7[1.00],8 -> 9[1.00],\n9: \n10: 10 -> 9[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Erase all odd vertices, which should remove all edges
    g.eraseVertex({1, 3, 5, 7, 9});
    expected = "0: \n2: \n4: \n6: \n8: \n10: \n";
    EXPECT_EQ(g.toString(",", true), expected);
    EXPECT_EQ(g.E(), 0);
    EXPECT_EQ(g.V(), 6);

    // Cyclic graphs with bidirectional edges
    g.insertEdge({{0, 2}, {2, 4}, {4, 6}, {6, 8}, {8, 10}, {10, 0}});
    EXPECT_EQ(g.E(), 6);
    g.insertEdge({{2, 0}, {6, 4}, {10, 8}});
    EXPECT_EQ(g.E(), 9);
    expected = "0: 2,\n2: 0,4,\n4: 6,\n6: 4,8,\n8: 10,\n10: 0,8,\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Remove vertices linked by bidirectional links
    g.eraseVertex({2, 8});
    EXPECT_EQ(g.V(), 4);
    EXPECT_EQ(g.E(), 3);
    expected = "0: \n4: 6,\n6: 4,\n10: 0,\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Self cycles
    g.eraseVertex({4, 6});
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 1);
    EXPECT_THROW(g.eraseEdge({{4, 4}}), std::out_of_range);
    EXPECT_THROW(g.eraseEdge({{0, 10}}), std::out_of_range);
    EXPECT_NO_THROW(g.eraseEdge({{10, 0}}));

    g.insertEdge({{0, 0}, {0, 10}, {10, 0}, {10, 10}});
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 4);
    expected = "0: 0,10,\n10: 0,10,\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // A series of deletions and checks
    g.eraseEdge(0, 0);
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 3);
    expected = "0: 10,\n10: 0,10,\n";
    EXPECT_EQ(g.toString(",", true), expected);

    g.eraseEdge(10, 0);
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 2);

    g.eraseVertex(0);
    EXPECT_EQ(g.V(), 1);
    EXPECT_EQ(g.E(), 1);

    g.eraseEdge(10, 10);
    EXPECT_EQ(g.V(), 1);
    EXPECT_EQ(g.E(), 0);
    g.eraseVertex(10);
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
}

TEST(DigraphTest, InsertionWithRepetitions)
{
    Graph g(5);

    // Repetitive vertex insertion
    g.insertVertex({0, 1, 2, 3, 4});
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.E(), 0);

    g.insertEdge(0, 4);
    g.insertEdge(1, 3);
    g.insertEdge(2, 2);
    EXPECT_EQ(g.E(), 3);

    // Repetitive edge insertion
    g.insertEdge(1, 3);
    g.insertEdge(2, 2);
    EXPECT_EQ(g.E(), 3);
    std::string expected = "0: 4,\n1: 3,\n2: 2,\n3: \n4: \n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Bidirectional edge
    g.insertEdge(3, 1);
    g.insertEdge(1, 3);
    expected = "0: 4,\n1: 3,\n2: 2,\n3: 1,\n4: \n";
    EXPECT_EQ(g.E(), 4);
    EXPECT_EQ(g.toString(",", true), expected);

    g.insertVertex({1, 3});
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.E(), 4);

    // Remove edge then insert twice
    g.eraseEdge(3, 1);
    g.insertEdge(3, 1);
    g.insertEdge(1, 3);
    g.insertEdge(3, 1);
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.E(), 4);
}

TEST(DigraphTest, MixedStressTest)
{
    Graph g;

    // Insertion with cycles
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
    {
        g.insertVertex(i);
        g.insertEdge(i, i % 100);
        g.insertEdge(i % 100, i);
        g.insertEdge(i % 100, 0);
    }

    EXPECT_EQ(g.V(), STRESS_TEST_SAMPLE_COUNT);
    EXPECT_EQ(g.E(), STRESS_TEST_SAMPLE_COUNT + STRESS_TEST_SAMPLE_COUNT - 1);

    // Reduce bidirectional edges to monodirectional edges
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
        g.eraseEdge(i, i % 100);

    EXPECT_EQ(g.V(), STRESS_TEST_SAMPLE_COUNT);
    EXPECT_EQ(g.E(), STRESS_TEST_SAMPLE_COUNT - 1);

    // Erase vertices above 100
    for (int i = 100; i < STRESS_TEST_SAMPLE_COUNT; i++)
        g.eraseVertex(i);
    EXPECT_EQ(g.V(), 100);
    EXPECT_EQ(g.E(), 99);
}
