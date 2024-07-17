/**linked-list-tests.cpp
 *
 * Unit tests for linked list API.
 */

#include <gtest/gtest.h>
#include <iostream>
#include "linked-list/linked-list.hpp"

// Test 1: Insert and Find
TEST(ListTest, InsertAndFind)
{
    List list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    List::Iterator it = list.find(20);
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, 20);

    it = list.find(40);
    EXPECT_EQ(it, list.end());
}

// Test 2: Erase Head
TEST(ListTest, EraseHead)
{
    List list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    list.erase(30);
    List::Iterator it = list.begin();
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, list.end());
}

// Test 3: Erase Middle Element
TEST(ListTest, EraseMiddleElement)
{
    List list = {10, 20, 30};

    list.erase(20);
    List::Iterator it = list.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, list.end());
}

// Test 4: Erase NonExistentElement
TEST(ListTest, EraseNonExistentElement)
{
    List list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    list.erase(40); // Trying to erase a non-existent element
    List::Iterator it = list.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(it, list.end());
}

// Test 5: Stress Test with Many Insertions
TEST(ListTest, StressTestWithManyInsertions)
{
    List list;
    const int numInsertions = 20000;

    for (int i = 0; i < numInsertions; ++i)
    {
        list.insert(i);
    }

    EXPECT_NE(list.find(numInsertions - 1), list.end());
    EXPECT_NE(list.find(numInsertions / 2), list.end());
    EXPECT_NE(list.find(0), list.end());

    // Verify the size of the list
    int count = 0;
    for (List::Iterator it = list.begin(); it != list.end(); ++it)
    {
        ++count;
    }
    EXPECT_EQ(count, numInsertions);
}
