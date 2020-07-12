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

TEST(List, Move) {
    List<int> list1({1, 2, 3, 4});
    List<int> list2(std::move(list1));
    EXPECT_EQ(list2, List<int>({1, 2, 3, 4}));
}

TEST(List, Copy) {
    List<int> list1({1, 2, 3, 4});
    List<int> list2(list1);
    EXPECT_EQ(list1, List<int>({1, 2, 3, 4}));
    EXPECT_EQ(list2, List<int>({1, 2, 3, 4}));
}

TEST(List, Equal) {
    List<int> list1({1, 2, 3, 4});
    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    EXPECT_EQ(list1, list2);
}

TEST(List, Unequal) {
    EXPECT_NE(List<int>({4, 3, 2, 1}), List<int>({4, 3, 2, 1, 0}));
    EXPECT_NE(List<int>({4, 3, 2, 1}), List<int>({1, 2, 3, 4}));
    EXPECT_NE(List<int>({4, 3, 2, 1}), List<int>({4, 3, 2, 0}));
    EXPECT_NE(List<int>({4, 3, 2, 1}), List<int>({4, 3, 2}));
    EXPECT_NE(List<int>({4, 3, 2, 1}), List<int>());
}
