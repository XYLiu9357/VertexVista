/**adjtree-tests.cpp
 *
 * Unit tests for the adjacency tree
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include <random>
#include <iostream>

#include "adjacency-tree/src/adjtree.hpp"

// Fast 32-bit integer log2 calculation from Bit Twiddling Hacks
// http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
unsigned int lg2(unsigned int a)
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    static const char LogTable256[256] = {
        -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)};
#undef LT

    unsigned int v = a; // 32-bit word to find the log of
    unsigned r;         // r will be lg(v)
    unsigned int t, tt; // temporaries

    tt = v >> 16;
    if (tt != 0)
    {
        t = tt >> 8;
        if (t != 0)
            r = 24 + LogTable256[t]; // Higher-order 8 bits are non-zero
        else
            r = 16 + LogTable256[tt]; // Higher-order 16 bits are non-zero, but next 8 bits are zero
    }
    else
    {
        t = v >> 8;
        if (t != 0)
            r = 8 + LogTable256[t]; // Lower-order 16 bits are zero, but next 8 bits are non-zero
        else
            r = LogTable256[v]; // Lower-order 24 bits are zero
    }

    return r;
}

/**
 * Note: the pseudorandom generator starts producing repeated keys
 * if STRESS_TEST_SAMPLE_COUNT > 100,000, which invalidate some of
 * the unit tests.
 */

// Stress test parameters
constexpr unsigned int STRESS_TEST_SAMPLE_COUNT = 100000;
constexpr unsigned int STRESS_TEST_STRIDING = 293;
constexpr unsigned int RAND_GEN_SEED = 1;
const unsigned int STRESS_TEST_LG2 = lg2(STRESS_TEST_SAMPLE_COUNT);

/**
 * Tree operations: search, insert, delete, copy tree
 */

TEST(AdjTreeTest, EmptyTree)
{
    AdjTree tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_THROW(tree.at(1), std::out_of_range);
    EXPECT_THROW(tree.erase(1), std::out_of_range);
    EXPECT_THROW(tree.rankSelect(1), std::out_of_range);

    // Empty serialization is permitted in the context of adjacency tree
    EXPECT_EQ(tree.toString(), "");

    EXPECT_EQ(tree.depth(), 0);
}

TEST(AdjTreeTest, Insert7Keys)
{
    AdjTree tree;
    tree.insert({3, nullptr});
    tree.insert({1, nullptr});
    tree.insert({5, nullptr});
    tree.insert({0, nullptr});
    tree.insert({4, nullptr});
    tree.insert({2, nullptr});
    tree.insert({6, nullptr});

    EXPECT_TRUE(!tree.empty());
    EXPECT_EQ(tree.size(), 7);
    EXPECT_EQ(tree.at(0), nullptr);
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(!tree.contains(8));
}

TEST(AdjTreeTest, Initialize7Integers)
{
    AdjTree tree{{3, nullptr}, {1, nullptr}, {5, nullptr}, {0, nullptr}, {4, nullptr}, {2, nullptr}, {6, nullptr}};

    EXPECT_TRUE(!tree.empty());
    EXPECT_EQ(tree.size(), 7);
    EXPECT_EQ(tree.at(0), nullptr);
    EXPECT_EQ(tree.at(3), nullptr);
    EXPECT_EQ(tree.at(5), nullptr);
}

TEST(AdjTreeTest, SerializeAndDepth)
{
    AdjTree tree{{3, nullptr}, {1, nullptr}, {5, nullptr}, {0, nullptr}, {4, nullptr}, {2, nullptr}, {6, nullptr}};

    EXPECT_TRUE(!tree.empty());
    EXPECT_EQ(tree.size(), 7);

    std::string serializedTree = tree.toString();
    std::string expected = "0,1,2,3,4,5,6,";
    EXPECT_EQ(serializedTree, expected);
    EXPECT_EQ(tree.depth(), 3);
}

TEST(AdjTreeTest, WorstCaseInsert7Integers)
{
    AdjTree tree{{0, nullptr}, {1, nullptr}, {2, nullptr}, {3, nullptr}, {4, nullptr}, {5, nullptr}, {6, nullptr}};

    std::string serializedTree = tree.toString();
    std::string expected = "0,1,2,3,4,5,6,";
    EXPECT_TRUE(!tree.empty());
    EXPECT_EQ(tree.size(), 7);
    EXPECT_EQ(serializedTree, expected);
}

TEST(AdjTreeTest, RandomStressTestInsertOnly)
{
    std::mt19937 randGen(RAND_GEN_SEED);
    AdjTree tree;

    int randNum = 0;
    int accessKey = 0;
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
    {
        randNum = randGen();
        tree.insert({randNum, nullptr});

        // Randomly choose a key to store
        if (randNum % 17 == 0)
            accessKey = randNum;

        // Randomly delete a key and check exception on access
        if (randNum % STRESS_TEST_STRIDING == 0)
            EXPECT_TRUE(tree.contains(accessKey));
    }

    EXPECT_EQ(tree.size(), STRESS_TEST_SAMPLE_COUNT);
    EXPECT_TRUE(tree.depth() <= STRESS_TEST_LG2 + STRESS_TEST_LG2); // Depth <= 2lgN
}

TEST(AdjTreeTest, WorstCaseStressTestInsertOnly)
{
    AdjTree tree;
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
        tree.insert({i, nullptr});

    EXPECT_EQ(tree.size(), STRESS_TEST_SAMPLE_COUNT);
    EXPECT_TRUE(tree.depth() <= STRESS_TEST_LG2 + STRESS_TEST_LG2); // Depth <= 2lgN
}

TEST(AdjTreeTest, Insert10IntegersWithDelete)
{
    AdjTree tree;
    for (int i = 0; i < 10; i++)
        tree.insert({i, nullptr});

    tree.erase(1);
    tree.erase(3);
    tree.erase(5);
    tree.erase(8);

    EXPECT_EQ(tree.size(), 6);
    EXPECT_TRUE(tree.contains(0));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(9));

    size_t depth = tree.depth();
    EXPECT_TRUE(depth == 3);

    EXPECT_THROW(tree.erase(1), std::out_of_range);
    EXPECT_THROW(tree.at(1), std::out_of_range);
}

TEST(AdjTreeTest, RandomStressTestMixedInsertErase)
{
    std::mt19937 randGen(RAND_GEN_SEED);
    AdjTree tree;

    int randNum = 0;
    int deleteCount = 0;
    int deleteKey = 0;
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; ++i)
    {
        randNum = randGen();
        tree.insert({randNum, nullptr});

        // Randomly choose a key to delete
        if (i % 7 == 0)
            deleteKey = randNum;

        // Randomly delete a key and check exception on access
        if (i % STRESS_TEST_STRIDING == 0)
        {
            EXPECT_TRUE(tree.contains(deleteKey));
            tree.erase(deleteKey);
            deleteCount++;
            EXPECT_THROW(tree.at(deleteKey), std::out_of_range);
        }
    }

    EXPECT_EQ(tree.size(), STRESS_TEST_SAMPLE_COUNT - deleteCount);

    size_t depth = tree.depth();
    EXPECT_TRUE(depth <= STRESS_TEST_LG2 + STRESS_TEST_LG2); // Depth <= 2lgN
}

TEST(AdjTreeTest, WorstCaseStressTestMixedInsertErase)
{
    AdjTree tree;
    int deleteCount = 0;
    int deleteKey = 0;
    for (int i = 0; i < STRESS_TEST_SAMPLE_COUNT; i++)
    {
        tree.insert({i, nullptr});

        // Store key i / 4
        if (i % 7 == 0)
            deleteKey = i >> 2;

        // Delete key every time i % 96 == 0
        if (i % STRESS_TEST_STRIDING == 0)
        {
            EXPECT_TRUE(tree.contains(deleteKey));
            tree.erase(deleteKey);
            deleteCount++;
            EXPECT_THROW(tree.at(deleteKey), std::out_of_range);
        }
    }

    EXPECT_EQ(tree.size(), STRESS_TEST_SAMPLE_COUNT - deleteCount);

    size_t depth = tree.depth();
    EXPECT_TRUE(depth <= STRESS_TEST_LG2 + STRESS_TEST_LG2); // Depth <= 2lgN
    EXPECT_TRUE(depth <= STRESS_TEST_LG2 + STRESS_TEST_LG2); // Depth <= 2lgN
}

TEST(AdjTreeTest, Iterator)
{
    AdjTree tree1;
    AdjTree tree2;

    for (int i = 0; i < 20; i++)
        tree1.insert({i, nullptr});

    for (std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *> pair : tree1)
        tree2.insert(pair);

    for (int i = 0; i < 20; i++)
        tree1.erase(i);

    EXPECT_TRUE(tree1.empty());
    EXPECT_TRUE(tree1.size() == 0);
    EXPECT_TRUE(tree2.size() == 20);

    int counter = 0;
    for (std::pair<int, RedBlackTree<int, AdjTree>::TreeNode *> pair : tree2)
    {
        EXPECT_EQ(pair.first, counter);
        EXPECT_EQ(tree2.find(counter)->first, counter);
        counter++;
    }
}