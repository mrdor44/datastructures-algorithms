#include <vector>
#include "inc/array_list.hpp"
#include "mock.hpp"

int push_beyond_capacity(ArrayList<int>& list) {
    int i = 0;
    for (; i < 1 + list.capacity(); ++i) {
        list.push_back(i);
    }
    return i; // as the last value pushed back
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
