/**digraph-tests.cpp
 *
 * Unit tests for directed graph data structure.
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "graph/digraph.hpp"
#include "graph/graph.hpp"

constexpr unsigned int STRESS_TEST_SAMPLE_COUNT = 10000;

/**
 * Directed Graph Tests
 */

TEST(DiGraphTest, DefaultConstructor)
{
    DiGraph g;
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
    EXPECT_EQ(g.toString(",", true), "");
}

TEST(DiGraphTest, VertexCountConstructor)
{
    int V = 5;
    DiGraph g(V);
    EXPECT_EQ(g.V(), V);
    EXPECT_EQ(g.E(), 0);
    EXPECT_NO_THROW(g.insertEdge(1, 2));
}

TEST(DiGraphTest, ToString)
{
    DiGraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    std::string expected = "1: 1 -> 2[1.00],\n2: \n";
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(DiGraphTest, CopyConstructor)
{
    DiGraph g1(5);
    g1.insertEdge(0, 1);
    g1.insertEdge(1, 2);
    DiGraph g2(g1);
    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);
    EXPECT_EQ(g1.toString(",", true), g2.toString(",", true));

    for (int i = 0; i < 5; i++)
        g1.eraseVertex(i);
    EXPECT_EQ(g1.V(), 0);
    EXPECT_EQ(g2.V(), 5);
}

TEST(DiGraphTest, CopyAssignment)
{
    DiGraph g1(5);
    g1.insertEdge(0, 1);
    g1.insertEdge(1, 2);
    DiGraph g2 = g1;
    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);
    EXPECT_EQ(g1.toString(",", true), g2.toString(",", true));

    for (int i = 0; i < 5; i++)
        g1.eraseVertex(i);
    EXPECT_EQ(g1.V(), 0);
    EXPECT_EQ(g2.V(), 5);
}

TEST(DiGraphTest, InsertVertex)
{
    DiGraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    EXPECT_EQ(g.V(), 3);
    g.insertEdge(1, 2);
    g.insertEdge(2, 1);
    g.insertEdge(3, 1);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n3: 3 -> 1[1.00],\n");
}

TEST(DiGraphTest, InsertEdge)
{
    DiGraph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    EXPECT_EQ(g.E(), 1);
}

TEST(DiGraphTest, EraseEdge)
{
    DiGraph g;
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

TEST(DiGraphTest, EraseVertex)
{
    int N = 10;
    DiGraph g(N);

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

TEST(DiGraphTest, MixedOpsWithIntializerList)
{
    DiGraph g = {0, 2, 4, 6, 8, 10};

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
    expected = "0: 0 -> 2[1.00],\n2: 2 -> 0[1.00],2 -> 4[1.00],\n4: 4 -> 6[1.00],\n6: 6 -> 4[1.00],6 -> 8[1.00],\n8: 8 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 8[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Remove vertices linked by bidirectional links
    g.eraseVertex({2, 8});
    EXPECT_EQ(g.V(), 4);
    EXPECT_EQ(g.E(), 3);
    expected = "0: \n4: 4 -> 6[1.00],\n6: 6 -> 4[1.00],\n10: 10 -> 0[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Self cycles
    g.eraseVertex({4, 6});
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 1);
    EXPECT_THROW(g.eraseEdge({{4, 4}}), std::out_of_range);
    EXPECT_NO_THROW(g.eraseEdge({{10, 0}}));

    g.insertEdge({{0, 0}, {0, 10}, {10, 0}, {10, 10}});
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 4);
    expected = "0: 0 -> 0[1.00],0 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 10[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // A series of deletions and checks
    g.eraseEdge(0, 0);
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 3);
    expected = "0: 0 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 10[1.00],\n";
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

TEST(DiGraphTest, InsertionWithRepetitions)
{
    DiGraph g(5);

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
    std::string expected = "0: 0 -> 4[1.00],\n1: 1 -> 3[1.00],\n2: 2 -> 2[1.00],\n3: \n4: \n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Bidirectional edge
    g.insertEdge(3, 1);
    g.insertEdge(1, 3);
    expected = "0: 0 -> 4[1.00],\n1: 1 -> 3[1.00],\n2: 2 -> 2[1.00],\n3: 3 -> 1[1.00],\n4: \n";
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

TEST(DiGraphTest, MixedStressTest)
{
    DiGraph g;

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

/**
 * Undirected Graph Tests
 */

TEST(GraphTest, DefaultConstructor)
{
    Graph g;
    EXPECT_EQ(g.V(), 0);
    EXPECT_EQ(g.E(), 0);
    EXPECT_EQ(g.toString(",", true), "");
}

TEST(GraphTest, VertexCountConstructor)
{
    int V = 5;
    Graph g(V);
    EXPECT_EQ(g.V(), V);
    EXPECT_EQ(g.E(), 0);
    EXPECT_NO_THROW(g.insertEdge(1, 2));
}

TEST(GraphTest, ToString)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    std::string expected = "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(GraphTest, CopyConstructor)
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

TEST(GraphTest, CopyAssignment)
{
    Graph g1(5);
    g1.insertEdge(0, 1);
    g1.insertEdge(1, 2);
    Graph g2 = g1;
    EXPECT_EQ(g2.V(), 5);
    EXPECT_EQ(g2.E(), 2);
    EXPECT_EQ(g1.toString(",", true), g2.toString(",", true));

    for (int i = 0; i < 5; i++)
        g1.eraseVertex(i);
    EXPECT_EQ(g1.V(), 0);
    EXPECT_EQ(g2.V(), 5);
}

TEST(GraphTest, InsertVertex)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    EXPECT_EQ(g.V(), 3);
    g.insertEdge(1, 2);
    g.insertEdge(3, 1);
    EXPECT_EQ(g.E(), 2);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],1 -> 3[1.00],\n2: 2 -> 1[1.00],\n3: 3 -> 1[1.00],\n");
}

TEST(GraphTest, InsertEdge)
{
    Graph g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertEdge(1, 2);
    EXPECT_EQ(g.E(), 1);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n");
}

TEST(GraphTest, EraseEdge)
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
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],2 -> 3[1.00],\n3: 3 -> 2[1.00],\n4: \n");
    EXPECT_THROW(g.eraseEdge(1, 5), std::out_of_range);
    EXPECT_NO_THROW(g.eraseEdge(1, 4));
}

TEST(GraphTest, EraseVertex)
{
    int N = 10;
    Graph g(N);

    // Each vertex connects to every vertex (excluding itself)
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            g.insertEdge(i, j);

    EXPECT_EQ(g.E(), N * (N - 1) / 2);
    g.eraseVertex(N - 1);
    EXPECT_EQ(g.V(), N - 1);
    EXPECT_EQ(g.E(), (N - 1) * (N - 2) / 2);

    std::string expected = "";
    for (int i = 0; i < N - 1; i++)
    {
        expected += std::to_string(i) + ": ";
        for (int j = 0; j < N - 1; j++)
            if (i != j)
                expected += std::to_string(i) + " -> " + std::to_string(j) + "[1.00]" + ",";
        expected += "\n";
    }
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(GraphTest, MixedOpsWithInitializerList)
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

    // Compiler auto-concatenates adjacent string literals
    std::string expected = "0: 0 -> 1[1.00],\n1: 1 -> 0[1.00],1 -> 2[1.00],\n2: 2 -> 1[1.00],2 -> 3[1.00],\n3: 3 -> 2[1.00],3 -> 4[1.00],\n"
                           "4: 4 -> 3[1.00],4 -> 5[1.00],\n5: 5 -> 4[1.00],5 -> 6[1.00],\n6: 6 -> 5[1.00],6 -> 7[1.00],\n7: 7 -> 6[1.00],7 -> 8[1.00],\n"
                           "8: 8 -> 7[1.00],8 -> 9[1.00],\n9: 9 -> 8[1.00],9 -> 10[1.00],\n10: 10 -> 9[1.00],\n";

    EXPECT_EQ(g.toString(",", true), expected);

    // Erase all odd vertices, which should remove all edges
    g.eraseVertex({1, 3, 5, 7, 9});
    expected = "0: \n2: \n4: \n6: \n8: \n10: \n";
    EXPECT_EQ(g.toString(",", true), expected);
    EXPECT_EQ(g.E(), 0);
    EXPECT_EQ(g.V(), 6);

    // Undirected edge repetitive insertion (should have no effect)
    g.insertEdge({{0, 2}, {2, 4}, {4, 6}, {6, 8}, {8, 10}, {10, 0}});
    EXPECT_EQ(g.E(), 6);
    g.insertEdge({{2, 0}, {6, 4}, {10, 8}});
    EXPECT_EQ(g.E(), 6);
    expected = "0: 0 -> 2[1.00],0 -> 10[1.00],\n2: 2 -> 0[1.00],2 -> 4[1.00],\n4: 4 -> 2[1.00],4 -> 6[1.00],\n6: 6 -> 4[1.00],6 -> 8[1.00],\n8: 8 -> 6[1.00],8 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 8[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Remove vertices linked by undirected edges
    g.eraseVertex({2, 8});
    EXPECT_EQ(g.V(), 4);
    EXPECT_EQ(g.E(), 2); // 0 <-> 10 and 4 <-> 6
    expected = "0: 0 -> 10[1.00],\n4: 4 -> 6[1.00],\n6: 6 -> 4[1.00],\n10: 10 -> 0[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Self cycles
    g.eraseVertex({4, 6});
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 1);
    EXPECT_THROW(g.eraseEdge({{4, 4}}), std::out_of_range);
    EXPECT_NO_THROW(g.eraseEdge({{10, 0}}));

    // After removing the only remaining edge, graph should be empty of edges
    EXPECT_EQ(g.E(), 0);
    expected = "0: \n10: \n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Insert back the vertices and create a complete graph
    g.insertVertex(2);
    g.insertEdge({{0, 2}, {0, 10}, {2, 10}});
    EXPECT_EQ(g.V(), 3);
    EXPECT_EQ(g.E(), 3);
    expected = "0: 0 -> 2[1.00],0 -> 10[1.00],\n2: 2 -> 0[1.00],2 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 2[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Add a new vertex and connect to every other vertex, creating a star graph
    g.insertVertex(1);
    g.insertEdge(1, 0);
    g.insertEdge(1, 2);
    g.insertEdge(1, 10);
    EXPECT_EQ(g.V(), 4);
    EXPECT_EQ(g.E(), 6);
    expected = "0: 0 -> 1[1.00],0 -> 2[1.00],0 -> 10[1.00],\n1: 1 -> 0[1.00],1 -> 2[1.00],1 -> 10[1.00],\n2: 2 -> 0[1.00],2 -> 1[1.00],2 -> 10[1.00],\n10: 10 -> 0[1.00],10 -> 1[1.00],10 -> 2[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);

    // Remove edges to form a linear chain of vertices
    g.eraseEdge({{0, 2}, {2, 10}, {1, 10}});
    EXPECT_EQ(g.E(), 3);
    expected = "0: 0 -> 1[1.00],0 -> 10[1.00],\n1: 1 -> 0[1.00],1 -> 2[1.00],\n2: 2 -> 1[1.00],\n10: 10 -> 0[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(GraphTest, InsertionWithRepetitions)
{
    Graph g;

    // Repeated vertex insertion
    g.insertVertex(1);
    g.insertVertex(1); // Should have no effect
    EXPECT_EQ(g.V(), 1);
    EXPECT_EQ(g.toString(",", true), "1: \n");

    // Repeated edge insertion
    g.insertVertex(2);
    g.insertEdge(1, 2);
    EXPECT_EQ(g.V(), 2);
    EXPECT_EQ(g.E(), 1);
    g.insertEdge(1, 2); // Should have no effect
    EXPECT_EQ(g.E(), 1);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n");

    // Repeated insertion with initializer list
    g.insertVertex({1, 3, 3, 3, 4, 5, 5, 5});
    EXPECT_EQ(g.V(), 5);
    EXPECT_EQ(g.toString(",", true), "1: 1 -> 2[1.00],\n2: 2 -> 1[1.00],\n3: \n4: \n5: \n");

    // Inserting multiple edges, some of which are duplicates
    g.insertEdge({{1, 3}, {2, 3}, {4, 5}, {4, 5}, {1, 3}});
    EXPECT_EQ(g.E(), 4);
    std::string expected = "1: 1 -> 2[1.00],1 -> 3[1.00],\n2: 2 -> 1[1.00],2 -> 3[1.00],\n3: 3 -> 1[1.00],3 -> 2[1.00],\n4: 4 -> 5[1.00],\n5: 5 -> 4[1.00],\n";
    EXPECT_EQ(g.toString(",", true), expected);
}

TEST(GraphTest, MixedStressTest)
{
    Graph g;

    // A connected line-graph with 100 vertices
    for (int i = 0; i < 100; ++i)
    {
        g.insertVertex(i);
        if (i > 0)
            g.insertEdge(i - 1, i); // Should be bidirectional
    }
    EXPECT_EQ(g.V(), 100);
    EXPECT_EQ(g.E(), 99);

    // Edge re-insertion, should have no effect
    g.insertEdge(0, 1);
    g.insertEdge(1, 0);
    EXPECT_EQ(g.E(), 99);

    // Vertex re-insertion, should have no effect
    g.insertVertex(0);
    g.insertVertex(50);
    EXPECT_EQ(g.V(), 100);

    // Bulk delete and validate
    for (int i = 0; i < 50; i += 2)
        g.eraseVertex(i);

    // 25 deletions, all odd vertices < 48 (1 ~ 47) are disconnected
    // The line graph from 49 ~ 100 has 50 edges in between
    EXPECT_EQ(g.V(), 75);

    // Verify structure after deletions
    for (int i = 1; i < 100; i += 2)
    {
        // Should not fail for valid vertices
        EXPECT_NO_THROW(g.insertEdge(i, (i + 2) % 100));
        EXPECT_NO_THROW(g.eraseEdge(i, (i + 2) % 100));
    }
    EXPECT_EQ(g.E(), 50);

    // Erase some edges to create isolated components
    g.eraseEdge(60, 61);
    g.eraseEdge(84, 83);
    EXPECT_EQ(g.E(), 48);
}
