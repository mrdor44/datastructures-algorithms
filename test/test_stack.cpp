#include <vector>
#include "inc/stack.hpp"
#include "mock.hpp"

TEST(Stack, PushTopPop) {
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(1, stack.top());
    stack.push(2);
    EXPECT_EQ(2, stack.top());
    stack.pop();
    EXPECT_EQ(1, stack.top());
    stack.pop();
}

TEST(Stack, PushRange) {
    Stack<int> stack;
    std::vector<int> v({1, 2, 3});
    stack.push(v.begin(), v.end());
    EXPECT_EQ(stack.top(), 1);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 3);
}