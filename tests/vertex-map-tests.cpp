/**vertex-map-tests.cpp
 *
 * Unit tests for vertex map data structure.
 */

#include <gtest/gtest.h>
#include "digraph/vertex-map.hpp"

// Test fixture for VertexMap
class VertexMapTest : public ::testing::Test
{
protected:
    VertexMap map;
};

// Test insertion and retrieval
TEST_F(VertexMapTest, InsertAndRetrieve)
{
    map.insert(1, 100);
    EXPECT_EQ(map.at(1), 100);

    map.insert(2, 200);
    EXPECT_EQ(map.at(2), 200);

    map.insert(1, 300); // Update value
    EXPECT_EQ(map.at(1), 300);

    map[2] = 500;
    EXPECT_EQ(map.at(2), 500);

    map[3] = 600;
    EXPECT_EQ(map[3], 600);
}

// Test contains method
TEST_F(VertexMapTest, Contains)
{
    map.insert(1, 100);
    EXPECT_TRUE(map.contains(1));
    EXPECT_FALSE(map.contains(2));
}

// Test erasure
TEST_F(VertexMapTest, Erase)
{
    map.insert(1, 100);
    map.erase(1);
    EXPECT_FALSE(map.contains(1));
    EXPECT_EQ(map.at(1), -1);
}

// Test size method
TEST_F(VertexMapTest, Size)
{
    EXPECT_EQ(map.size(), 0);
    map.insert(1, 100);
    EXPECT_EQ(map.size(), 1);
    map.insert(2, 200);
    EXPECT_EQ(map.size(), 2);
    map.erase(1);
    EXPECT_EQ(map.size(), 1);
}

// Stress test
TEST_F(VertexMapTest, StressTest)
{
    const int numElements = 100000;

    // Insert 100,000 elements
    for (int i = 0; i < numElements; ++i)
        map.insert(i, i);

    // Check size
    EXPECT_EQ(map.size(), numElements);

    // Check correctness of inserted elements
    for (int i = 0; i < numElements; ++i)
        EXPECT_EQ(map.at(i), i);

    // Measure performance of access
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numElements; ++i)
        EXPECT_EQ(map.at(i), i);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    if (duration > std::chrono::duration<double>(0.007))
        FAIL();
}