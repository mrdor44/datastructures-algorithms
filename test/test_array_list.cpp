#include <vector>
#include "inc/array_list.hpp"
#include "mock.hpp"

int push_beyond_capacity(ArrayList<int>& list) {
    const int capacity = list.capacity();
    int i = 0;
    for (; i < 1 + capacity; ++i) {
        list.push_back(i);
    }
    return i - 1; // as the last value pushed back
}

TEST(ArrayList, PushBack) {
    ArrayList<int> list;
    list.push_back(5);
    EXPECT_EQ(5, list[0]);
}

TEST(ArrayList, PushBeyondCapacity) {
    ArrayList<int> list;
    int last_value = push_beyond_capacity(list);
    EXPECT_EQ(last_value, list.back());
    last_value = push_beyond_capacity(list);
    EXPECT_EQ(last_value, list.back());
}

TEST(ArrayList, PopAndReduceCapacity) {
    ArrayList<int> list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ASSERT_EQ(10, list.length());
    ASSERT_EQ(16, list.capacity());
    list.pop_back();
    ASSERT_EQ(16, list.capacity());
    list.pop_back();
    ASSERT_EQ(16, list.capacity());
    list.pop_back();
    ASSERT_EQ(7, list.length())
    ASSERT_EQ(8, list.capacity());
    list.pop_back();
    ASSERT_EQ(8, list.capacity());
    list.pop_back();
    ASSERT_EQ(8, list.capacity());
    list.pop_back();
    ASSERT_EQ(4, list.length())
    ASSERT_EQ(8, list.capacity());
    list.pop_back();
    ASSERT_EQ(3, list.length())
    ASSERT_EQ(4, list.capacity());
    list.pop_back();
    ASSERT_EQ(2, list.length())
    ASSERT_EQ(4, list.capacity());
    list.pop_back();
    ASSERT_EQ(1, list.length())
    ASSERT_EQ(4, list.capacity());
    list.pop_back();
    ASSERT_EQ(0, list.length())
    ASSERT_EQ(4, list.capacity());
}
