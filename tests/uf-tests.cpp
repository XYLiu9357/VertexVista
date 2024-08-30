/**tests.cpp
 *
 * Google test suites for union find.
 */

#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "graph/node-edge.hpp"
#include "utils/uf.hpp"

using namespace std;

TEST(UnionFindTest, UnionOperation5Ints)
{
    UF<int> u = UF<int>(5);
    vector<vector<int>> state(5);

    u.connect(1, 2);
    u.connect(1, 3);

    // u.getUnionState(state);
    // vector<vector<int>> expectedState = {{0}, {1, 2}, {2}, {3, 2}, {4}};
    // EXPECT_TRUE(state == expectedState);

    EXPECT_TRUE(u.isConnected(2, 3));
    EXPECT_FALSE(u.isConnected(3, 4));
    EXPECT_TRUE(u.contains(3));
    EXPECT_TRUE(u.contains(4));
    EXPECT_TRUE(!u.contains(5));
    EXPECT_TRUE(!u.contains(-1));
}

TEST(UnionFindTest, UnionOperation10Ints)
{
    UF<int> u = UF<int>(10);
    vector<vector<int>> state1(10);

    u.connect(0, 1);
    u.connect(2, 3);
    u.connect(4, 5);
    u.connect(6, 7);
    u.connect(8, 9);

    // u.getUnionState(state1);
    // vector<vector<int>> expectedState1 = {{0, 1}, {1}, {2, 3}, {3}, {4, 5}, {5}, {6, 7}, {7}, {8, 9}, {9}};
    // EXPECT_TRUE(state1 == expectedState1);

    u.connect(0, 6);
    u.connect(2, 0);
    u.connect(8, 3);
    vector<vector<int>> state2(10);
    // vector<vector<int>> expectedState2 = {{0, 7}, {1, 7}, {2, 3, 7}, {3, 7}, {4, 5}, {5}, {6, 7}, {7}, {8, 9, 7}, {9, 7}};
    // u.getUnionState(state2);
    // EXPECT_TRUE(state2 == expectedState2);
}

TEST(UnionFindTest, UnionOperation10MoreInts)
{
    UF<int> u = UF<int>(10);
    vector<vector<int>> state(10);

    u.connect(0, 1);
    u.connect(2, 3);
    u.connect(4, 5);
    u.connect(6, 7);
    u.connect(8, 9);

    u.connect(8, 2);
    u.connect(3, 1);
    u.connect(0, 6);

    // path compression kicks in
    // vector<vector<int>> expectedState = {{0, 3}, {1, 3}, {2, 3}, {3}, {4, 5}, {5}, {6, 7, 3}, {7, 3}, {8, 9, 3}, {9, 3}};
    // u.getUnionState(state);
    EXPECT_TRUE(u.isConnected(2, 3));
    EXPECT_TRUE(u.isConnected(0, 8));

    // EXPECT_TRUE(state == expectedState);
}

TEST(UnionFindTest, UnionOperation8Ints)
{
    UF<int> u = UF<int>(8);
    vector<vector<int>> state(8);

    u.connect(0, 1);
    u.connect(1, 2);
    u.connect(2, 3);
    u.connect(4, 5);
    u.connect(6, 5);
    u.connect(6, 7);
    u.connect(0, 6); // repeated

    // vector<vector<int>> expectedState = {{0, 1, 5}, {1, 5}, {2, 1, 5}, {3, 1, 5}, {4, 5}, {5}, {6, 5}, {7, 5}};
    // u.getUnionState(state);

    // EXPECT_TRUE(state == expectedState);
}

constexpr int STRESS_TEST_SAMPLE_COUNT = 100000;

TEST(UnionFindTest, IntStressTest)
{
    UF<int> u = UF<int>(STRESS_TEST_SAMPLE_COUNT);
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
    {
        if (i % 2 == 0)
            u.connect(i, 2);
        else
            u.connect(i, 3);
    }

    EXPECT_TRUE(u.isConnected(3, 1997));
    EXPECT_TRUE(u.isConnected(3, 28945));
    EXPECT_TRUE(u.isConnected(1, 3));

    EXPECT_TRUE(u.isConnected(2, 1998));
    EXPECT_TRUE(u.isConnected(2, 28946));
    EXPECT_TRUE(u.isConnected(0, 2));

    EXPECT_TRUE(!u.isConnected(0, 1));
    EXPECT_TRUE(!u.isConnected(0, 3));
}

TEST(UnionFindTest, Insert10IntOutOfOrder)
{
    UF<int> u = UF<int>({10, 8, 9, 7, 1, 5, 6, 3, 4, 2});
    u.connect(1, 3);
    u.connect(5, 6);
    u.connect(6, 7);
    u.connect(5, 1);

    EXPECT_TRUE(u.isConnected(1, 1));
    EXPECT_TRUE(u.isConnected(1, 6));
    EXPECT_TRUE(u.isConnected(1, 7));
    EXPECT_TRUE(u.isConnected(3, 7));

    u.connect(10, 10); // Self union
    u.connect(10, 8);
    u.connect(4, 8);
    u.connect(3, 4);

    EXPECT_TRUE(u.isConnected(1, 10));
    EXPECT_TRUE(u.isConnected(7, 8));
}

TEST(UnionFindTest, CopyAndCopyAssignment)
{
    UF<int> u1 = UF<int>(50);

    for (int i = 0; i < 50; i++)
        if (i % 2 == 0)
            u1.connect(0, i);

    EXPECT_TRUE(u1.isConnected(42, 44));

    UF<int> u2 = UF<int>(u1); // Copy construction
    UF<int> u3 = u2;          // Copy assignment

    EXPECT_TRUE(u2.isConnected(22, 44));
    EXPECT_TRUE(u3.isConnected(8, 38));

    for (int i = 0; i < 50; i++)
        if (i % 2 == 1)
            u1.connect(1, i);

    EXPECT_TRUE(u1.isConnected(5, 39));
    EXPECT_TRUE(!u2.isConnected(5, 39));
    EXPECT_TRUE(!u3.isConnected(5, 39));

    for (int i = 0; i < 50; i++)
        if (i % 2 == 1)
            u2.connect(49, i);

    EXPECT_TRUE(u2.isConnected(7, 39));
    EXPECT_TRUE(!u3.isConnected(9, 39));
}

TEST(UnionFindTest, ErrorBehavior)
{
    UF<int> u = UF<int>(5);

    EXPECT_THROW(u.connect(0, 5), std::out_of_range);
    EXPECT_THROW(u.connect(0, 10), std::out_of_range);
    EXPECT_THROW(u.connect(-2, 3), std::out_of_range);

    EXPECT_THROW(u.connect(0, 5), std::out_of_range);
    EXPECT_THROW(u.connect(0, 10), std::out_of_range);
    EXPECT_THROW(u.isConnected(-2, 3), std::out_of_range);
}

TEST(UnionFindTest, Insert5Strings)
{
    UF<std::string> u = {"a", "b", "c", "d", "e"};
    u.connect("a", "b");
    u.connect("c", "d");
    u.connect("d", "b");
    EXPECT_TRUE(u.isConnected("a", "d"));
    EXPECT_TRUE(u.isConnected("b", "c"));
    EXPECT_TRUE(!u.isConnected("c", "e"));

    u.insert("f");
    u.connect("f", "e");
    EXPECT_TRUE(u.isConnected("e", "f"));
    EXPECT_TRUE(!u.isConnected("a", "f"));

    u.connect("a", "f");
    EXPECT_TRUE(u.isConnected("c", "e"));
    EXPECT_TRUE(u.isConnected("b", "f"));
}

TEST(UnionFindTest, Insert8NodeObjects)
{
    UF<Node> u = {Node(5),
                  Node(3),
                  Node(4),
                  Node(7),
                  Node(1),
                  Node(0),
                  Node(2),
                  Node(6)};

    u.connect(Node(1), Node(3));
    u.connect(Node(5), Node(3));
    u.connect(Node(7), Node(1));

    EXPECT_TRUE(u.isConnected(Node(1), Node(3)));
    EXPECT_TRUE(u.isConnected(Node(7), Node(3)));
    EXPECT_TRUE(!u.isConnected(Node(2), Node(6)));
}

TEST(UnionFindTest, Insert4EdgeObjects)
{
    UF<Edge> u = {Edge(0, 1, 1),
                  Edge(1, 2, 1),
                  Edge(2, 3, 1),
                  Edge(4, 5, 1)};

    u.connect(Edge(0, 1, 1), Edge(2, 3, 1));
    u.connect(Edge(0, 1, 1), Edge(4, 5, 1));

    EXPECT_TRUE(u.isConnected(Edge(2, 3, 1), Edge(4, 5, 1)));
    EXPECT_TRUE(!u.isConnected(Edge(4, 5, 1), Edge(1, 2, 1)));
    EXPECT_THROW(u.connect(Edge(0, 0, 0), Edge(2, 3, 1)), std::out_of_range);
}