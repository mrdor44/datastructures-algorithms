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