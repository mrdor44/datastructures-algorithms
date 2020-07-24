#include <vector>
#include "inc/array_list.hpp"
#include "mock.hpp"

TEST(ArrayList, PushBack) {
    ArrayList<int> list;
    list.push_back(5);
    EXPECT_EQ(5, list[0]);
}
