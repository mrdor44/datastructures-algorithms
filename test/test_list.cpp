#include "inc/list.hpp"
#include "mock.hpp"

TEST(List, PushFrontAndClear) {
    List<int> list;
    list.push_front(5);
    EXPECT_EQ(5, list[0]);
    EXPECT_EQ(5, list.front());
    list.clear();
    EXPECT_EQ(0, list.length());
}

TEST(List, EraseAndLength) {
    List<int> list;
    EXPECT_EQ(0, list.length());
    list.push_front(5);
    EXPECT_EQ(1, list.length());
    list.erase(0);
    EXPECT_EQ(0, list.length());
}

TEST(List, InsertAndPopFront) {
    List<int> list;
    list.insert(0, 0);
    list.insert(1, 1);
    EXPECT_EQ(1, list.back());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list[1]);
    list.pop_front();
    EXPECT_EQ(1, list[0]);
}

TEST(List, PushPopBack) {
    List<int> list;
    list.push_front(0);
    list.push_back(1);
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list[1]);
    list.pop_back();
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list.length());
}