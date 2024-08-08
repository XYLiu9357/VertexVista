/**tests.cpp
 *
 * Google test suites for union find.
 */

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "utils/uf.hpp"

using namespace std;

void printState(vector<vector<int>> state)
{
    for (int i = 0; i < state.size(); i++)
    {
        int j = 0;

        for (; j < state[i].size() - 1; j++)
            cout << state[i][j] << "---";

        cout << state[i][j] << endl;
    }
}

TEST(UnionFindTest, UnionOperation5Elements)
{
    UF u = UF(5);
    vector<vector<int>> state(5);

    u.connect(1, 2);
    u.connect(1, 3);

    u.getUnionState(state);
    vector<vector<int>> expectedState = {{0}, {1, 2}, {2}, {3, 2}, {4}};

    EXPECT_TRUE(state == expectedState);
    EXPECT_TRUE(u.isConnected(2, 3));
    EXPECT_FALSE(u.isConnected(3, 4));
}

TEST(UnionFindTest, UnionOperation10Elements)
{
    UF u = UF(10);
    vector<vector<int>> state1(10);

    u.connect(0, 1);
    u.connect(2, 3);
    u.connect(4, 5);
    u.connect(6, 7);
    u.connect(8, 9);

    u.getUnionState(state1);
    vector<vector<int>> expectedState1 = {{0, 1}, {1}, {2, 3}, {3}, {4, 5}, {5}, {6, 7}, {7}, {8, 9}, {9}};
    EXPECT_TRUE(state1 == expectedState1);

    u.connect(0, 6);
    u.connect(2, 0);
    u.connect(8, 3);
    vector<vector<int>> state2(10);
    vector<vector<int>> expectedState2 = {{0, 7}, {1, 7}, {2, 3, 7}, {3, 7}, {4, 5}, {5}, {6, 7}, {7}, {8, 9, 7}, {9, 7}};
    u.getUnionState(state2);

    EXPECT_TRUE(state2 == expectedState2);
}

TEST(UnionFindTest, UnionOperation10ElementsSequel)
{
    UF u = UF(10);
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
    vector<vector<int>> expectedState = {{0, 3}, {1, 3}, {2, 3}, {3}, {4, 5}, {5}, {6, 7, 3}, {7, 3}, {8, 9, 3}, {9, 3}};
    u.getUnionState(state);
    EXPECT_TRUE(u.isConnected(2, 3));
    EXPECT_TRUE(u.isConnected(0, 8));

    EXPECT_TRUE(state == expectedState);
}

TEST(UnionFindTest, UnionOperation8Elements)
{
    UF u = UF(8);
    vector<vector<int>> state(8);

    u.connect(0, 1);
    u.connect(1, 2);
    u.connect(2, 3);
    u.connect(4, 5);
    u.connect(6, 5);
    u.connect(6, 7);
    u.connect(0, 6); // repeated

    vector<vector<int>> expectedState = {{0, 1, 5}, {1, 5}, {2, 1, 5}, {3, 1, 5}, {4, 5}, {5}, {6, 5}, {7, 5}};
    u.getUnionState(state);

    EXPECT_TRUE(state == expectedState);
}

constexpr int STRESS_TEST_SAMPLE_COUNT = 100000;

TEST(UnionFindTest, StressTest)
{
    UF u = UF(STRESS_TEST_SAMPLE_COUNT);
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